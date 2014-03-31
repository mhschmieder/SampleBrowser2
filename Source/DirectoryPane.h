/*
  ==============================================================================

    DirectoryPane.h
    Created: 29 Mar 2014 8:17:40am
    Author:  goodwin

  ==============================================================================
*/

#ifndef DIRECTORYPANE_H_INCLUDED
#define DIRECTORYPANE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class DirectoryPane : public Component, public FileBrowserListener, public ComboBox::Listener, public Button::Listener
{
public:
	class Listener
	{
	public:
		virtual void selectionChanged(const File &file) = 0;
	};

    DirectoryPane(TimeSliceThread &theThread);
    virtual ~DirectoryPane();

    void resized() override;

	void selectionChanged() override;
	void fileClicked(const File &, const MouseEvent &) override { }
	void fileDoubleClicked(const File &) override { }
	void browserRootChanged(const File &) override { }
	void comboBoxChanged(ComboBox *comboBox) override;
	void buttonClicked(Button *button) override;

	void addListener(Listener *listener);

private:
	File currentPath;
	ComboBox directoryField;
	TextButton browseButton;
	TextButton upButton;
	TextButton favouritesButton;
	TimeSliceThread &thread;
	DirectoryContentsList directoryContents;
	FileTreeComponent fileTree;
	Array<Listener *> listeners;

	void notifyListeners(const File &file);
	void upPath();
	void browsePath();
	void addFavourites();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirectoryPane)
};


#endif  // DIRECTORYPANE_H_INCLUDED
