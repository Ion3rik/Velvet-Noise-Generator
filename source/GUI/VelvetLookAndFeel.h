
#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

namespace GUI
{
class VelvetLookAndFeel : public juce::LookAndFeel_V4
{
public:
    VelvetLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(181, 114, 174)); 
        setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);
        setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    }
};
} // namespace GUI
