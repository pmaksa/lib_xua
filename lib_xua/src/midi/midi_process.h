#ifndef __MIDI_PROCESS_H
#define __MIDI_PROCESS_H

#ifdef __XC__
extern "C" {
#endif

#include <xccompat.h>

void usb_midi_process(chanend c_midi, unsigned cable_number);

#ifdef __XC__
}
#endif

#endif
