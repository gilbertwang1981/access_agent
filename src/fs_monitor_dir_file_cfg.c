/*
 * fs_monitor_dir_file_cfg.c
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */

#include "fs_monitor_log.h"
#include "fs_monitor_dir_file_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct fs_monitor_dir_file_cfg * dir_file_cfg_ptr = 0;

struct fs_monitor_dir_file_cfg * convert_dir_file_cfg(struct fs_monitor_common_cfg * common_cfg) {
	struct fs_monitor_common_cfg * ptr = common_cfg;
	int isFound = 0;
	while (ptr != 0) {
		if (strcmp(ptr->item , "dir_file") == 0) {
			isFound = 1;

			break;
		}

		ptr = ptr->next;
	}

	if (isFound) {
		struct fs_monitor_cfg_item * pitems = ptr->items;
		while (pitems != 0) {
			int i = 0;
			char dir[DEFAULT_STR_LEN] = {0};
			char file[DEFAULT_STR_LEN] = {0};
			char host[DEFAULT_STR_LEN] = {0};
			char port[DEFAULT_STR_LEN] = {0};
			for (;i < CFG_DIR_FILE_FIELDS_NUM;i ++) {
				if (strcmp(pitems->key , "dir") == 0) {
					(void)strcpy(dir , pitems->value);
				} else if (strcmp(pitems->key , "file") == 0) {
					(void)strcpy(file , pitems->value);
				} else if (strcmp(pitems->key , "host") == 0) {
					(void)strcpy(host , pitems->value);
				} else if (strcmp(pitems->key , "port") == 0) {
					(void)strcpy(port , pitems->value);
				}

				pitems = pitems->next;
			}

			if (strlen(dir) > 0 && strlen(file) > 0 && strlen(host) > 0 && strlen(port) > 0) {
				struct fs_monitor_dir_file_cfg * config = (struct fs_monitor_dir_file_cfg *)malloc(sizeof(struct fs_monitor_dir_file_cfg));
				(void)strcpy(config->dir , dir);
				(void)strcpy(config->file , file);
				(void)strcpy(config->host , host);
				config->port = atoi(port);

				if (dir_file_cfg_ptr == 0) {
					dir_file_cfg_ptr = config;
				} else {
					config->next = dir_file_cfg_ptr;
					dir_file_cfg_ptr = config;
				}
			}
		}
	}

	return dir_file_cfg_ptr;
}
