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

    auto bounds = juce::Rectangle<float>(x, y, width/2, height);

    g.setColour(juce::Colours::red);
    g.fillRoundedRectangle(bounds, 2.f);
    
    if(dynamic_cast<SliderSVG*>(&slider) != nullptr)
    {
        g.setColour(juce::Colours::green);
        g.fillRoundedRectangle(bounds, 2.f);
    }
    
    drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);

}

void SVG_Lnf::drawLinearSliderBackground (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, y, width, height);

    g.setColour(juce::Colours::yellow);
    g.fillRoundedRectangle(bounds, 2.f);
    
    if(dynamic_cast<SliderSVG*>(&slider) != nullptr)
    {
        g.setColour(juce::Colours::blue);
        g.fillRoundedRectangle(bounds, 2.f);
    }
}

void SVG_Lnf::drawLinearSliderThumb (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float>(x, sliderPos, width, 2.f);

    g.setColour(juce::Colours::orange);
    g.fillRoundedRectangle(bounds, 2.f);
    
    if(dynamic_cast<SliderSVG*>(&slider) != nullptr)
    {
        g.setColour(juce::Colours::yellow);
        g.fillRoundedRectangle(bounds, 2.f);
    }
}
