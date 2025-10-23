#include "PluginEditor.h"


MyAudioProcessorEditor::MyAudioProcessorEditor(MyAudioProcessor& p)
    : AudioProcessorEditor(p), audioProcessor(p),
    genericParamEditor(audioProcessor.getParameterManager())
    
{
    unsigned int numParams { static_cast<unsigned int>(audioProcessor.getParameterManager().getParameters().size()) };
    unsigned int paramHeight { static_cast<unsigned int>(genericParamEditor.parameterWidgetHeight) };

    addAndMakeVisible(genericParamEditor);
    setSize(500, numParams * paramHeight);
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
    genericParamEditor.setBounds(getLocalBounds());
}
