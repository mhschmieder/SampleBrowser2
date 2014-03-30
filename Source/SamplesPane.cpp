/*
  ==============================================================================

    SamplesPane.cpp
    Created: 29 Mar 2014 8:20:15am
    Author:  goodwin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SamplesPane.h"

//==============================================================================
SamplesPane::SamplesPane(AudioFormatManager &formatManager, AudioTransportSource &transportSource) :
	resizer(&layout, 1, false), 
	previewPane(formatManager, transportSource)
{
	layout.setItemLayout(0, -0.2, -0.8, -0.8);
	layout.setItemLayout(1, 5.0, 5.0, 5.0);
	layout.setItemLayout(2, -0.2, -0.8, -0.2);
	addAndMakeVisible(filesPane);
	addAndMakeVisible(resizer);
	addAndMakeVisible(previewPane);
}

SamplesPane::~SamplesPane()
{
}

void SamplesPane::resized()
{
	Component *comps[] = { &filesPane, &resizer, &previewPane };
	layout.layOutComponents(comps, 3, 0, 0, getWidth(), getHeight(), true, true);
}

void SamplesPane::selectionChanged(const File &file)
{
	filesPane.selectionChanged(file);
}
