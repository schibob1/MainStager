//
// Created by Martin Rumori on 10.05.22.
//

#include "MainContainer.h"
#include <ParameterIds.h>

MainContainer::MainContainer (juce::AudioProcessorValueTreeState& apvts)
    : compressorAttackSliderAttachment (apvts, ParameterIds::compressorAttack, compressorAttackSlider)
{

    addAndMakeVisible (compressorAttackSlider);
}

void MainContainer::resized()
{
    // compressorAttackSlider.setBoundsRelative (...);
}

void MainContainer::paint (juce::Graphics& g)
{

}
