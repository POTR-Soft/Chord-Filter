/*
  ==============================================================================

    MidiProcessing.h
    Created: 13 Oct 2021 10:17:40am
    Author:  thmsr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


#include "MidiList.h"

class MidiProcessing {
    // std::list<juce::MidiMessage> myList;
    MidiList myList;
public:
    void midiProcess(juce::MidiBuffer& buffer, const int sliderVal) {

        juce::MidiBuffer localBuffer;
        juce::MidiBuffer tmpBuffer;

        localBuffer.clear();
        tmpBuffer.clear();

        //copy values to Local Buffer
        localBuffer.swapWith(buffer);
        buffer.clear();

        //Copy Messages to MidiList
        addMessagesToMidiList(localBuffer);

        
        //creating buffer for final
        chooseNoteFromList(localBuffer, tmpBuffer, sliderVal);

        buffer.swapWith(tmpBuffer);


    }


    void chooseNoteFromList(juce::MidiBuffer& firstBuffer, juce::MidiBuffer& secondBuffer, const int index)
    {
        for(const auto msg: firstBuffer)
        {
            if (msg.getMessage().isNoteOn())
            {
                if (msg.getMessage().getNoteNumber() == myList.retrieveMessageByIndex(index).getNoteNumber())
                {
                    secondBuffer.addEvent(msg.getMessage(), msg.samplePosition);
                }
            }
            else if (msg.getMessage().isNoteOff())
            {
                myList.deleteMessage(msg.getMessage());
                secondBuffer.addEvent(msg.getMessage(), msg.samplePosition);
            }
            else
            {
                secondBuffer.addEvent(msg.getMessage(), msg.samplePosition);
            }

        }
    }



   /**
    * .
    * 
    * \param midiBuffer
    */
    void addMessagesToMidiList(juce::MidiBuffer& midiBuffer)
    {
        for (const auto msg : midiBuffer)
        {
            if (msg.getMessage().isNoteOn())
            {
                myList.addToList(msg.getMessage());
            }
            

        }
    }
    

};

