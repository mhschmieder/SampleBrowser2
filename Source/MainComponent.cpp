/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
	resizer(&layout, 1, true),
	samplesPane(formatManager, transportSource)
{
	LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
	layout.setItemLayout(0, -0.2, -0.8, -0.3);
	layout.setItemLayout(1, 5.0, 5.0, 5.0);
	layout.setItemLayout(2, -0.4, -0.8, -0.7);
	addAndMakeVisible(directoryPane);
	addAndMakeVisible(resizer);
	addAndMakeVisible(samplesPane);
	directoryPane.addListener(this);
    setSize (800, 600);
}

MainComponent::~MainComponent()
{
}

void MainComponent::resized()
{
	Component *comps[] = { &directoryPane, &resizer, &samplesPane };
	layout.layOutComponents(comps, 3, 0, 0, getWidth(), getHeight() - 22, false, true);
}

void MainComponent::selectionChanged(const File &file)
{
	samplesPane.selectionChanged(file);
}
