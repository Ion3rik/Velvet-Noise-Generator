#pragma once
#include <JuceHeader.h>

namespace Utils
{
class SmoothedGain : public juce::SmoothedValue<float>
{
    public:
        SmoothedGain() = default;

        void prepare(double sampleRate, double rampTimeSeconds, float defValuedB)
        {
            reset(sampleRate, rampTimeSeconds); // set sample rate and ramp time
            setCurrentAndTargetValue(juce::Decibels::decibelsToGain(defValuedB)); // set default value
        }

        void setTargetGain(float newGaindB)
        {
            setTargetValue(juce::Decibels::decibelsToGain(newGaindB));  
        }
};
}
