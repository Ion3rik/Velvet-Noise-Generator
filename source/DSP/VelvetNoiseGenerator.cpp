#include "VelvetNoiseGenerator.h"
#include <JuceHeader.h>

namespace DSP
{
VelvetNoiseGenerator::VelvetNoiseGenerator()
{

}

VelvetNoiseGenerator::~VelvetNoiseGenerator()
{

}

void VelvetNoiseGenerator::prepare(double sampleRate)
{
    this->sampleRate = sampleRate;
}


void VelvetNoiseGenerator::process(float* const* output, unsigned int numChannels, unsigned int numSamples)
{
    if (!enabled)
        return;

    // Generate velvet noise for the first channel
    std::fill(output[0], output[0] + numSamples, 0.0f);
    for (unsigned int n = 0; n < numSamples; ++n)
    {
        output[0][n] += getNextSample();
    }

    // Copy first channel to all other channels
    for (unsigned int ch = 1; ch < numChannels; ++ch)
        std::memcpy(output[ch], output[0], numSamples * sizeof(float));
}

float VelvetNoiseGenerator::getNextSample()
{
    updatePulse(); // Update pulse parameters if needed (logic inside the function)
    unsigned int pulsePhase = gridPhase - location; // phase within the pulse (negative if before pulse)
    float mask = (0 <= pulsePhase && pulsePhase <= relativePulseWidthToSamples(pulseWidth)); // pulse active mask
    float sample = sign * gain * mask; // generate sample
    gridPhase = (gridPhase + 1) % gridSize; // advance and wrap grid phase

    return sample;
}

void VelvetNoiseGenerator::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

void VelvetNoiseGenerator::setDensity(float density)
{
    this->gridSize = static_cast<unsigned int>(sampleRate / density ); // Convert density (pulses per second) to grid size in samples
    gain = std::sqrt(static_cast<float>(gridSize) * 1.0f/sampleRate); // energy normalization
}

void VelvetNoiseGenerator::setPulseWidth(float width)
{
    this->pulseWidth =  width*0.01; // width in [0,1] for 0–100% relative to grid size

}

void VelvetNoiseGenerator::setRegularity(float regularity)
{
    this->regularity = regularity*0.01; // regularity in [0,1] for 0–100%
}

void VelvetNoiseGenerator::updatePulse()
{
    // Only generate a new pulse at grid start
    unsigned int update = (gridPhase == 0);

    location = update * rd.nextInt(static_cast<int>((1-regularity)*(gridSize - relativePulseWidthToSamples(pulseWidth)))+1) + (1 - update) * location; // update location
    sign = update * (2*static_cast<int>(rd.nextBool())-1)+ (1 - update) * sign; // update sign
    
}

} // namespace DSP