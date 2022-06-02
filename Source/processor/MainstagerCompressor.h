/**
    A simple compressor with standard threshold, ratio, attack time and release time
    controls.
*/

#pragma once

#include "ParameterIds.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class MainstagerCompressor
{
public:
    //==============================================================================
    /** Constructor. */
    MainstagerCompressor();

    //==============================================================================
    /** Sets the threshold in dB of the compressor.*/
    void setThreshold (float newThreshold);

    /** Sets the ratio of the compressor (must be higher or equal to 1).*/
    void setRatio (float newRatio);

    /** Sets the attack time in milliseconds of the compressor.*/
    void setAttack (float newAttack);

    /** Sets the release time in milliseconds of the compressor.*/
    void setRelease (float newRelease);

    //==============================================================================
    /** Initialises the processor. */
    void prepare (const juce::dsp::ProcessSpec& spec);

    /** Resets the internal state variables of the processor. */
    void reset();

    //==============================================================================
    /** Processes the input and output samples supplied in the processing context. */
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples  = outputBlock.getNumSamples();

        jassert (inputBlock.getNumChannels() == numChannels);
        jassert (inputBlock.getNumSamples()  == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom (inputBlock);
            return;
        }

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* inputSamples  = inputBlock .getChannelPointer (channel);
            auto* outputSamples = outputBlock.getChannelPointer (channel);

            for (size_t i = 0; i < numSamples; ++i)
                outputSamples[i] = processSample ((int) channel, inputSamples[i]);
        }
    }

    /** Performs the processing operation on a single sample at a time. */
    float processSample (int channel, float inputValue);

private:
    //==============================================================================
    void update();

    //==============================================================================
    float threshold, thresholdInverse, ratioInverse;
    juce::dsp::BallisticsFilter<float> envelopeFilter;

    double sampleRate = 44100.0;
    float thresholddB = 0.0f, ratio = 1.0f, attackTime = 1.0f, releaseTime = 100.0f;
};
