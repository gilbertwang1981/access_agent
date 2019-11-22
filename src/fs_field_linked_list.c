/*
 * fs_linked_list.c
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#include <unistd.h>
#include <stdlib.h>

#include "fs_filed_linked_list.h"

struct field_linked_list * add_field_linked_list(struct field_linked_list * header , struct field_linked_list * ele) {
	if (header == 0) {
		header = ele;
		ele->next = 0;
	} else {
		ele->next = header;
		header = ele;
	}

	return header;
}

void free_field_linked_list(struct field_linked_list * header) {
	struct field_linked_list * ptr = header;

	struct field_linked_list * tmp = 0;
	while (ptr != 0) {
		tmp = ptr;

		ptr = ptr->next;

		free(tmp);
	}
}
