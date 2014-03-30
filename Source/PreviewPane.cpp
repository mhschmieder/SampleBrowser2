/*
  ==============================================================================

    PreviewPane.cpp
    Created: 29 Mar 2014 8:18:07am
    Author:  goodwin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PreviewPane.h"

//==============================================================================
PreviewPane::PreviewPane(AudioFormatManager &formatManager, AudioTransportSource &transportSource) :
	preview(formatManager, transportSource, zoomSlider),
	zoomSlider(Slider::LinearHorizontal, Slider::NoTextBox)
{
	addAndMakeVisible(preview);
	addAndMakeVisible(playButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(zoomSlider);

	playButton.setButtonText("Play");
	stopButton.setButtonText("Stop");
}

PreviewPane::~PreviewPane()
{
}

void PreviewPane::resized()
{
	preview.setBounds(2, 2, getWidth() - 4, getHeight() - 32);
	playButton.setBounds(2, getHeight() - 28, 70, 26);
	stopButton.setBounds(74, getHeight() - 28, 70, 26);
	zoomSlider.setBounds(getWidth() - 170, getHeight() - 28, 140, 26);
}
