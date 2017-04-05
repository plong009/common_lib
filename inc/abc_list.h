#ifndef __ABC_LIST_H_28E5B155_C0DA_4BA2_8202_2E2ED7BA61EA__
#define __ABC_LIST_H_28E5B155_C0DA_4BA2_8202_2E2ED7BA61EA__

typedef struct abc_list_t abc_list_t;


typedef void*  (*abc_pop_front_t)(void *list);
typedef void   (*abc_push_back_t)(void *list, void *node);
typedef void   (*abc_remove_node_t)(void *list, void *node);
typedef void   (*abc_insert_node_t)(void *list, void *pos, void *node);

typedef struct abc_node_t
{
	struct abc_node_t *next;
	struct abc_node_t *prev;
}abc_node_t;


struct abc_list_t
{
	abc_pop_front_t   pop;
	abc_push_back_t   push;

	abc_remove_node_t remove;
	abc_insert_node_t insert;
	abc_node_t       *header;
	abc_node_t       *tail;
};

void make_abc_list(abc_list_t *list);

#endif /*__ABC_LIST_H_28E5B155_C0DA_4BA2_8202_2E2ED7BA61EA__*/
