#ifndef _SAMPLEMODEL_H
#define _SAMPLEMODEL_H

#include "../JuceLibraryCode/JuceHeader.h"

class SampleModel
{
public:
	SampleModel(StringRef theName, StringRef theFilename);

	String getName() const { return name; }
	String getFilename() const { return filename; }
	int getSampleRate() const { return sampleRate; }
	int getChannels() const { return channels; }
	int getBits() const { return bits; }
	int getSize() const { return size; }

	void setSampleRate(int value);
	void setChannels(int value);
	void setBits(int value);
	void setSize(int value);

private:
	String name;
	String filename;
	int sampleRate;
	int channels;
	int bits;
	int size;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleModel)
};

#endif // _SAMPLEMODEL_H
