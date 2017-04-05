/*********************************************************************************
 * pure_list.h: common interface form all kinds of list, liek
 *              abs list, mpsc list, mpmc list and sync list etc.
 *********************************************************************************
 * Copyright (C) 2016-2016 Yufeng Long
 * Authors: Yufeng Long <loong.yufeng@gmail.com>
 * Version: 1.0
 **********************************************************************************/
#ifndef __PURE_LIST_H_677F0B79_2123_48F6_BB8E_46386D8880A6__
#define __PURE_LIST_H_677F0B79_2123_48F6_BB8E_46386D8880A6__

typedef struct pure_list_node_t pure_list_node_t;
typedef struct pure_easy_node_t pure_easy_node_t;
typedef struct pure_list_t      pure_list_t;

typedef pure_list_node_t*  (*pure_list_pop_front_t)(void *);
typedef void               (*pure_list_push_back_t)(void *, void *);


struct pure_list_node_t
{
	struct pure_list_node_t *next;
	struct pure_list_node_t *prev;
};

struct pure_easy_node_t
{
	pure_list_node_t node;
	int   user_data1;
	void *user_data2;
};


struct pure_list_t
{
	pure_list_pop_front_t pop;
	pure_list_push_back_t push;
};


inline void *pure_pop(void*list) { return ((pure_list_t*)list)->pop(list);}
inline void  pure_push(void *list, void *node) { ((pure_list_t*)list)->push(list, node);}

#endif /*__PURE_LIST_H_677F0B79_2123_48F6_BB8E_46386D8880A6__*/
