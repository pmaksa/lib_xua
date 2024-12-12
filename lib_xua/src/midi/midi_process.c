#include "midi_process.h"


int __usb_midi_process_overloaded__ = 1;

__attribute__((weak)) void usb_midi_process(chanend c_midi, unsigned cable_number) {
    __usb_midi_process_overloaded__ = 0;
}