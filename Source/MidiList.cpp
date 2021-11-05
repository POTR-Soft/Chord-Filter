/*
  ==============================================================================

    MidiList.cpp
    Created: 13 Oct 2021 10:17:20am
    Author:  thmsr

  ==============================================================================
*/

#include "MidiList.h"
/***
 * Compares two Midi Mesages
 * @param m1 juce::MidiMessage
 * @param m2 juce::MidiMessage
 * @return
 */
bool MidiList::midiListComp(juce::MidiMessage& m1, juce::MidiMessage& m2) {
    return m1.getNoteNumber() < m2.getNoteNumber();
}



/***
 * Gets Index of MidiMessage in Vector
 * @param msg Midimessage
 * @return Index of Message
 */
int MidiList::getIndexOfMessage(juce::MidiMessage msg) {
    int index = 0;
    for (const auto tmp : localMidilist) {
        if (msg.getNoteNumber() == tmp.getNoteNumber())
            break;
        index++;
    }
    return index;
}


/***
 * Checks if MidiMessage is in List
 * @param msg Midi Message
 * @return bool
 */

bool MidiList::checkIfMessageInList(juce::MidiMessage msg) {

    for (auto tmp : localMidilist) {
        if (tmp.getNoteNumber() == msg.getNoteNumber())
            return true;
    }

    return false;

}

/***
 * True if list is empty
 * @return
 */
bool MidiList::isEmpty() {
    return localMidilist.empty();
}

/***
 * Checks if NoteNumber is already in List
 * @param msg juce::MidiMessage
 * @return True or False
 */
bool MidiList::checkForDuplicates(juce::MidiMessage msg) {
    for (const auto tmpMsg : localMidilist) {
        if (tmpMsg.getNoteNumber() == msg.getNoteNumber())
            return true;
    }
    return false;
}


/***
 * Adding item to list (sorted)
 * @param msg juce::MidiMessage
 */
void MidiList::addToList(juce::MidiMessage msg) {

    if (!checkForDuplicates(msg))
        localMidilist.push_back(msg);

    std::sort(localMidilist.begin(), localMidilist.end(), midiListComp);
}

MidiList::MidiList()
{
    localMidilist.clear();
}

/***
 * Gets note by Index
 * @param index index of note
 * @return juce::MidiMessage
 */
juce::MidiMessage MidiList::retrieveMessageByIndex(int index) {
   

    
       if (index >= localMidilist.size()) {
            
           int tmp = localMidilist.size() - 1;
           return localMidilist.at(tmp);

    }
     return localMidilist.at(index);
}

/***
 * deletes message from list
 * @param msg juce::MidiMessage
 */

void MidiList::deleteMessage(juce::MidiMessage msg) {


    std::vector<juce::MidiMessage> tmplMidilist;

    tmplMidilist.clear();

    for (const auto lclmsg : localMidilist) {
        if (msg.getNoteNumber() != lclmsg.getNoteNumber())
            tmplMidilist.push_back(lclmsg);
    }

   
    localMidilist.swap(tmplMidilist);

    //sorting 
    std::sort(localMidilist.begin(), localMidilist.end(), midiListComp);

  

}


