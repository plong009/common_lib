/*********************************************************************************
 * sync_list.h: if internal list is empty, pop operation will wait untill it get a node. 
 *                   it support mpsc list, but NOT support mpmc list.
 *                   sync_list requires internal list to place pop and push function pointers at begin of list struct,
 *                   just like mpsc_list does.
 *********************************************************************************
 * Copyright (C) 2016-2016 Yufeng Long
 * Authors: Yufeng Long <loong.yufeng@gmail.com>
 * Version: 1.0
 *
 **********************************************************************************/
#ifndef __SYNC_LIST_H_39E3119B_E392_4718_8964_14E52879E551__
#define __SYNC_LIST_H_39E3119B_E392_4718_8964_14E52879E551__

#define SYNC_LIST_PRIV_SIZE (sizeof(void*)*3)

typedef void*  (*sync_pop_front_t)(void *list);
typedef void   (*sync_push_back_t)(void *list, void *node);
typedef void   (*sync_pop_try_t)(void *list, int timeout); /* timeout is in millisecond */

typedef struct sync_list_t
{
	sync_pop_front_t pop;
	sync_push_back_t push;

	sync_pop_try_t pop_try;
	char priv[SYNC_LIST_PRIV_SIZE];
}sync_list_t;

/* -1 failed, 0 OK */
int make_sync_list(sync_list_t *sync, void *alist);

/* so make sure there is NO pop operation blocking, and NO push() shall be invoked anymore. */
void release_sync_list(sync_list_t *sync);

#endif /*__SYNC_LIST_H_39E3119B_E392_4718_8964_14E52879E551__*/
