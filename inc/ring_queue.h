/*********************************************************************************
 * ring_queue.h: MPMC queue based on ring,
 *********************************************************************************
 * Copyright (C) 2016-2016 Yufeng Long
 * Authors: Yufeng Long <loong.yufeng@gmail.com>
 *
 **********************************************************************************/
#ifndef __RING_QUEUE_H_1450AB2A_D518_4BFF_B02A_8B7581316A5B__
#define __RING_QUEUE_H_1450AB2A_D518_4BFF_B02A_8B7581316A5B__


/* return 1 success, 0 failed, element buffer size MUST equal or greater than unit_len */
int ring_queue_push(void *ring_queue, void *element);

/* return 1 success, 0 failed, element buffer size MUST equal or greater than unit_len */
int ring_queue_pop(void *ring_queue, void *element);

/* power_for_2 shall be in range of [1, 25], the function shall allocate ring buf if ext_ring is NULL */
void *create_ring_queue(int power_for_2, int unit_len, void *ext_ring);

void free_ring_queue(void *ring);

#endif /*__RING_QUEUE_H_1450AB2A_D518_4BFF_B02A_8B7581316A5B__*/ 
