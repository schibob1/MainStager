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
        auto& outputBlock = context.getOutputBlock();
        const auto numSamples = inputBlock.getNumSamples();
        const auto numTotalChannels = inputBlock.getNumChannels();

        jassert (numTotalChannels > 1 && numTotalChannels % 2 == 0);

        const auto busChannels = numTotalChannels / 2;

        jassert (outputBlock.getNumChannels() == numTotalChannels);
        jassert (outputBlock.getNumSamples() == numSamples);

        if (context.isBypassed)
        {
            outputBlock.copyFrom (inputBlock);
            return;
        }
        //Input Block in 2 Bus-Ansicht zerlegt
        const auto mainInputBlock = inputBlock.getSubsetChannelBlock (0, busChannels);
        const auto sideInputBlock = inputBlock.getSubsetChannelBlock (busChannels, busChannels);

        for (size_t channel = 0; channel < busChannels; ++channel)
        {
            auto* mainInputSamples = mainInputBlock.getChannelPointer (channel);
            auto* sideInputSamples = sideInputBlock.getChannelPointer (channel);
            auto* outputSamples = outputBlock.getChannelPointer (channel);

            for (size_t i = 0; i < numSamples; ++i)
                outputSamples[i] = processSample ((int) channel, mainInputSamples[i], sideInputSamples[i]);
        }
    }

    /** Performs the processing operation on a single sample at a time. */
    float processSample (int channel, float mainInputValue, float sideInputValue);

private:
    //==============================================================================
    void update();

    //==============================================================================
    float threshold, thresholdInverse, ratioInverse;
    juce::dsp::BallisticsFilter<float> envelopeFilter;

    double sampleRate = 44100.0;
    float thresholddB = 0.0f, ratio = 1.0f, attackTime = 1.0f, releaseTime = 100.0f;
};
