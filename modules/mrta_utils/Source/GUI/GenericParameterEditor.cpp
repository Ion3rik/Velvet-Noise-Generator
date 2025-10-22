/*
 * Original code copyright © Joao Rossi
 * Original source: https://github.com/joaorossi/modern-real-time-audio-2025
 * Modifications copyright © 2025 Jon Fagerström
 */

namespace mrta
{

GenericParameterEditor::GenericParameterEditor(mrta::ParameterManager& parameterManager, int pwh, const juce::StringArray& pids) :
    parameterWidgetHeight { pwh },
    parameterIDs { pids }
{
    juce::AudioProcessorValueTreeState& apvts { parameterManager.getAPVTS() };

    const std::vector<mrta::ParameterInfo>& originalParameters { parameterManager.getParameters() };
    std::vector<mrta::ParameterInfo> parameters;

    if (parameterIDs.size())
    {
        for (const mrta::ParameterInfo& pi : originalParameters)
            if (parameterIDs.contains(pi.ID))
                parameters.push_back(pi);
    }
    else
    {
        for (const mrta::ParameterInfo& pi : originalParameters)
            parameters.push_back(pi);
    }

    std::transform(parameters.begin(), parameters.end(), std::back_inserter(parameterComponents),
    [&apvts] (const mrta::ParameterInfo& p)
    {
        std::unique_ptr<juce::Component> ptr;
        switch (p.type)
        {
            case mrta::ParameterInfo::Float:
                ptr = std::make_unique<mrta::ParameterSlider>(p.ID, apvts);
                break;

            case mrta::ParameterInfo::Choice:
                ptr = std::make_unique<mrta::ParameterComboBox>(p.ID, apvts);
                break;

            case mrta::ParameterInfo::Bool:
                ptr = std::make_unique<mrta::ParameterButton>(p.ID, apvts);
                break;
        }
        return ptr;
    });

    std::transform(parameters.begin(), parameters.end(), std::back_inserter(parameterLabels),
    [&apvts] (const mrta::ParameterInfo& p)
    {
        std::unique_ptr<juce::Label> ptr { std::make_unique<juce::Label>() };
        ptr->setText(p.name, juce::dontSendNotification);
        ptr->setFont(juce::FontOptions(12.f));
        return ptr;
    });

    std::for_each(parameterComponents.begin(), parameterComponents.end(), [this] (const auto& pc) { addAndMakeVisible(pc.get()); });
    std::for_each(parameterLabels.begin(), parameterLabels.end(), [this] (const auto& pl) { addAndMakeVisible(pl.get()); });
}

void GenericParameterEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}
void GenericParameterEditor::resized()
{
    const int numColumns = 3;
    const int numParams = static_cast<int>(parameterComponents.size());
    const int numRows = (numParams + numColumns - 1) / numColumns;

    auto bounds = getLocalBounds().toFloat();
    auto cellWidth = bounds.getWidth() / numColumns;
    auto cellHeight = bounds.getHeight() / numRows;

    for (int i = 0; i < numParams; ++i)
    {
        int row = i / numColumns;
        int col = i % numColumns;

        // Compute cell bounds
        juce::Rectangle<float> cellBounds {
            col * cellWidth,
            row * cellHeight,
            cellWidth,
            cellHeight
        };

        // Divide cell into label and widget vertically
        auto labelBounds = cellBounds.removeFromTop(cellHeight * 0.4f);
        auto widgetBounds = cellBounds; // Remainder

        parameterLabels[i]->setBounds(labelBounds.toNearestInt());
        parameterComponents[i]->setBounds(widgetBounds.toNearestInt());
    }
}


}
