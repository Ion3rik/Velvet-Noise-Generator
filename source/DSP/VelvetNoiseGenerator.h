#pragma once
#include <JuceHeader.h>


namespace DSP
{
class VelvetNoiseGenerator
{
    public:
        VelvetNoiseGenerator();
        ~VelvetNoiseGenerator();

        void prepare(double sampleRate);
        void process(float* const* output, unsigned int numChannels, unsigned int numSamples);
        float getNextSample();
        void setEnabled(bool enabled);
        void setDensity(float density);
        void setPulseWidth(float width);

    private:
        void updatePulse();
        unsigned int relativePulseWidthToSamples(float widthNorm)
        {
            return std::max(1u, static_cast<unsigned int>(widthNorm * gridSize));
        }

        // Parameters
        bool enabled { false }; // generator enabled flag
        double sampleRate { 44100.0 }; // sample rate in Hz
        float pulseWidth { 0 }; // pulse width relative to grid size
        unsigned int gridSize { 24 }; // grid size in samples
        float gain { 1.0f }; // current gain of the pulse
        int sign { 1 }; // current sign of the pulse
        unsigned int location { 0 }; // current location of the pulse
        unsigned int gridPhase { 0 }; // current phase within the grid
        juce::Random rd; // random number generator


};
}// namespace DSP