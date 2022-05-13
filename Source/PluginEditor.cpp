/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LiveGUIAudioProcessorEditor::LiveGUIAudioProcessorEditor (LiveGUIAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p)
{

    svgComp = std::make_unique<SVGComponent>();
    addAndMakeVisible(svgComp.get());
    
    setSize (400, 300);
}

LiveGUIAudioProcessorEditor::~LiveGUIAudioProcessorEditor()
{
}

//==============================================================================
void LiveGUIAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void LiveGUIAudioProcessorEditor::resized()
{
    svgComp->setBoundsRelative(0.25f, 0.25f, 0.5f, 0.5f);
}
