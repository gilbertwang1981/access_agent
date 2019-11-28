/*
 * fs_monitor_sys_cfg.c
 *
 *  Created on: Nov 28, 2019
 *      Author: gilbert
 */

#include "fs_monitor_sys_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct fs_monitor_sys_cfg * fs_monitor_sys_cfg_ptr = 0;

struct fs_monitor_sys_cfg * get_fs_monitor_sys_cfg() {
	return fs_monitor_sys_cfg_ptr;
}

struct fs_monitor_sys_cfg * convert_sys_cfg(struct fs_monitor_common_cfg * common_cfg) {
	struct fs_monitor_common_cfg * ptr = common_cfg;
	int isFound = 0;
	while (ptr != 0) {
		if (strcmp(ptr->item , "system") == 0) {
			isFound = 1;

			break;
		}

		ptr = ptr->next;
	}

	if (isFound) {
		struct fs_monitor_cfg_item * pitems = ptr->items;

		char separator[DEFAULT_STR_LEN] = {0};
		char is_daemon[DEFAULT_STR_LEN] = {0};
		char is_from_begin[DEFAULT_STR_LEN] = {0};
		while (pitems != 0) {
			if (strcmp(pitems->key , "separator") == 0) {
				(void)strcpy(separator , pitems->value);
			} else if (strcmp(pitems->key , "is_daemon") == 0) {
				(void)strcpy(is_daemon , pitems->value);
			}

			pitems = pitems->next;
		}

		if (strlen(separator) > 0 && strlen(is_daemon) > 0) {
			struct fs_monitor_sys_cfg * config = (struct fs_monitor_sys_cfg *)malloc(sizeof(struct fs_monitor_sys_cfg));

			if (strcmp(is_daemon , "true") == 0) {
				config->is_daemon = 1;
			} else {
				config->is_daemon = 0;
			}

			(void)strcpy(config->separator , separator);

			fs_monitor_sys_cfg_ptr = config;
		}
	}

	return fs_monitor_sys_cfg_ptr;
}
