#pragma once

#include <processor/PluginProcessor.h>
#include "MainContainer.h"

//==============================================================================
class MainStagerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit MainStagerAudioProcessorEditor (MainStagerAudioProcessor&);
    ~MainStagerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MainStagerAudioProcessor& processorRef;

    // main container
    MainContainer mainContainer;

    // background image
    std::unique_ptr<juce::Drawable> backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainStagerAudioProcessorEditor)
};
