#ifndef __PEAK_CONTROL_H_3A46CB93_D11D_4EBE_A4CD_6A652FEBAF88__
#define __PEAK_CONTROL_H_3A46CB93_D11D_4EBE_A4CD_6A652FEBAF88__

typedef struct peak_control_t
{
	void *report;
	
	unsigned int slice_duration;
	unsigned int slice_byte;
	unsigned int neighbor_size;
}peak_control_t;

/* return 0 allow sending out data now, other value is time to wait in micro second. */
unsigned int peak_control_check(peak_control_t *ctrl, int packet_size);
void peak_control_note(peak_control_t *ctrl, int packet_size);


/* if sending out allowed, MUST send out immediately. use the function if sending operation nerver failed */
unsigned int peak_control_pass_now(peak_control_t *ctrl, int packet_size);


/* bitrate is bits number in one second, slice_duration is in microsecond */
void make_peak_control(peak_control_t *blank, int bitrate, int slice_duration);
void config_peak_control(peak_control_t *ctrl, int bitrate, int slice_duration);
void release_peak_control(peak_control_t *ctrl);

#endif /*__PEAK_CONTROL_H_3A46CB93_D11D_4EBE_A4CD_6A652FEBAF88__*/
