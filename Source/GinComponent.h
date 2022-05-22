/*
  ==============================================================================

    GinComponent.h
    Created: 1 May 2022 8:37:57am
    Author:  Ryan Devens

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//==============================================================================
/*
 
*/
class GinComponent    : public juce::Component, public juce::FileDragAndDropTarget
{
public:
    GinComponent(juce::StringRef componentID);
    ~GinComponent();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;
    
    void saveToXml(juce::File& fileToWriteTo);
    void loadFromXml(juce::File& fileToLoadFrom);
    
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;
    
private:
    std::unique_ptr<juce::Label> xLabel;
    std::unique_ptr<juce::Label> yLabel;

    juce::Point<int> lastPos; // referenced in mouse drag and set in mouseUp
    
    bool hasDrawable = false;
    std::unique_ptr<juce::Drawable> drawable;
    
    // DATA THAT WILL BE STORED IN XML WHEN SAVED
    /*
        Hoping to extract most info from component class (bounds, position, etc.)
        But will make an external struct ComponentData if needed
    */
    juce::String _ID = {""};
    juce::String _DrawablePath = {"default"};
    juce::Colour _backgroundColour;
    //
    std::unique_ptr<juce::XmlElement> _getXml();
    void _updateDrawable(juce::StringRef filePath);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GinComponent)
};
