
/* Warnings relating to defines have been moved to this XC file to avoid multiple warnings being issued from the devicedefines.h header file */

#ifndef DEFAULT_FREQ
#warning DEFAULT_FREQ not defined. Using MIN_FREQ
#endif

#ifndef MIN_FREQ
#warning MIN_FREQ not defined. Using 44100
#endif

#ifndef MAX_FREQ
#warning MAX_FREQ not defined. Using 192000
#endif

#ifndef SPDIF_TX_INDEX
#warning SPDIF_TX_INDEX not defined! Using 0
#endif

#ifndef VENDOR_STR
#warning VENDOR_STR not defined. Using "XMOS"
#endif

#ifndef VENDOR_ID
#warning VENDOR_ID not defined. Using XMOS vendor ID (0x20B1)
#endif

#ifndef PRODUCT_STR_A2
#warning PRODUCT_STR_A2 not defined. Using default XMOS string
#endif

#ifndef PRODUCT_STR_A1
#warning PRODUCT_STR_A1 not defined. Using default XMOS string
#endif

#ifndef BCD_DEVICE
#warning BCD_DEVICE not defined. Using 0x0620
#endif

#if (AUDIO_CLASS==1) || defined(AUDIO_CLASS_FALLBACK)
#ifndef PID_AUDIO_1
#warning PID_AUDIO_1 not defined. Using 0x0003
#endif
#endif

#ifndef PID_AUDIO_2
#warning PID_AUDIO_2 not defined. Using 0x0002
#endif

#ifndef AUDIO_CLASS
#warning AUDIO_CLASS not defined, using 2
#endif

#ifndef AUDIO_CLASS_FALLBACK
#warning AUDIO_CLASS_FALLBACK not defined, using 0
#endif
