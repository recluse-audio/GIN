/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LiveGUIAudioProcessorEditor::LiveGUIAudioProcessorEditor (LiveGUIAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p)
{
//    lnf = std::make_unique<SVG_Lnf>();
//    setLookAndFeel(lnf.get());
    
    ginComp = std::make_unique<GinComponent>("Main Picture");
    addAndMakeVisible(ginComp.get());
    
    saveButton = std::make_unique<juce::TextButton>("Save Button");
    saveButton->addListener(this);
    addAndMakeVisible(saveButton.get());
    
    loadButton = std::make_unique<juce::TextButton>("Load Button");
    loadButton->addListener(this);
    addAndMakeVisible(loadButton.get());
    
//    slider = std::make_unique<SliderSVG>();
//    addAndMakeVisible(slider.get());
//    slider->setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
//    slider->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 40, 10);

    
    setSize (400, 300);
}

LiveGUIAudioProcessorEditor::~LiveGUIAudioProcessorEditor()
{
}

//==============================================================================
void LiveGUIAudioProcessorEditor::paint (juce::Graphics& g)
{

}

void LiveGUIAudioProcessorEditor::resized()
{
    ginComp->setBoundsRelative(0.25f, 0.25f, 0.5f, 0.5f);
    saveButton->setBoundsRelative(0.8f, 0.1f, 0.15f, 0.05f);
    loadButton->setBoundsRelative(0.05f, 0.1f, 0.15f, 0.05f);
    //slider->setBoundsRelative(0.1f, 0.25f, 0.1f, 0.5f);

}

void LiveGUIAudioProcessorEditor::buttonClicked(juce::Button* b)
{
    if(b == saveButton.get())
    {
        _runFileChooser(true);
    }
    if(b == loadButton.get())
    {
        _runFileChooser(false);
    }
}

void LiveGUIAudioProcessorEditor::_runFileChooser(bool isSaving)
{
    fileChooser = std::make_unique<juce::FileChooser>
    ("Save your XML baby!!!", juce::File{});
    
    int chooserFlags;
    
    if(isSaving)
    {
        chooserFlags = juce::FileBrowserComponent::FileChooserFlags::saveMode |
        juce::FileBrowserComponent::FileChooserFlags::canSelectFiles;

        fileChooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
        {
            auto fileToWriteTo = fc.getResult();
            // if this is not already a file I think?
            if (fileToWriteTo != juce::File{})
            {
                ginComp->saveToXml(fileToWriteTo);
            }
        });
    }
    else
    {
        chooserFlags = juce::FileBrowserComponent::FileChooserFlags::openMode |
        juce::FileBrowserComponent::FileChooserFlags::canSelectFiles;
        
        fileChooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
        {
            auto fileToLoad = fc.getResult();

            ginComp->loadFromXml(fileToLoad);
            
        });
    }
    

}
