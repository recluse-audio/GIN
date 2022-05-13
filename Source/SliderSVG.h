/*
  ==============================================================================

    SliderSVG.h
    Created: 1 May 2022 10:31:27am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SVG_LnF.h"

//==============================================================================
/*
*/
class SliderSVG  : public juce::Slider, public juce::FileDragAndDropTarget
{
public:
    SliderSVG();
    ~SliderSVG() override;

    //void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;
    
private:
    bool hasDrawable = false;
    std::unique_ptr<juce::Drawable> drawable;
    std::unique_ptr<SVG_Lnf> lnf;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderSVG)
};
