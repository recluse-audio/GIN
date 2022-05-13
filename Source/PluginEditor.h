/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SVGComponent.h"

//==============================================================================
/**
*/
class LiveGUIAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LiveGUIAudioProcessorEditor (LiveGUIAudioProcessor&);
    ~LiveGUIAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    std::unique_ptr<SVGComponent> svgComp;
    LiveGUIAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveGUIAudioProcessorEditor)
};
