#include "PluginEditor.h"


MyAudioProcessorEditor::MyAudioProcessorEditor(MyAudioProcessor& p)
    : AudioProcessorEditor(p), audioProcessor(p),
    genericParamEditor(audioProcessor.getParameterManager())
    
{
    unsigned int numParams { static_cast<unsigned int>(audioProcessor.getParameterManager().getParameters().size()) };
    unsigned int paramHeight { static_cast<unsigned int>(genericParamEditor.parameterWidgetHeight) };

    addAndMakeVisible(genericParamEditor);
    setSize(500, numParams * paramHeight);

    addAndMakeVisible(waveform);
    startTimerHz(30);
}



MyAudioProcessorEditor::~MyAudioProcessorEditor()
{
    setLookAndFeel(nullptr); // Reset the look and feel to default
}

//==============================================================================
void MyAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MyAudioProcessorEditor::resized()
{
    // Height for the waveform plot
    const int waveformHeight = 100;

    // Set bounds for waveform at the top
    waveform.setBounds(10, 10, getWidth() - 20, waveformHeight);

    // Set bounds for parameter editor below the waveform
    // Top starts after waveform ends (add margin if desired)
    genericParamEditor.setBounds(
        0,
        waveformHeight + 20,  // 20 is margin below waveform, adjust as needed
        getWidth(),
        getHeight() - (waveformHeight + 20)
    );
}

void MyAudioProcessorEditor::timerCallback()
{
    auto& fifo = audioProcessor.fifoBuffer;
    int writePos = audioProcessor.fifoWritePosition.load(std::memory_order_acquire);

    // Get a window of the most recent samples
    const int numSamples = 256; // choose a small window
    std::vector<float> temp(numSamples);

    for (int i = 0; i < numSamples; ++i)
    {
        int idx = (writePos + fifo.getNumSamples() - numSamples + i) % fifo.getNumSamples();
        temp[i] = 10.0f * fifo.getSample(0, idx); // Scale for visibility
    }

    waveform.pushSamples(temp.data(), numSamples);
}
