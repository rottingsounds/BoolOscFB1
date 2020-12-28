/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "SynthVoiceFaust.h"
#include "SynthSound.h"


//==============================================================================
/**
 */
class BoolOscFB1AudioProcessor  : public juce::AudioProcessor
{
public:
  //==============================================================================
  BoolOscFB1AudioProcessor();
  ~BoolOscFB1AudioProcessor() override;
  
  //==============================================================================
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;
  
#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
  
  void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
  
  //==============================================================================
  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;
  
  //==============================================================================
  const juce::String getName() const override;
  
  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;
  
  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const juce::String getProgramName (int index) override;
  void changeProgramName (int index, const juce::String& newName) override;
  
  //==============================================================================
  void getStateInformation (juce::MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;
  

  juce::AudioProcessorValueTreeState apvts;

private:
  juce::Synthesiser synth;
  juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
  void linkParameters();
  
// pointers to parameters updated by 
  std::atomic<float>* mod1Parameter = nullptr;
  std::atomic<float>* mod2Parameter = nullptr;
  std::atomic<float>* bias1Parameter = nullptr;
  std::atomic<float>* bias2Parameter = nullptr;
  std::atomic<float>* leakParameter = nullptr;
  std::atomic<float>* distortParameter = nullptr;
  std::atomic<float>* ampParameter = nullptr;
  std::atomic<float>* widthParameter = nullptr;
  std::atomic<float>* rotParameter = nullptr;
  std::atomic<float>* lpfreqParameter = nullptr;

  
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BoolOscFB1AudioProcessor)
};
