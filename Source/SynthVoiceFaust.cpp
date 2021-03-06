/*
 ==============================================================================
 
 SynthVoiceFaust.cpp
 Created: 23 Dec 2020 3:52:58pm
 Author:  lfsaw
 
 ==============================================================================
 */

#include "SynthVoiceFaust.h"


bool SynthVoiceFaust::canPlaySound (juce::SynthesiserSound* sound) {
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoiceFaust::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) {
    //  osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    
    
    // {{{ FAUST
    fDSP->instanceClear(); // reset
    // set_freq(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    // }}}
    
    adsr.noteOn();
}

void SynthVoiceFaust::stopNote (float velocity, bool allowTailOff) {
    adsr.noteOff();
}

void SynthVoiceFaust::controllerMoved (int controllerNumber, int newControllerValue) {}

void SynthVoiceFaust::pitchWheelMoved(int newPitchWheelValue) {
//    std::cout << "p " << newPitchWheelValue << std::endl;
}

void SynthVoiceFaust::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels) {
    
    // SPEC
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numOutputChannels;
    
    
    // FAUST {{{
    fDSP = std::make_unique <mydsp> (); // FAUST dsp object
    fDSP->init (sampleRate); // set samplerate
    fDSP->buildUserInterface (&fUI);
    // FAUST }}}
        
    // ADSR
    // "plain juce"-style adsr
    adsr.setSampleRate(sampleRate);
    adsr.setParameters(juce::ADSR::Parameters {1.0f, 0.0f, 1.0f, 1.0f} );
    
    isPrepared = true;
}


void SynthVoiceFaust::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    jassert (isPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock {outputBuffer};
        
    
    // FAUST {{{
    fDSP->compute(outputBuffer.getNumSamples(),NULL,outputBuffer.getArrayOfWritePointers());
    // FAUST }}}

    // ADSR
    // "plain juce"-style of applying efx to a vbuffer;
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}



//===============================================================================
// FAUST {{{
void SynthVoiceFaust::setMod1(float val) {
    fUI.setParamValue("mod1", val);
};
void SynthVoiceFaust::setMod2(float val) {
    fUI.setParamValue("mod2", val);
};
void SynthVoiceFaust::setBias1(float val) {
    fUI.setParamValue("bias1", val);
};
void SynthVoiceFaust::setBias2(float val) {
    fUI.setParamValue("bias2", val);
};
void SynthVoiceFaust::setLeak(float val) {
    fUI.setParamValue("leak", val);
};
void SynthVoiceFaust::setDistort(float val) {
    fUI.setParamValue("distort", val);
};
void SynthVoiceFaust::setAmp(float val) {
    fUI.setParamValue("amp", val);
};
void SynthVoiceFaust::setWidth(float val) {
    fUI.setParamValue("width", val);
};
void SynthVoiceFaust::setRot(float val) {
    fUI.setParamValue("rot", val);
};
void SynthVoiceFaust::setLpfreq(float val) {
    fUI.setParamValue("lpfreq", val);
};
// FAUST }}}

std::unique_ptr<juce::NormalisableRange<float>> SynthVoiceFaust::getRangeForParam(juce::String& name) {
    auto rangePtr = std::make_unique<juce::NormalisableRange<float>>(0, 1, 0, 2);
    
    return rangePtr;
};
