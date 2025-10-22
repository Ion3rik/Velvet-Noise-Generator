#pragma once
#include <JuceHeader.h>

namespace Param
{

    namespace ID
    {
        static const juce::String Gain { "gain" };
    }

    namespace Name
    {
        static const juce::String Gain { "Gain" };
    }
    namespace Unit
    {
        static const juce::String dB { "dB" };
        static const juce::String Seconds { "s" };
        static const juce::String Percent { "%" };
    }

    namespace Range
    {
        static constexpr float GainDef { 0.f };
        static constexpr float GainMin { -60.f };
        static constexpr float GainMax { 0.f };
        static constexpr float GainInc { .1f };
        static constexpr float GainSkew { 3.f };
    }

    namespace Value
    {
        static constexpr double RampTimeS { 0.02 };
    }

    const std::vector<mrta::ParameterInfo>& getParameterVector()
    {
        static const std::vector<mrta::ParameterInfo> paramVector
        {
            { Param::ID::Gain, Param::Name::Gain, Param::Unit::dB, Param::Range::GainDef, Param::Range::GainMin, Param::Range::GainMax, Param::Range::GainInc, Param::Range::GainSkew }

        };

        return paramVector;
    }
}