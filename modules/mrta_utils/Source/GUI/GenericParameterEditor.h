/*
 * Original code copyright © Joao Rossi
 * Original source: https://github.com/joaorossi/modern-real-time-audio-2025
 * Modifications copyright © 2025 Jon Fagerström
 */

#pragma once

namespace mrta
{

class GenericParameterEditor : public juce::Component
{
public:
    GenericParameterEditor(mrta::ParameterManager& parameterManager,
                           int parameterWidgetHeight = 80,
                           const juce::StringArray& parameterIDs = {});
    GenericParameterEditor() = delete;

    void paint(juce::Graphics&) override;
    void resized() override;

    const int parameterWidgetHeight;

    std::vector<std::unique_ptr<juce::Component>>& getParameterComponents() { return parameterComponents;}


private:
    juce::StringArray parameterIDs;
    std::vector<std::unique_ptr<juce::Component>> parameterComponents;
    std::vector<std::unique_ptr<juce::Label>> parameterLabels;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GenericParameterEditor)
};

}
