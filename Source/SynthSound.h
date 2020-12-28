/*
 ==============================================================================
 
 SynthSound.h
 Created: 23 Dec 2020 3:53:15pm
 Author:  lfsaw
 
 ==============================================================================
 */

#pragma once


#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
  bool appliesToNote (int midiNoteNumber) override {
    return true;
  }
  bool appliesToChannel (int midiChannel) override {
    return true;
  }
};
