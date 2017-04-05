/*********************************************************************************
 * token.h: guarantee the resource that token is protecting already be released before close it,
 * protect resource to be closed safely.
 * safely closing token itself(not the resource protected) shall be implemented in user application but NOT here,
 * to safely close token, must guarantee no apply() and no return() invoked anymore.
 * apply to two threads only, one uses resource the other authorizes it.
 *********************************************************************************
 * Copyright (C) 2016-2016 Yufeng Long
 * Authors: Yufeng Long <loong.yufeng@gmail.com>
 *
 **********************************************************************************/
#ifndef __TOKEN_H_E0027F1A_2D8F_4FFF_98F7_F9448A12039F__
#define __TOKEN_H_E0027F1A_2D8F_4FFF_98F7_F9448A12039F__

#define TOKEN_PRIV_SIZE (sizeof(int)*8)

typedef struct token_t
{
	char priv[TOKEN_PRIV_SIZE];
}token_t;

void token_init(token_t *token);
void token_enable(token_t *token);
int  token_try_retrieve(token_t *token); /* return 1 for OK, return 0 for failed */
void token_wait_retrieve(token_t *token);

/* apply() and return() must make pairs, it does not match error could happend. */
int  token_apply(token_t *token); /* return 1 for OK, return 0 for failed */
void token_return(token_t *token);

#endif /*__TOKEN_H_E0027F1A_2D8F_4FFF_98F7_F9448A12039F__*/
