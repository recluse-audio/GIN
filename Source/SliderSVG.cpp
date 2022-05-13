/*
  ==============================================================================

    SliderSVG.cpp
    Created: 1 May 2022 10:31:27am
    Author:  Ryan Devens

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SliderSVG.h"

//==============================================================================
SliderSVG::SliderSVG()
{
    setSliderStyle(SliderStyle::LinearVertical);
    setTextBoxStyle(TextEntryBoxPosition::NoTextBox, true, 10, 10);
    
    lnf = std::make_unique<SVG_Lnf>();
    setLookAndFeel(lnf.get());
}

SliderSVG::~SliderSVG()
{
}


void SliderSVG::resized()
{


}

bool SliderSVG::isInterestedInFileDrag(const juce::StringArray& files)
{
    for(auto file : files)
    {
        if(file.contains(".svg"))
            return true;
    }
    
    return false;
}

void SliderSVG::filesDropped(const juce::StringArray& files, int x, int y)
{
    for(auto filePath : files)
    {
        if(isInterestedInFileDrag(filePath))
        {
            auto svgFile = juce::File(filePath);
            drawable = juce::Drawable::createFromSVGFile(svgFile);
            hasDrawable = true;
            repaint();
        }
    }
    
}
