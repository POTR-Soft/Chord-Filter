/*
  ==============================================================================

    MidiList.h
    Created: 13 Oct 2021 10:17:20am
    Author:  thmsr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MidiList {
public:
    std::vector<juce::MidiMessage> localMidilist;

    MidiList();
    bool isEmpty();
    void addToList(juce::MidiMessage msg);
    void deleteMessage(juce::MidiMessage msg);
    juce::MidiMessage retrieveMessageByIndex(int index);
    bool checkForDuplicates(juce::MidiMessage msg);
    int getIndexOfMessage(juce::MidiMessage msg);
    static  bool midiListComp(juce::MidiMessage& m1, juce::MidiMessage& m2);
    bool checkIfMessageInList(juce::MidiMessage msg);
};

