/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BoolOscFB1AudioProcessorEditor::BoolOscFB1AudioProcessorEditor (BoolOscFB1AudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
        
    createSlider(mod1Slider, mod1Label, "mod1");
    mod1SliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MOD1", mod1Slider);
    
    createSlider(mod2Slider, mod2Label, "mod2");
    mod2SliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MOD2", mod2Slider);
    
    createSlider(bias1Slider, bias1Label, "bias1");
    bias1SliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "BIAS1", bias1Slider);
    
    createSlider(bias2Slider, bias2Label, "bias2");
    bias2SliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "BIAS2", bias2Slider);
    
    createSlider(leakSlider, leakLabel, "leak");
    leakSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LEAK", leakSlider);
    
    createSlider(distortSlider, distortLabel, "distort");
    distortSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DISTORT", distortSlider);
    
    createSlider(ampSlider, ampLabel, "amp");
    ampSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "AMP", ampSlider);
    
    createSlider(widthSlider, widthLabel, "width");
    widthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WIDTH", widthSlider);
    
    createSlider(rotSlider, rotLabel, "rot");
    rotSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ROT", rotSlider);
    
    createSlider(lpfreqSlider, lpfreqLabel, "lpfreq");
    lpfreqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LPFREQ", lpfreqSlider);
    
    
    int width_px, height_px;

    width_u = 21;
    height_u = 14;
    
    width_px = 800;
    unit = width_px / width_u;
    height_px = height_u * (unit-1);
    
    setSize(width_px, height_px);
}

BoolOscFB1AudioProcessorEditor::~BoolOscFB1AudioProcessorEditor()
{
}

//==============================================================================
void BoolOscFB1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    //    g.setColour (juce::Colours::white);
    //    g.setFont (15.0f);
    //    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void BoolOscFB1AudioProcessorEditor::resized()
{
    setSliderBounds (distortSlider,
                      1, 9, 3, 3);
    setSliderBounds (ampSlider,
                      5, 9, 3, 3);
    setSliderBounds (widthSlider,
                     17, 9, 3, 3);
    setSliderBounds (rotSlider,
                     13, 9, 3, 3);
    setSliderBounds (lpfreqSlider,
                      9, 9, 3, 3);

    setSliderBounds (leakSlider,
                      9, 3, 3, 3);

    setSliderBounds (mod1Slider,
                      5, 1, 3, 3);
    setSliderBounds (mod2Slider,
                     13, 1, 3, 3);
    setSliderBounds (bias1Slider,
                      5, 5, 3, 3);
    setSliderBounds (bias2Slider,
                     13, 5, 3, 3);
}


void BoolOscFB1AudioProcessorEditor::createSlider (juce::Slider& sl, juce::Label& lb, juce::String label, bool hasTextBox, int w, int h) {

    addAndMakeVisible (sl);
    sl.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    if (hasTextBox) {
        sl.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    } else {
        sl.setTextBoxStyle (juce::Slider::NoTextBox, true, 50, 25);
    }

    addAndMakeVisible (lb);
    lb.setText (label, juce::dontSendNotification);
    lb.setJustificationType(juce::Justification::centred);
    lb.attachToComponent (&sl, false);
}

void BoolOscFB1AudioProcessorEditor::setSliderBounds (juce::Slider& sl, int x, int y, int w, int h) {
    sl.setBounds (x * unit,
                  y * unit,
                  w * unit,
                  h * unit);
}
