/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
	thread("audio preview thread"),
	directoryPane(thread),
	resizer(&layout, 1, true),
	samplesPane(thread, formatManager, transportSource)
{
	LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
	deviceManager.initialise(2, 2, nullptr, true);
	deviceManager.addAudioCallback(&sourcePlayer);
	sourcePlayer.setSource(&transportSource);
	layout.setItemLayout(0, -0.2, -0.8, -0.3);
	layout.setItemLayout(1, 5.0, 5.0, 5.0);
	layout.setItemLayout(2, -0.4, -0.8, -0.7);
	addAndMakeVisible(directoryPane);
	addAndMakeVisible(resizer);
	addAndMakeVisible(samplesPane);
	directoryPane.addListener(this);
	formatManager.registerBasicFormats();

	loadOptions();

    setSize (800, 600);
}

MainComponent::~MainComponent()
{
	deviceManager.removeAudioCallback(&sourcePlayer);
	sourcePlayer.setSource(nullptr);
	transportSource.stop();
	transportSource.setSource(nullptr);
	saveOptions();
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

void MainComponent::loadOptions()
{
	PropertiesFile::Options options;

	options.applicationName = ProjectInfo::projectName;
	options.folderName = ProjectInfo::projectName;
	options.filenameSuffix = "settings";
	options.osxLibrarySubFolder = "Applications Support";
	applicationProperties.setStorageParameters(options);

	PropertiesFile *properties = applicationProperties.getUserSettings();

	String value = properties->getValue("numFavourites", "0");
	int numFavourites = value.getIntValue();
	for (int index = 0; index < numFavourites; index++)
	{
		value = properties->getValue(String("favourite") + String(index));
		directoryPane.addFavourite(value);
	}
}

void MainComponent::saveOptions()
{
	PropertiesFile *properties = applicationProperties.getUserSettings();

	StringArray favourites = directoryPane.getFavourites();
	properties->setValue("numFavourites", favourites.size());
	for (int index = 0; index < favourites.size(); index++)
	{
		properties->setValue(String("favourite") + String(index), favourites[index]);
	}
}
