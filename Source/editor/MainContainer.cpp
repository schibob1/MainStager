#include "MainContainer.h"
#include <ParameterIds.h>

MainContainer::MainContainer (juce::AudioProcessorValueTreeState& apvts) //constructor
    : dryWetKnobAttachment (apvts, ParameterIds::dryWet, dryWetKnob),
      sizeKnobAttachment (apvts, ParameterIds::size, sizeKnob),
      //   widthKnobAttachment (apvts, ParameterIds::width, widthKnob),
      colourKnobAttachment (apvts, ParameterIds::colour, colourKnob),
      thresholdKnobAttachment (apvts, ParameterIds::threshold, thresholdKnob),
      speedKnobAttachment (apvts, ParameterIds::speed, speedKnob)

{
    //dryWet
    configureKnobAndLabel (dryWetKnob, dryWetLabel, "Volume");
    addAndMakeVisible (dryWetKnob);
    //addAndMakeVisible (dryWetLabel);

    //size
    configureKnobAndLabel (sizeKnob, sizeLabel, "Size");
    addAndMakeVisible (sizeKnob);
    //addAndMakeVisible (sizeLabel);

    //colour
    configureKnobAndLabel (colourKnob, colourLabel, "Colour");
    addAndMakeVisible (colourKnob);
    //addAndMakeVisible (colourLabel);

    //width
    /*
    configureKnobAndLabel (widthKnob, widthLabel, "Width");
    addAndMakeVisible (widthKnob);
    addAndMakeVisible (widthLabel);
     */

    //Speed aka Release
    configureKnobAndLabel (speedKnob, speedLabel, "Speed");
    addAndMakeVisible (speedKnob);
    //addAndMakeVisible (speedLabel);

    //Threshold
    configureKnobAndLabel (thresholdKnob, thresholdLabel, "Threshold / Ducking");
    addAndMakeVisible (thresholdKnob);
    //addAndMakeVisible (thresholdLabel);

    //labels placement
    dryWetLabel.toBehind (&dryWetKnob);
    sizeLabel.toBehind (&sizeKnob);
    colourLabel.toBehind (&colourKnob);
    // widthLabel.toBehind (&widthKnob);
    speedLabel.toBehind (&speedKnob);
    thresholdLabel.toBehind (&thresholdKnob);
}

void MainContainer::resized()
{
    auto knobSize = proportionOfWidth (0.17155f /*0.1716f*/);

    //knobs position
    dryWetKnob.setBounds (proportionOfWidth (0.07258f /*0.072575f*/), proportionOfHeight (0.3225f /* 0.32248f*/), knobSize, knobSize);
    sizeKnob.setBounds (proportionOfWidth (0.07347f /*0.073476f*/), proportionOfHeight (0.6259f /*0.6258f*/), knobSize, knobSize);
    colourKnob.setBounds (proportionOfWidth (0.21835f /*0.2183f*/), proportionOfHeight (0.47548f /*0.4755f*/), knobSize, knobSize);
    //widthKnob.setBounds (proportionOfWidth (0.1725f), proportionOfHeight (0.635f /*0.595f 0.64f 0.63f */), knobSize, knobSize);
    speedKnob.setBounds (proportionOfWidth (0.765f /*765025f*/), proportionOfHeight (0.4757f /*47556f*/), knobSize, knobSize);
    thresholdKnob.setBounds (proportionOfWidth (0.5927f /*0.593f*/), proportionOfHeight (0.475825f /*0.475825f*/), knobSize, knobSize);

    //labels
    auto labelOffset = -proportionOfHeight (0.01f);
    auto labelHeight = proportionOfHeight (0.03f);

    dryWetLabel.setBounds (dryWetKnob.getBounds().withY (dryWetKnob.getBottom() + labelOffset).withHeight (labelHeight));
    sizeLabel.setBounds (sizeKnob.getBounds().withY (sizeKnob.getBottom() + labelOffset).withHeight (labelHeight));
    colourLabel.setBounds (colourKnob.getBounds().withY (colourKnob.getBottom() + labelOffset).withHeight (labelHeight));
    //widthLabel.setBounds (widthKnob.getBounds().withY (widthKnob.getBottom() + labelOffset).withHeight (labelHeight));
    speedLabel.setBounds (speedKnob.getBounds().withY (speedKnob.getBottom() + labelOffset).withHeight (labelHeight));
    thresholdLabel.setBounds (thresholdKnob.getBounds().withY (thresholdKnob.getBottom() + labelOffset).withHeight (labelHeight));
}

void MainContainer::paint (juce::Graphics& g)
{
}

void MainContainer::configureKnobAndLabel (juce::Slider& knob, juce::Label& label, juce::String labelText)
{
    knob.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knob.setTextBoxStyle (juce::Slider::NoTextBox, true, 100, 25);
    knob.setColour (juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::turquoise);
    knob.setColour (juce::Slider::ColourIds::thumbColourId, juce::Colours::turquoise);

    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
}