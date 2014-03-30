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
	addAndMakeVisible(browseButton);
	addAndMakeVisible(upButton);
	addAndMakeVisible(fileTree);

	browseButton.setButtonText("...");
	upButton.setButtonText("Up");

	currentPath = File::getSpecialLocation(File::userDocumentsDirectory);
	directoryField.setText(currentPath.getFullPathName(), false);
	directoryContents.setDirectory(currentPath, true, false);
	thread.startThread(3);

	fileTree.addListener(this);
	directoryField.addListener(this);
}

DirectoryPane::~DirectoryPane()
{
}

void DirectoryPane::resized()
{
	directoryField.setBounds(2, 2, getWidth() - 80, 24);
	browseButton.setBounds(getWidth() - 66, 2, 30, 24);
	upButton.setBounds(getWidth() - 32, 2, 30, 24);
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

void DirectoryPane::textEditorReturnKeyPressed(TextEditor &textEditor)
{
	currentPath = directoryField.getText();
	directoryContents.setDirectory(currentPath, true, false);
}
