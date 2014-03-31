/*
  ==============================================================================

    DirectoryPane.cpp
    Created: 29 Mar 2014 8:17:40am
    Author:  goodwin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DirectoryPane.h"

//==============================================================================
DirectoryPane::DirectoryPane(TimeSliceThread &theThread) : thread(theThread), directoryContents(nullptr, thread), fileTree(directoryContents)
{
	addAndMakeVisible(directoryField);
	addAndMakeVisible(favouritesButton);
	addAndMakeVisible(browseButton);
	addAndMakeVisible(upButton);
	addAndMakeVisible(fileTree);

	browseButton.setButtonText("...");
	upButton.setButtonText("Up");
	favouritesButton.setButtonText("+");

	directoryField.setEditableText(true);
	currentPath = File::getSpecialLocation(File::userDocumentsDirectory);
	directoryField.setText(currentPath.getFullPathName(), dontSendNotification);
	directoryContents.setDirectory(currentPath, true, false);
	thread.startThread(3);

	browseButton.addListener(this);
	upButton.addListener(this);
	favouritesButton.addListener(this);
	fileTree.addListener(this);
	directoryField.addListener(this);
}

DirectoryPane::~DirectoryPane()
{
}

void DirectoryPane::resized()
{
	directoryField.setBounds(2, 2, getWidth() - 100, 24);
	browseButton.setBounds(getWidth() - 96, 2, 30, 24);
	upButton.setBounds(getWidth() - 64, 2, 30, 24);
	favouritesButton.setBounds(getWidth() - 32, 2, 30, 24);
	fileTree.setBounds(2, 26, getWidth() - 4, getHeight() - 28);
}

void DirectoryPane::selectionChanged()
{
	File file = fileTree.getSelectedFile();
	notifyListeners(file);
}

void DirectoryPane::addListener(Listener *listener)
{
	listeners.add(listener);
}

void DirectoryPane::notifyListeners(const File &file)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->selectionChanged(file);
	}
}

void DirectoryPane::comboBoxChanged(ComboBox *)
{
	currentPath = directoryField.getText();
	directoryContents.setDirectory(currentPath, true, false);
}

void DirectoryPane::buttonClicked(Button *button)
{
	if (button == &upButton)
	{
		upPath();
	}
	else if (button == &browseButton)
	{
		browsePath();
	}
	else if (button == &favouritesButton)
	{
		addFavourites();
	}
}

void DirectoryPane::upPath()
{
	currentPath = currentPath.getParentDirectory();
	directoryField.setText(currentPath.getFullPathName(), dontSendNotification);
	directoryContents.setDirectory(currentPath, true, false);
}

void DirectoryPane::browsePath()
{
	FileBrowserComponent browser(FileBrowserComponent::canSelectDirectories | FileBrowserComponent::openMode, currentPath, nullptr, nullptr);
	FileChooserDialogBox dialog("Select path", String::empty, browser, false, Colours::lightgrey);
	if (dialog.show())
	{
		currentPath = browser.getSelectedFile(0);
		directoryField.setText(currentPath.getFullPathName(), dontSendNotification);
		directoryContents.setDirectory(currentPath, true, false);
	}
}

void DirectoryPane::addFavourites()
{
	addFavourite(directoryField.getText());
}

void DirectoryPane::addFavourite(StringRef favourite)
{
	int id = directoryField.getNumItems() + 1;
	directoryField.addItem(favourite.text, id);
}

StringArray DirectoryPane::getFavourites()
{
	StringArray result;
	int numFavourites = directoryField.getNumItems();
	for (int i = 0; i < numFavourites; i++)
	{
		String value = directoryField.getItemText(i);
		result.add(value);
	}
	return result;
}
