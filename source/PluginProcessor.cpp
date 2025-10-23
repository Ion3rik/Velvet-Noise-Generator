#include "PluginProcessor.h"
#include <JuceHeader.h>
#include "PluginEditor.h"
#include "Parameters.h"


MyAudioProcessor::MyAudioProcessor() :
    paramManager(*this, ProjectInfo::projectName, Param::getParameterVector()) // Construct the parameter manager
    
{
    // Register parameter callbacks here

    paramManager.registerParameterCallback(Param::ID::Enabled,
    [this](float newValue, bool force)
    {
        velvetNoiseGenerator.setEnabled(static_cast<bool>(static_cast<int>(newValue)));
    });

    paramManager.registerParameterCallback(Param::ID::Density,
    [this](float newValue, bool force)
    {
        velvetNoiseGenerator.setDensity(newValue);
    });

    paramManager.registerParameterCallback(Param::ID::PulseWidth,
    [this](float newValue, bool force)
    {
        velvetNoiseGenerator.setPulseWidth(newValue);
    });

    paramManager.registerParameterCallback(Param::ID::Gain,
    [this](float newValue, bool force)
    {
        smoothedGain.setTargetGain(newValue);
    });

}

MyAudioProcessor::~MyAudioProcessor()
{
}

void MyAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    smoothedGain.prepare(sampleRate, Param::Value::RampTimeS, Param::Range::GainDef);
    velvetNoiseGenerator.prepare(sampleRate);
}

void MyAudioProcessor::releaseResources()
{
}

void MyAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    juce::ScopedNoDenormals noDenormals;
    paramManager.updateParameters();

    const unsigned int numChannels{ static_cast<unsigned int>(buffer.getNumChannels()) };
    const unsigned int numSamples{ static_cast<unsigned int>(buffer.getNumSamples()) };

    // Generate velvet noise
    velvetNoiseGenerator.process(buffer.getArrayOfWritePointers(), numChannels, numSamples);

    // Apply smoothed gain
    smoothedGain.applyGain(buffer, numSamples);

}

void MyAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    paramManager.getStateInformation(destData);

}

void MyAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    paramManager.setStateInformation(data, sizeInBytes);
}

bool MyAudioProcessor::acceptsMidi() const
{
    return true;
}




//==============================================================================
const juce::String MyAudioProcessor::getName() const { return JucePlugin_Name; }
bool MyAudioProcessor::producesMidi() const { return false; }
bool MyAudioProcessor::isMidiEffect() const { return false; }
double MyAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int MyAudioProcessor::getNumPrograms() { return 1; }
int MyAudioProcessor::getCurrentProgram() { return 0; }
void MyAudioProcessor::setCurrentProgram(int) { }
const juce::String MyAudioProcessor::getProgramName(int) { return {}; }
void MyAudioProcessor::changeProgramName(int, const juce::String&) { }
bool MyAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* MyAudioProcessor::createEditor() { return new MyAudioProcessorEditor(*this); }
//==============================================================================

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyAudioProcessor();
}