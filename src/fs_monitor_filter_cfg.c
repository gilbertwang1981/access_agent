/*
 * fs_monitor_filter_cfg.c
 *
 *  Created on: Nov 29, 2019
 *      Author: gilbert
 */

#include "fs_monitor_filter_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct fs_monitor_filter_cfg * fs_monitor_filter_cfg_ptr = 0;

struct fs_monitor_filter_cfg * convert_filter_cfg(struct fs_monitor_common_cfg * common_cfg) {
	struct fs_monitor_common_cfg * ptr = common_cfg;
	int isFound = 0;
	while (ptr != 0) {
		if (strcmp(ptr->item , "filter") == 0) {
			isFound = 1;

			break;
		}

		ptr = ptr->next;
	}

	if (isFound) {
		struct fs_monitor_cfg_item * pitems = ptr->items;
		while (pitems != 0) {
			struct fs_monitor_filter_cfg * config = (struct fs_monitor_filter_cfg *)malloc(sizeof(struct fs_monitor_filter_cfg));
			(void)strcpy(config->filter_key , pitems->key);
			(void)strcpy(config->filter_value , pitems->value);
			config->next = 0;

			if (fs_monitor_filter_cfg_ptr == 0) {
				fs_monitor_filter_cfg_ptr = config;
			} else {
				config->next = fs_monitor_filter_cfg_ptr;
				fs_monitor_filter_cfg_ptr = config;
			}

			pitems = pitems->next;
		}
	}

	return fs_monitor_filter_cfg_ptr;
}

struct fs_monitor_filter_cfg * get_fs_monitor_filter_cfg() {
	return fs_monitor_filter_cfg_ptr;
}
