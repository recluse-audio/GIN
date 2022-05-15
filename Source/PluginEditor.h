/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GinComponent.h"
#include "SliderSVG.h"

//==============================================================================
/**
*/
class LiveGUIAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener
{
public:
    LiveGUIAudioProcessorEditor (LiveGUIAudioProcessor&);
    ~LiveGUIAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* b) override;
private:
    //std::unique_ptr<SVG_Lnf> lnf;

    std::unique_ptr<GinComponent> ginComp;
    std::unique_ptr<juce::TextButton> saveButton;
    std::unique_ptr<juce::TextButton> loadButton;
    std::unique_ptr<juce::FileChooser> fileChooser;
    //std::unique_ptr<SliderSVG> slider;

    void _runFileChooser(bool isSaving);
    
    LiveGUIAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LiveGUIAudioProcessorEditor)
};
