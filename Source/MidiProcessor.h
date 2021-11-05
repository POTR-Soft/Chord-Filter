/*
  ==============================================================================

    MidiProcessor.h
    Created: 13 Oct 2021 12:38:27pm
    Author:  thmsr

  ==============================================================================
*/

#pragma once
#include "MidiList.h"
#include <JuceHeader.h>



class MidiProcessor
{
public:
	MidiProcessor();
	~MidiProcessor();
    void midiProcess(juce::MidiBuffer& buffer, const int sliderVal);

private:
    MidiList *myList;
    void addBufferToMidiList(juce::MidiBuffer& buffer);
    void filterNotesFromBuffer(juce::MidiBuffer& buffer, int sliderValue);
    void deleteOffNotesFromList(juce::MidiBuffer& buffer);
    void sortBuffer(juce::MidiBuffer& buffer);
    

};

