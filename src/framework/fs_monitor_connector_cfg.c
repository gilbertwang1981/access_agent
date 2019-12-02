/*
 * fs_monitor_connector_cfg.c
 *
 *  Created on: Dec 2, 2019
 *      Author: gilbert
 */

#include "fs_monitor_connector_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct fs_monitor_connector_cfg * connector_cfg_ptr = 0;

struct fs_monitor_connector_cfg * convert_connector_cfg(struct fs_monitor_common_cfg * common_cfg) {
	struct fs_monitor_common_cfg * ptr = common_cfg;
	int isFound = 0;
	while (ptr != 0) {
		if (strcmp(ptr->item , "connectors") == 0) {
			isFound = 1;

			break;
		}

		ptr = ptr->next;
	}

	if (isFound) {
		struct fs_monitor_cfg_item * pitems = ptr->items;
		while (pitems != 0) {
			if (strcmp(pitems->key , "connector_so_path") == 0) {
				struct fs_monitor_connector_cfg * config = (struct fs_monitor_connector_cfg * )malloc(sizeof(struct fs_monitor_connector_cfg));
				(void)strcpy(config->connector , pitems->value);

				if (connector_cfg_ptr == 0) {
					connector_cfg_ptr = config;
				} else {
					config->next = connector_cfg_ptr;
					connector_cfg_ptr = config;
				}
			}

			pitems = pitems->next;
		}
	}

	return connector_cfg_ptr;
}

struct fs_monitor_connector_cfg * get_fs_monitor_connector_cfg() {
	return connector_cfg_ptr;
}
