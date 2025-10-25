#pragma once

#include <JuceHeader.h>

//==============================================================================
// A real-time waveform plot component for JUCE.
// Call pushSamples() from the audio thread to feed data.
// The GUI thread periodically pulls data and displays the waveform.
class WaveformComponent : public juce::Component, private juce::Timer
{
public:
    WaveformComponent(int bufferSize = 2048, int displaySize = 512);
    ~WaveformComponent() override = default;

    // Call this from the audio thread to push samples into the buffer
    void pushSamples(const float* samples, int numSamples);

    void paint(juce::Graphics&) override;
    void resized() override;

    // Call to start/stop the display update timer (optional)
    void start(int fps = 30);
    void stop();

private:
    void timerCallback() override;

    juce::AudioBuffer<float> circularBuffer;
    std::atomic<int> writePos { 0 };
    int bufferSize;
    int displaySize;
    std::vector<float> displayData; // Used only on the GUI thread
};