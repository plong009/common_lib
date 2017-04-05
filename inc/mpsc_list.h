/*********************************************************************************
 * mpsc_list.h: lock free mpsc list header file
 *********************************************************************************
 * Copyright (C) 2013-2013 Yufeng Long
 * Authors: Yufeng Long <loong.yufeng@gmail.com>
 * Version: 1.0
 *
 ************************* Example *************************************************
 * mpsc_list_t list;
 * struct {
 * 	 mpsc_node_t  n;
 * 	 usertype     place_more_userdat_here;
 * }node;
 *
 * make_mpsc_list(&list);
 * list.push(&list, &node);
 * void *p = list.pop(&list);
 **********************************************************************************/
#ifndef __MPSC_LIST_H_EE0EE566_C547_4720_ACB1_A1C380FA9B32__
#define __MPSC_LIST_H_EE0EE566_C547_4720_ACB1_A1C380FA9B32__

#define MPSC_LIST_PRIV_SIZE (sizeof(void*)*5)

typedef void*  (*mpsc_pop_front_t)(void *list);
typedef void   (*mpsc_push_back_t)(void *list, void *node);

typedef struct mpsc_node_t
{
	void *node_priv[2];
}mpsc_node_t;

typedef struct mpsc_list_t
{
	mpsc_pop_front_t pop; /* user likely would not remember and type mpsc_pop_front(), just a comon word is fine*/
	mpsc_push_back_t push;

	char priv[MPSC_LIST_PRIV_SIZE];
}mpsc_list_t;

/* the return value is input parameter blank, no special meaing just for coding easy to nest it in sync list */
void* make_mpsc_list(mpsc_list_t *blank);

#endif /*__MPSC_LIST_H_EE0EE566_C547_4720_ACB1_A1C380FA9B32__*/
