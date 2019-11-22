/*
 * fs_line_analysis.h
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#ifndef _FS_FIELD_LINKED_LIST_H_
#define _FS_FIELD_LINKED_LIST_H_

#include "fs_access_agent_consts.h"

struct field_linked_list {
	int index;
	char field[DEFAULT_STR_LEN];

	struct field_linked_list * next;
};

struct field_linked_list * add_field_linked_list(struct field_linked_list * header , struct field_linked_list * ele);
void free_field_linked_list(struct field_linked_list * header);


#endif /* _FS_FIELD_LINKED_LIST_H_ */
