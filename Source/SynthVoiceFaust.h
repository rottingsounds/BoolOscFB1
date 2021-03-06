/*
 ==============================================================================
 
 SynthVoice.h
 Created: 23 Dec 2020 3:52:58pm
 Author:  lfsaw
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

// FAUST specific {{{
//#include "BoolOscFB1.h"
#include "BoolOscFB1-vec.h"
// FAUST specific }}}

class SynthVoiceFaust : public juce::SynthesiserVoice {
    
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
    void releaseResources() {}
    
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    
    // FAUST {{{
    void setMod1(float val);
    void setMod2(float val);
    void setBias1(float val);
    void setBias2(float val);
    void setLeak(float val);
    void setDistort(float val);
    void setAmp(float val);
    void setWidth(float val);
    void setRot(float val);
    void setLpfreq(float val);
    // FAUST }}}
    
    std::unique_ptr<juce::NormalisableRange<float>> getRangeForParam(juce::String& name);
    
private:
    juce::dsp::ProcessSpec spec;
    
    // FAUST specific {{{
    APIUI fUI; // UI contains control parameters for the Faust DSP
//    dsp* fDSP;  // contains audio DSP/callback
    std::unique_ptr<dsp> fDSP;  // contains audio DSP/callback
//    float** outputs; // used to collect output of faust dsp
//    std::vector<float> outputs;

    // FAUST specific }}}
    
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
        
    bool isPrepared {false};
};
