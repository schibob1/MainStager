#include "PluginEditor.h"
#include "PluginProcessor.h"

#include <BinaryData.h>

//==============================================================================
MainStagerAudioProcessorEditor::MainStagerAudioProcessorEditor (MainStagerAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processorRef (p),
      backgroundImage (juce::Drawable::createFromImageData (BinaryData::background_jpg, BinaryData::background_jpgSize))
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 450);
}

MainStagerAudioProcessorEditor::~MainStagerAudioProcessorEditor()
{
}

//==============================================================================
void MainStagerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // draw background image
    backgroundImage->drawWithin (g, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, 0.5f);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MainStagerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
