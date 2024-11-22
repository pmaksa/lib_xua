#ifndef __MIDI_PROCESS_H
#define __MIDI_PROCESS_H

#ifdef __XC__
extern "C" {
#endif

void MidiProcess_UsbFromHost(unsigned midiData[], unsigned size);

#ifdef __XC__
}
#endif

#endif
