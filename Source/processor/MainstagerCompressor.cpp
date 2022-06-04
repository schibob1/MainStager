#include "MainstagerCompressor.h"

//==============================================================================
MainstagerCompressor::MainstagerCompressor()
{
    update();
}

//==============================================================================
void MainstagerCompressor::setThreshold (float newThreshold)
{
    thresholddB = newThreshold;
    update();
}

void MainstagerCompressor::setRatio (float newRatio)
{
    jassert (newRatio >= 1.0f);

    ratio = newRatio;
    update();
}

void MainstagerCompressor::setAttack (float newAttack)
{
    attackTime = newAttack;
    update();
}

void MainstagerCompressor::setRelease (float newRelease)
{
    releaseTime = newRelease;
    update();
}

//==============================================================================
void MainstagerCompressor::prepare (const juce::dsp::ProcessSpec& spec)
{
    jassert (spec.sampleRate > 0);
    jassert (spec.numChannels > 0);

    sampleRate = spec.sampleRate;

    envelopeFilter.prepare (spec);

    update();
    reset();
}

void MainstagerCompressor::reset()
{
    envelopeFilter.reset();
}

//==============================================================================
float MainstagerCompressor::processSample (int channel, float mainInputValue, float sideInputValue)
{
    // Ballistics filter with peak rectifier
    auto env = envelopeFilter.processSample (channel, sideInputValue);

    // VCA
    auto gain = (env < threshold) ? 1.0f
                                  : std::pow (env * thresholdInverse, ratioInverse - 1.0f);

    // Output
    return gain * mainInputValue;
}

void MainstagerCompressor::update()
{
    threshold = juce::Decibels::decibelsToGain (thresholddB, -200.0f);
    thresholdInverse = 1.0f / threshold;
    ratioInverse = 1.0f / ratio;

    envelopeFilter.setAttackTime (attackTime);
    envelopeFilter.setReleaseTime (releaseTime);
}
