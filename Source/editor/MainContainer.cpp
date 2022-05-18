//
// Created by Martin Rumori on 10.05.22.
//

#include "MainContainer.h"
#include <ParameterIds.h>

MainContainer::MainContainer (juce::AudioProcessorValueTreeState& apvts)
    : compressorAttackSliderAttachment (apvts, ParameterIds::compressorAttack, compressorAttackSlider)
{

    //addAndMakeVisible(sizeKnob);
    //addAndMakeVisible (compressorAttackSlider);
}

void MainContainer::resized()
{
    //sizeKnob.setBoundsRelative(0.28f, 0.5711f, 0.1975f, 0.3511f);
    // compressorAttackSlider.setBoundsRelative (...);
}

void MainContainer::paint (juce::Graphics& g)
{

}
