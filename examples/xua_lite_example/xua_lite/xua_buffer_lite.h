#include <xs1.h>
#include "xua_ep0_wrapper.h"
#include "xua.h"

//Currently only single frequency supported
#define NOMINAL_SR_DEVICE                 DEFAULT_FREQ
#define NOMINAL_SR_HOST                   DEFAULT_FREQ

#define DIV_ROUND_UP(n, d) (n / d + 1)  //Always rounds up to the next integer. Needed for 48001Hz case etc.
#define BIGGEST(a, b) (a > b ? a : b)

#define SOF_FREQ_HZ                       (8000 - ((2 - AUDIO_CLASS) * 7000) ) //1000 for FS or 8000 for HS

//Defines for endpoint buffer sizes. Samples is total number of samples across all channels
#define MAX_OUT_SAMPLES_PER_SOF_PERIOD    (DIV_ROUND_UP(MAX_FREQ, SOF_FREQ_HZ) * NUM_USB_CHAN_OUT)
#define MAX_IN_SAMPLES_PER_SOF_PERIOD     (DIV_ROUND_UP(MAX_FREQ, SOF_FREQ_HZ) * NUM_USB_CHAN_IN)
#define MAX_OUTPUT_SLOT_SIZE              4
#define MAX_INPUT_SLOT_SIZE               4

#define OUT_AUDIO_BUFFER_SIZE_BYTES       (MAX_OUT_SAMPLES_PER_SOF_PERIOD * MAX_OUTPUT_SLOT_SIZE)
#define IN_AUDIO_BUFFER_SIZE_BYTES        (MAX_IN_SAMPLES_PER_SOF_PERIOD * MAX_INPUT_SLOT_SIZE)

unsafe void XUA_Buffer_lite(chanend c_ep0_out, chanend c_ep0_in, chanend c_aud_out, chanend ?c_feedback, chanend c_aud_in, chanend c_sof, in port p_for_mclk_count, streaming chanend c_audio_hub);
[[combinable]]
unsafe void XUA_Buffer_lite2(server ep0_control_if i_ep0_ctl, chanend c_aud_out, chanend ?c_feedback, chanend c_aud_in, chanend c_sof, in port p_for_mclk_count, streaming chanend c_audio_hub);

/** Transfer samples to/from XUA. Should be called at the current USB rate.
 * This function is non-blocking.
 *
 * \param[in,out] c_audio               Channel to XUA.
 *
 * \param[out] sampsFromUsbToAudio      Samples sent from host to device.
 *
 * \param[in] sampsFromAudioToUsb       Samples to send from device to host.
 *
 * \param[out] clock_nudge              Notification that the device is running
 *                                      too slowly/quickly. Only used when in
 *                                      adaptive endpoint mode.
 */
static inline void XUA_transfer_samples(streaming chanend c_audio,
                                        unsigned sampsFromUsbToAudio[],
                                        unsigned sampsFromAudioToUsb[],
                                        int &clock_nudge) {
    //Transfer samples. Takes about 25 ticks
    for (int i = 0; i < NUM_USB_CHAN_OUT; i++) c_audio :> sampsFromUsbToAudio[i];
    if (XUA_ADAPTIVE) c_audio :> clock_nudge;
    for (int i = 0; i < NUM_USB_CHAN_IN; i++) c_audio <: sampsFromAudioToUsb[i];
}