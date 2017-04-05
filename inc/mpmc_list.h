#include "mpsc_list.h"

/* even using oddeven token, block happen when list empty , only use one token */
struct {
	node token;

	mpsc_list_t mpsc;
	ring_queue_t ring;
}list_t;

pop()
{
	do {node = ring.pop(); }while(!node)
	

	if(node != token)
		return node;


	node = mpsc.pop(list->mpsc);
	if(node == NULL) {
		pushback token;
		return NULL;
	}
	

	for(i=0; i<ringsize-2, i++ ) {
		node = mpsc.pop(list->mpsc);
		if(node == NULL)
			break;
		list->ring.push(list->ring, node);
	}

	ring.push tokenback;
	return node;

}

push()
{
	mpsc.push();
}

