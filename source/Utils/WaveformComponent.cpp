#include "WaveformComponent.h"

WaveformComponent::WaveformComponent(int bufferSize_, int displaySize_)
    : bufferSize(bufferSize_), displaySize(displaySize_)
{
    circularBuffer.setSize(1, bufferSize, false, false, true);
    displayData.resize(displaySize, 0.0f);
    setOpaque(true);
    start(); // Starts the update timer at 30 FPS by default
}

void WaveformComponent::pushSamples(const float* samples, int numSamples)
{
    // Safe for audio thread: only writes to circularBuffer and writePos
    int pos = writePos.load(std::memory_order_relaxed);

    for (int i = 0; i < numSamples; ++i)
    {
        circularBuffer.setSample(0, pos, samples[i]);
        pos = (pos + 1) % bufferSize;
    }
    writePos.store(pos, std::memory_order_release);
}

void WaveformComponent::timerCallback()
{
    // Pull latest displaySize samples for drawing
    int pos = writePos.load(std::memory_order_acquire);
    for (int i = 0; i < displaySize; ++i)
    {
        // Oldest to newest (wraps around buffer)
        int bufferIndex = (pos + bufferSize - displaySize + i) % bufferSize;
        displayData[i] = circularBuffer.getSample(0, bufferIndex);
    }
    repaint();
}

void WaveformComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    auto w = getWidth();
    auto h = getHeight();

    if (displayData.empty())
        return;

    juce::Path p;
    p.startNewSubPath(0, h * 0.5f);

    for (int x = 0; x < w; ++x)
    {
        int dataIdx = juce::jmap(x, 0, w-1, 0, (int)displayData.size()-1);
        float y = juce::jmap(displayData[dataIdx], -1.0f, 1.0f, (float)h, 0.0f);
        p.lineTo((float)x, y);
    }
    g.strokePath(p, juce::PathStrokeType(2.0f));
}

void WaveformComponent::resized()
{
    // Nothing needed for this example
}

void WaveformComponent::start(int fps)
{
    startTimerHz(fps);
}

void WaveformComponent::stop()
{
    stopTimer();
}