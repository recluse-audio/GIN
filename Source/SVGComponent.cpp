/*
  ==============================================================================

    SVGComponent.cpp
    Created: 1 May 2022 8:37:57am
    Author:  Ryan Devens

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SVGComponent.h"

//==============================================================================
SVGComponent::SVGComponent()
{
    auto svgFile = juce::File("/MacintoshHD/Users/ryandevens/desktop/BTN On.svg");
    drawable = juce::Drawable::createFromSVGFile(svgFile);
}

SVGComponent::~SVGComponent()
{
}

void SVGComponent::paint (juce::Graphics& g)
{
    if(hasDrawable)
    {
        drawable->setTransformToFit(getLocalBounds().toFloat(), juce::RectanglePlacement::centred);
        drawable->drawAt(g, 0, 0, 1.f);
    }

    
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 2.f, 2.f);
}

void SVGComponent::resized()
{

}

bool SVGComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    for(auto file : files)
    {
        if(file.contains(".svg"))
            return true;
    }
    
    return false;
}

void SVGComponent::filesDropped(const juce::StringArray& files, int x, int y)
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
