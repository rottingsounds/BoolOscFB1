/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class BoolOscFB1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BoolOscFB1AudioProcessorEditor (BoolOscFB1AudioProcessor&);
    ~BoolOscFB1AudioProcessorEditor() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    typedef std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> SliderAttachmentPtr;

    int width_u;
    int height_u;
    int unit;
    
    void setSliderBounds (juce::Slider& sl, int x, int y, int w, int h);
    void createSlider (juce::Slider& sl, juce::Label& lb, juce::String label, bool hasTextBox = true, int w = 50, int h = 25);


    juce::Slider mod1Slider;
    juce::Slider mod2Slider;
    juce::Slider bias1Slider;
    juce::Slider bias2Slider;
    juce::Slider leakSlider;
    juce::Slider distortSlider;
    juce::Slider ampSlider;
    juce::Slider widthSlider;
    juce::Slider rotSlider;
    juce::Slider lpfreqSlider;

    SliderAttachmentPtr mod1SliderAttachment;
    SliderAttachmentPtr mod2SliderAttachment;
    SliderAttachmentPtr bias1SliderAttachment;
    SliderAttachmentPtr bias2SliderAttachment;
    SliderAttachmentPtr leakSliderAttachment;
    SliderAttachmentPtr distortSliderAttachment;
    SliderAttachmentPtr ampSliderAttachment;
    SliderAttachmentPtr widthSliderAttachment;
    SliderAttachmentPtr rotSliderAttachment;
    SliderAttachmentPtr lpfreqSliderAttachment;

    juce::Label mod1Label;
    juce::Label mod2Label;
    juce::Label bias1Label;
    juce::Label bias2Label;
    juce::Label leakLabel;
    juce::Label distortLabel;
    juce::Label ampLabel;
    juce::Label widthLabel;
    juce::Label rotLabel;
    juce::Label lpfreqLabel;


    BoolOscFB1AudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BoolOscFB1AudioProcessorEditor)
};
