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
PreviewPane::PreviewPane(TimeSliceThread &theThread, AudioFormatManager &theFormatManager, AudioTransportSource &theTransportSource) :
	thread(theThread),
	formatManager(theFormatManager),
	transportSource(theTransportSource),
	preview(formatManager, theTransportSource, zoomSlider),
	zoomSlider(Slider::LinearHorizontal, Slider::NoTextBox)
{
	addAndMakeVisible(preview);
	addAndMakeVisible(playButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(zoomSlider);

	playButton.setButtonText("Play");
	playButton.addListener(this);
	stopButton.setButtonText("Stop");
	stopButton.addListener(this);

	zoomSlider.setRange(0, 1, 0);
	zoomSlider.setSkewFactor(2);
	zoomSlider.addListener(this);
}

PreviewPane::~PreviewPane()
{
	current = nullptr;
}

void PreviewPane::resized()
{
	preview.setBounds(2, 2, getWidth() - 4, getHeight() - 32);
	playButton.setBounds(2, getHeight() - 28, 70, 26);
	stopButton.setBounds(74, getHeight() - 28, 70, 26);
	zoomSlider.setBounds(getWidth() - 170, getHeight() - 28, 140, 26);
}

void PreviewPane::setSampleFile(const File &file)
{
	preview.setFile(file);

	transportSource.stop();
	transportSource.setSource(nullptr);
	current = nullptr;

	AudioFormatReader *reader = formatManager.createReaderFor(file);
	if (reader)
	{
		current = new AudioFormatReaderSource(reader, true);
		transportSource.setSource(current, 32768, &thread, reader->sampleRate);
	}
}

void PreviewPane::buttonClicked(Button *button)
{
	if (button == &playButton)
	{
		playSample();
	}
	else if (button == &stopButton)
	{
		stopSample();
	}
}

void PreviewPane::playSample()
{
	if (!transportSource.isPlaying())
	{
		transportSource.setPosition(0);
		transportSource.start();
	}
}

void PreviewPane::stopSample()
{
	if (transportSource.isPlaying())
	{
		transportSource.stop();
	}
}

void PreviewPane::sliderValueChanged(Slider*)
{
	preview.setZoomFactor(zoomSlider.getValue());
}
