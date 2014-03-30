#include "SampleModel.h"

SampleModel::SampleModel(StringRef theName, StringRef theFilename)
{
	name = theName.text;
	filename = theFilename.text;
	sampleRate = 0;
	channels = 0;
	bits = 0;
	size = 0;
}

void SampleModel::setSampleRate(int value)
{
	sampleRate = value;
}

void SampleModel::setChannels(int value)
{
	channels = value;
}

void SampleModel::setBits(int value)
{
	bits = value;
}

void SampleModel::setSize(int value)
{
	size = value;
}


