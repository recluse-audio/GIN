/*
  ==============================================================================

    GinComponent.cpp
    Created: 1 May 2022 8:37:57am
    Author:  Ryan Devens

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "GinComponent.h"
#include "ComponentData.h"


//==============================================================================
GinComponent::GinComponent(juce::StringRef componentID)
{
    setComponentID(componentID);
    _backgroundColour = juce::Colours::aqua.withAlpha(0.2f);
}

GinComponent::~GinComponent()
{
}

void GinComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour(_backgroundColour);
    g.fillRoundedRectangle(bounds, 2.f);
    
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds, 2.f, 2.f);
    
    if(drawable != nullptr)
    {
        drawable->setTransformToFit(bounds, juce::RectanglePlacement::centred);
        drawable->drawAt(g, 0, 0, 1.f);
    }

    

}

void GinComponent::resized()
{

}

void GinComponent::mouseDrag(const juce::MouseEvent& e)
{
    int xOffset = e.getDistanceFromDragStartX();
    int yOffset = e.getDistanceFromDragStartY();
    
    auto bounds = getLocalBounds();

    int xPos = bounds.getX() + xOffset;
    xPos = juce::jlimit<int>(0, getParentWidth() - bounds.getWidth(), xPos);
    
    int yPos = bounds.getY() + yOffset;
    yPos = juce::jlimit<int>(0, getParentWidth() - bounds.getWidth(), yPos);
    
    this->setBounds(xPos, yPos, getWidth(), getHeight());
}

bool GinComponent::isInterestedInFileDrag(const juce::StringArray& files)
{
    for(auto file : files)
    {
        if(file.contains(".svg"))
            return true;
    }
    
    return false;
}

void GinComponent::filesDropped(const juce::StringArray& files, int x, int y)
{
    for(auto filePath : files)
    {
        if(isInterestedInFileDrag(filePath))
        {
            _updateDrawable(filePath);
        }
    }
    
}

void GinComponent::_updateDrawable(juce::StringRef filePath)
{
    auto svgFile = juce::File(filePath);
    drawable = juce::Drawable::createFromSVGFile(svgFile);
    _DrawablePath = filePath;
    hasDrawable = true;
    repaint();
}
void GinComponent::saveToXml(juce::File& fileToWriteTo)
{
    auto xml = _getXml();
    xml->writeTo(fileToWriteTo);
}

void GinComponent::loadFromXml(juce::File& fileToLoadFrom)
{
    juce::XmlDocument xmlDoc(fileToLoadFrom);
    auto xml = xmlDoc.getDocumentElement();
    
    // ID
    setComponentID(xml->getStringAttribute("componentName"));

    // BOUNDS
    int x = xml->getIntAttribute("X");
    int y = xml->getIntAttribute("Y");
    int w = xml->getIntAttribute("Width");
    int h = xml->getIntAttribute("Height");
    
    this->setBounds(x, y, w, h);
    
    // COLOR
    const int r = xml->getIntAttribute("red");
    const int g = xml->getIntAttribute("green");
    const int b = xml->getIntAttribute("blue");
    
    _backgroundColour = juce::Colour(r, g, b);
    repaint();
    
    // DRAWABLE
    hasDrawable = xml->getBoolAttribute("hasDrawable");
    _updateDrawable(xml->getStringAttribute("drawablePath"));
    
}


std::unique_ptr<juce::XmlElement> GinComponent::_getXml()
{
    // I wanted to do this using elements but couldn't get it working
    // ROOT NODE
    auto rootXml = std::make_unique<juce::XmlElement>("Root");
    rootXml->setAttribute("componentName", getComponentID());
    
    // BOUNDS
    auto bounds =  getBoundsInParent();
    rootXml->setAttribute("X",      bounds.getX());
    rootXml->setAttribute("Y",      bounds.getX());
    rootXml->setAttribute("Width",  bounds.getWidth());
    rootXml->setAttribute("Height", bounds.getHeight());
    
    // COLORS
    rootXml->setAttribute("red", _backgroundColour.getRed());
    rootXml->setAttribute("green", _backgroundColour.getGreen());
    rootXml->setAttribute("blue", _backgroundColour.getBlue());
    
    // DRAWABLES
    rootXml->setAttribute("hasDrawable", hasDrawable);
    rootXml->setAttribute("drawablePath", _DrawablePath);
    
    return rootXml;
}
