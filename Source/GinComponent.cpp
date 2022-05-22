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
    _backgroundColour = juce::Colours::red.withAlpha(0.1f);
    
    xLabel = std::make_unique<juce::Label>();
    addAndMakeVisible(xLabel.get());
    
    yLabel = std::make_unique<juce::Label>();
    addAndMakeVisible(yLabel.get());
    
    
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
    xLabel->setBoundsRelative(0.f, 0.8f, 0.4f, 0.2f);
    yLabel->setBoundsRelative(0.5f, 0.8f, 0.4f, 0.2f);
}

void GinComponent::mouseDrag(const juce::MouseEvent& e)
{
    // always starts by jumping to top left (0,0) and don't know why
    int xOffset = e.getDistanceFromDragStartX();
    int yOffset = e.getDistanceFromDragStartY();

    auto bounds = getBoundsInParent();
                       
    int xPos = lastPos.getX() + xOffset;
    xPos = juce::jlimit<int>(0, getParentWidth() - bounds.getWidth(), xPos);
    xLabel->setText(juce::String(xPos), juce::dontSendNotification);
    
    int yPos = lastPos.getY() + yOffset;
    yPos = juce::jlimit<int>(0, getParentHeight() - bounds.getHeight(), yPos);
    yLabel->setText(juce::String(yPos), juce::dontSendNotification);

    this->setBounds(xPos, yPos, getWidth(), getHeight());
}

void GinComponent::mouseUp(const juce::MouseEvent& e)
{
    lastPos.setXY(getBoundsInParent().getX(), getBoundsInParent().getY());
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
    lastPos.setXY(x, y);
    
    // COLOR
    const int r = xml->getIntAttribute("red");
    const int g = xml->getIntAttribute("green");
    const int b = xml->getIntAttribute("blue");
    const int a = xml->getIntAttribute("alpha");
    
    _backgroundColour = juce::Colour::fromRGBA(r, g, b, a);
    
    repaint();
    
    // DRAWABLE
    hasDrawable = xml->getBoolAttribute("hasDrawable");
    if(hasDrawable)
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
    rootXml->setAttribute("Y",      bounds.getY());
    rootXml->setAttribute("Width",  bounds.getWidth());
    rootXml->setAttribute("Height", bounds.getHeight());
    
    // COLORS
    rootXml->setAttribute("red",    _backgroundColour.getRed());
    rootXml->setAttribute("green",  _backgroundColour.getGreen());
    rootXml->setAttribute("blue",   _backgroundColour.getBlue());
    rootXml->setAttribute("alpha",  _backgroundColour.getAlpha());
    
    // DRAWABLES
    rootXml->setAttribute("hasDrawable", hasDrawable);
    rootXml->setAttribute("drawablePath", _DrawablePath);
    
    return rootXml;
}
