#pragma once
#include <JuceHeader.h>

namespace Param
{

    namespace ID
    {   
        static const juce::String Enabled { "enabled" };
        static const juce::String Gain { "gain" };
        static const juce::String PulseWidth { "pulseWidth" };
        static const juce::String Density { "density" };
    }

    namespace Name
    {
        static const juce::String Enabled { "Enabled" };
        static const juce::String Gain { "Gain" };
        static const juce::String PulseWidth { "Pulse Width" };
        static const juce::String Density { "Density" };
    }
    namespace Unit
    {
        static const juce::String dB { "dB" };
        static const juce::String Seconds { "s" };
        static const juce::String Percent { "%" };
        static const juce::String PulsePerS { "pulse/s" };
    }

    namespace Range
    {
        static const juce::String EnabledOff { "Off" };
        static const juce::String EnabledOn { "On" };

        static constexpr float GainDef { 0.f };
        static constexpr float GainMin { -60.f };
        static constexpr float GainMax { 0.f };
        static constexpr float GainInc { .1f };
        static constexpr float GainSkew { 3.f };

        static constexpr float PulseWidthDef { 0.f };
        static constexpr float PulseWidthMin { 0.f };
        static constexpr float PulseWidthMax { 100.f };
        static constexpr float PulseWidthInc { 0.1f };
        static constexpr float PulseWidthSkew { 1.f };

        static constexpr float DensityDef { 1000.f };
        static constexpr float DensityMin { 1.f };
        static constexpr float DensityMax { 10000.f };
        static constexpr float DensityInc { 0.01f };
        static constexpr float DensitySkew { 0.5f };
    }

    namespace Value
    {
        static constexpr double RampTimeS { 0.02 };
    }

    const std::vector<mrta::ParameterInfo>& getParameterVector()
    {
        static const std::vector<mrta::ParameterInfo> paramVector
        {
            { Param::ID::Enabled,  Param::Name::Enabled,  Param::Range::EnabledOff, Param::Range::EnabledOn, false },
            { Param::ID::Gain, Param::Name::Gain, Param::Unit::dB, Param::Range::GainDef, Param::Range::GainMin, Param::Range::GainMax, Param::Range::GainInc, Param::Range::GainSkew },
            { Param::ID::Density, Param::Name::Density, Param::Unit::PulsePerS, Param::Range::DensityDef, Param::Range::DensityMin, Param::Range::DensityMax, Param::Range::DensityInc, Param::Range::DensitySkew },
            { Param::ID::PulseWidth, Param::Name::PulseWidth, Param::Unit::Percent, Param::Range::PulseWidthDef, Param::Range::PulseWidthMin, Param::Range::PulseWidthMax, Param::Range::PulseWidthInc, Param::Range::PulseWidthSkew }
        };

        return paramVector;
    }
}