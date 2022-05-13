/*
  ==============================================================================

    SVGComponent.h
    Created: 1 May 2022 8:37:57am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SVGComponent    : public juce::Component, public juce::FileDragAndDropTarget
{
public:
    SVGComponent();
    ~SVGComponent();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;
    
private:
    bool hasDrawable = false;
    std::unique_ptr<juce::Drawable> drawable;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SVGComponent)
};
