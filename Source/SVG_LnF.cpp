/*
  ==============================================================================

    SVG_LnF.cpp
    Created: 1 May 2022 11:14:20am
    Author:  Ryan Devens

  ==============================================================================
*/

#include "SVG_LnF.h"
#include "SliderSVG.h"

SVG_Lnf::SVG_Lnf()
{
    
}

SVG_Lnf::~SVG_Lnf()
{
    
}

void SVG_Lnf::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    if(dynamic_cast<SliderSVG*>(&slider) != nullptr)
    {
       // g.fillAll();
    }
}

void SVG_Lnf::drawLinearSliderBackground (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    if(dynamic_cast<SliderSVG*>(&slider) != nullptr)
    {
        DBG("test");
        auto bounds = juce::Rectangle<float>(x, y, width, height);
        g.setColour(juce::Colours::pink);
        g.fillRoundedRectangle(bounds, 2.f);
    }
}

void SVG_Lnf::drawLinearSliderThumb (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider& slider)
{
    
}
