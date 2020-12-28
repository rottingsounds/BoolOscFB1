/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BoolOscFB1AudioProcessor::BoolOscFB1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    linkParameters();
    
    // mono synth, create one sound and one voice at instantiation:
    // both are deleted by the SynthAllocator: no explicite delete needed
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoiceFaust());
}

BoolOscFB1AudioProcessor::~BoolOscFB1AudioProcessor()
{
}

//==============================================================================
const juce::String BoolOscFB1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BoolOscFB1AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool BoolOscFB1AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool BoolOscFB1AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double BoolOscFB1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BoolOscFB1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int BoolOscFB1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void BoolOscFB1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BoolOscFB1AudioProcessor::getProgramName (int index)
{
    return {};
}

void BoolOscFB1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BoolOscFB1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);
    
    // only one voice
    for (int i=0; i < synth.getNumVoices(); ++i)
    {
        if(auto voice = dynamic_cast<SynthVoiceFaust*>(synth.getVoice(i)))
        {
            voice->prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void BoolOscFB1AudioProcessor::releaseResources()
{
    for (int i=0; i < synth.getNumVoices(); ++i)
    {
        if(auto voice = dynamic_cast <SynthVoiceFaust*> (synth.getVoice(i)))
        {
            voice->releaseResources();
        }
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BoolOscFB1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void BoolOscFB1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i=0; i<synth.getNumVoices(); ++i)
    {
        // casting the voice to be a juce SynthesiserVoice
        if (auto voice = dynamic_cast <SynthVoiceFaust*> (synth.getVoice(i)))
        {
            // set parameters
            voice->setMod1 (*mod1Parameter);
            voice->setMod2 (*mod2Parameter);
            voice->setBias1 (*bias1Parameter);
            voice->setBias2 (*bias2Parameter);
            voice->setLeak (*leakParameter);
            voice->setDistort (*distortParameter);
            voice->setAmp (*ampParameter);
            voice->setWidth (*widthParameter);
            voice->setRot (*rotParameter);
            voice->setLpfreq (*lpfreqParameter);
        }
    }
    // calls voice:renderNextBlock internally for all active voices and sounds:
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BoolOscFB1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BoolOscFB1AudioProcessor::createEditor()
{
    return new BoolOscFB1AudioProcessorEditor (*this);
}

//==============================================================================
void BoolOscFB1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // implementation via https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void BoolOscFB1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // implementation via https://docs.juce.com/master/tutorial_audio_processor_value_tree_state.html
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout BoolOscFB1AudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MOD1", "Mod1",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 0.5f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MOD2", "Mod2",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 0.5f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("BIAS1", "Bias1",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 0.5f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("BIAS2", "Bias2",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 0.5f), 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LEAK", "Leak",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 0.5f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DISTORT", "Distort",
                                                                 juce::NormalisableRange<float>(1.0f, 5.f, 0.0f, 1.0f), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("AMP", "Amp",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 1.0f), 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WIDTH", "Width",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 1.0f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ROT", "Rot",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.0f, 1.0f), 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LPFREQ", "Lpfreq",
                                                                 juce::NormalisableRange<float>(50.0f, 12800.0f, 0.0f, 0.5f), 1000.0f));
    
    return {params.begin(), params.end()};
}


void BoolOscFB1AudioProcessor::linkParameters() {
    mod1Parameter = apvts.getRawParameterValue("MOD1");
    mod2Parameter = apvts.getRawParameterValue("MOD2");
    bias1Parameter = apvts.getRawParameterValue("BIAS1");
    bias2Parameter = apvts.getRawParameterValue("BIAS2");
    leakParameter = apvts.getRawParameterValue("LEAK");
    distortParameter = apvts.getRawParameterValue("DISTORT");
    ampParameter = apvts.getRawParameterValue("AMP");
    widthParameter = apvts.getRawParameterValue("WIDTH");
    rotParameter = apvts.getRawParameterValue("ROT");
    lpfreqParameter = apvts.getRawParameterValue("LPFREQ");
}





//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BoolOscFB1AudioProcessor();
}
