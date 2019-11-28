/*
 * fs_monitor_field_cfg.c
 *
 *  Created on: Nov 25, 2019
 *      Author: gilbert
 */

#include "fs_monitor_field_cfg.h"
#include "fs_monitor_log.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct fs_monitor_field_cfg * field_cfg_ptr = 0;

struct fs_monitor_field_cfg * convert_field_cfg(struct fs_monitor_common_cfg * common_cfg) {
	struct fs_monitor_common_cfg * ptr = common_cfg;
	int isFound = 0;
	while (ptr != 0) {
		if (strcmp(ptr->item , "field") == 0) {
			isFound = 1;

			break;
		}

		ptr = ptr->next;
	}

	if (isFound) {
		struct fs_monitor_cfg_item * pitems = ptr->items;
		while (pitems != 0) {
			struct fs_monitor_field_cfg * config = (struct fs_monitor_field_cfg *)malloc(sizeof(struct fs_monitor_field_cfg));
			(void)strcpy(config->field , pitems->key);
			char * token = strtok(pitems->value , ":");
			if (token != 0) {
				config->index = atoi(token);
				token = strtok(0 , ":");
				if (token != 0) {
					config->size = atoi(token);
				}
			}

			if (field_cfg_ptr == 0) {
				field_cfg_ptr = config;
			} else {
				config->next = field_cfg_ptr;
				field_cfg_ptr = config;
			}

			pitems = pitems->next;
		}
	}

	return field_cfg_ptr;
}
