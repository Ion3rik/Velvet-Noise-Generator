#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utils/WaveformComponent.h"
#include "GUI/VelvetLookAndFeel.h"

class MyAudioProcessorEditor : public juce::AudioProcessorEditor
                            , private juce::Timer
{
public:
    MyAudioProcessorEditor(MyAudioProcessor&);
    ~MyAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;
    MyAudioProcessor& audioProcessor;
    mrta::GenericParameterEditor genericParamEditor;
    WaveformComponent waveform;
    GUI::VelvetLookAndFeel velvetLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyAudioProcessorEditor)
};