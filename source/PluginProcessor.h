#pragma once
#include <JuceHeader.h>
#include "Utils/SmoothedGain.h"
#include "DSP/VelvetNoiseGenerator.h"


class MyAudioProcessor : public juce::AudioProcessor
{
public:
    MyAudioProcessor();
    ~MyAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void releaseResources() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    mrta::ParameterManager& getParameterManager() { return paramManager; }

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int) override;
    const juce::String getProgramName(int) override;
    void changeProgramName(int, const juce::String&) override;
    //==============================================================================
    
    juce::AbstractFifo fifo { 48000 }; // Example: 1 second of mono data
    juce::AudioBuffer<float> fifoBuffer { 1, 48000 };
    std::atomic<int> fifoWritePosition { 0 };
private:

    Utils::SmoothedGain smoothedGain;
    mrta::ParameterManager paramManager;

    DSP::VelvetNoiseGenerator velvetNoiseGenerator;
    void pushNextSampleIntoFifo(float sample);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyAudioProcessor)
};