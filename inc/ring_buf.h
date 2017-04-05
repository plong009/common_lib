/* safe for two threads, one for reading and the other for writing
 */
#ifndef __RING_BUF_H_6CA3C026_33BE_4a77_BB9B_61E42EAFF02F__
#define __RING_BUF_H_6CA3C026_33BE_4a77_BB9B_61E42EAFF02F__

typedef struct ring_buf_t ring_buf_t;


typedef   int (*ring_buf_write_t)    (ring_buf_t *ring, void *buf, int size); /* write all or none*/
typedef   int (*ring_buf_free_size_t)(ring_buf_t *ring);

typedef   int (*ring_buf_read_t)     (ring_buf_t *ring, void *buf, int size);  /* return size of read, maybe zero size */
typedef   int (*ring_buf_data_size_t)(ring_buf_t *ring);
typedef void* (*ring_buf_check_t)    (ring_buf_t *ring, int *size1, int *size2); /* return read pointer, size1 or size2 must not be null */
typedef   int (*ring_buf_skip_t)     (ring_buf_t *ring, int size); /* if size bigger than all available data, skip all and return all data size */


struct ring_buf_t
{
	unsigned int write_total;
	unsigned int read_total;
	int write_offset;
	int read_offset;
	void *buf;
	int buf_size;

	ring_buf_write_t     write;
	ring_buf_free_size_t free_size;

	ring_buf_read_t      read;
	ring_buf_data_size_t data_size;
	ring_buf_check_t     check;
	ring_buf_skip_t      skip;
};

void make_ring_buf(ring_buf_t *blank, void *buf, int size);

/* when switching buf, there shall not be any reading or writing operation */
void switch_ring_buf(ring_buf_t *ring, void *buf, int size);

#endif /*__RING_BUF_H_6CA3C026_33BE_4a77_BB9B_61E42EAFF02F__*/
