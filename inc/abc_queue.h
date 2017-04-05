#ifndef __ABC_QUEUE_23567E5D_F91C_4696_829C_CE44EFED9800__
#define __ABC_QUEUE_23567E5D_F91C_4696_829C_CE44EFED9800__

typedef void*  (*abc_queue_pop_t)(void *queue);
typedef int    (*abc_queue_push_t)(void *queue, void *element);
typedef void*  (*abc_queue_first_t)(void *queue);
typedef void*  (*abc_queue_next_t)(void *queue);

typedef struct abc_queue_t
{
	abc_queue_pop_t   pop;
	abc_queue_push_t  push; /* the push is NOT compatible with pure_push */
	abc_queue_first_t first;
	abc_queue_next_t  next;

	unsigned int   write_total;
	unsigned int   read_total;
	unsigned int   read_offset;
	unsigned int   write_offset;
	unsigned int   seeking_offset;
	unsigned int   unit_number;
	unsigned int   unit_len_align; /*because it returns data pointer but not copys data to outside like ring_queue, it requires data alignment here */
	unsigned int   unit_len;
	unsigned char* buf;
}abc_queue_t;

abc_queue_t *create_abc_queue(int unit_number, int unit_len);
void free_abc_queue(abc_queue_t *queue);
void reset_abc_queue(abc_queue_t *queue);
int double_abc_queue(abc_queue_t *queue);

#endif /*__ABC_QUEUE_23567E5D_F91C_4696_829C_CE44EFED9800__*/
