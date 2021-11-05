/*
  ==============================================================================

	MidiProcessor.cpp
	Created: 13 Oct 2021 12:38:27pm
	Author:  thmsr

  ==============================================================================
*/

#include "MidiProcessor.h"
#include <JuceHeader.h>

/**
 * @brief Construct a new Midi Processor:: Midi Processor object
 * 
 */
MidiProcessor::MidiProcessor()
{
	myList = new MidiList();
}

/**
 * @brief Destroy the Midi Processor:: Midi Processor object
 * 
 */
MidiProcessor::~MidiProcessor()
{
}

/**
 * @brief Processes midi events
 * 
 * @param buffer Midi Buffer
 * @param sliderVal Value of GUI slider
 */

void MidiProcessor::midiProcess(juce::MidiBuffer& buffer, const int sliderVal)
{
	juce::MidiBuffer localBuffer;
	


	//Clearing buffers
	localBuffer.clear();
	

	//Writing all Messages to first locl buffer
	localBuffer.swapWith(buffer);
	buffer.clear();

    //Sort Buffer first off events theb on
    sortBuffer(localBuffer);
    
	//Add all NoteOn Messages to Midilist
	addBufferToMidiList(localBuffer);
	//Deleting all notes with value off
	deleteOffNotesFromList(localBuffer);

	//Iterate over Buffer and Filter Notes which are not picked by the algorithm
	filterNotesFromBuffer(localBuffer, sliderVal);

	

	//delete offnotes
	deleteOffNotesFromList(localBuffer);

	

	//swap buffers
	buffer.swapWith(localBuffer);

}

/**
 * @brief Adds alle noteOn events to the Midilist
 * 
 * @param buffer Midibuffer
 */

void MidiProcessor::addBufferToMidiList(juce::MidiBuffer& buffer)
{
	for (const auto msg : buffer
		) {
		if (msg.getMessage().isNoteOn())
		{
			myList->addToList(msg.getMessage());
		}
	}
}

/**
 * @brief Filters the midibuffer according to the slider value
 *  
 *
 * @param buffer 
 * @param sliderValue 
 */

void MidiProcessor::filterNotesFromBuffer(juce::MidiBuffer& buffer, int sliderValue)
{

	juce::MidiBuffer tmpBuffer;
	tmpBuffer.clear();

	for (const auto msg : buffer) {

		if (msg.getMessage().isNoteOn())
		{

			// Nested loop ensures that notes are in midilist. Will be deleted with next fix
			addBufferToMidiList(buffer);

			//Checks is note is the choosen note of the Algorithm
  			if (!myList->isEmpty()) {
				if (msg.getMessage().getNoteNumber() == myList->retrieveMessageByIndex(sliderValue).getNoteNumber())
				{
					tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);
				}

			}
			else {
				myList->addToList(msg.getMessage());
				tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);
			}

		}
		else
		{
			tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);
		}
	}

	//swaping filtered buffer
	buffer.swapWith(tmpBuffer);
}

/**
 * @brief Deletes notes from Midilist
 * 
 * @param buffer 
 */

void MidiProcessor::deleteOffNotesFromList(juce::MidiBuffer& buffer)
{

	juce::MidiBuffer tmpBuffer;
	tmpBuffer.clear();

	for (const auto msg : buffer) {
		if (msg.getMessage().isNoteOff())
		{
			if (!myList->isEmpty())
			{
				myList->deleteMessage(msg.getMessage());
			}
		}
		tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);

	}

	buffer.swapWith(tmpBuffer);
}



/// <#Description#>
/// @param buffer <#buffer description#>
void MidiProcessor::sortBuffer(juce::MidiBuffer &buffer) { 
    juce::MidiBuffer onBuffer;
    juce::MidiBuffer offBuffer;
    juce::MidiBuffer otherBuffer;
    juce::MidiBuffer tmpBuffer;
    
    onBuffer.clear();
    offBuffer.clear();
    otherBuffer.clear();
    tmpBuffer.clear();
    
    
    for(const auto msg: buffer){
        if(msg.getMessage().isNoteOn()){
            onBuffer.addEvent(msg.getMessage(), msg.samplePosition);
        }
        else if(msg.getMessage().isNoteOff()){
            offBuffer.addEvent(msg.getMessage(), msg.samplePosition);
        }
        else
        {
            otherBuffer.addEvent(msg.getMessage(), msg.samplePosition);
        }
    }
    
    for(const auto msg: offBuffer)
    {
        tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);
    }
    
    for(const auto msg: onBuffer)
    {
        tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);
    }
    
    for(const auto msg: otherBuffer)
    {
        tmpBuffer.addEvent(msg.getMessage(), msg.samplePosition);
    }
    
    buffer.swapWith(tmpBuffer);
    
    
}



