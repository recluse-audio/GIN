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


}

SliderSVG::~SliderSVG()
{
    setLookAndFeel(nullptr);
}

juce::Drawable* SliderSVG::getDrawable()
{
    return bkgd.get();
}

bool SliderSVG::hasBkgdDrawable()
{
    return hasDrawable;
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
            bkgd = juce::Drawable::createFromSVGFile(svgFile);
            hasDrawable = true;
            repaint();
        }
    }
    
}


