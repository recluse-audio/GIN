/*
  ==============================================================================

    SVG_LnF.h
    Created: 1 May 2022 11:14:20am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class SVG_Lnf : public juce::LookAndFeel_V4
{
public:
    SVG_Lnf();
    ~SVG_Lnf();
    
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider& slider) override ;
    
    void drawLinearSliderBackground (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle style, juce::Slider & slider) override;
    
    void drawLinearSliderThumb (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const juce::Slider::SliderStyle, juce::Slider& slider) override;
};
