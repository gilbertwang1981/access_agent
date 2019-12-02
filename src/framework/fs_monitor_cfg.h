/*
 * fs_monitor_cfg.h
 *
 *  Created on: Nov 27, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_CFG_H_
#define _FS_MONITOR_CFG_H_

#include "fs_access_agent_consts.h"

struct fs_monitor_cfg_item {
	int index;
	char key[DEFAULT_STR_LEN];
	char value[DEFAULT_LINE_BUFFER_SIZE];
	struct fs_monitor_cfg_item * next;
	struct fs_monitor_cfg_item * items;
};

struct fs_monitor_common_cfg {
	char item[DEFAULT_STR_LEN];
	int item_type;

	struct fs_monitor_cfg_item * items;

	struct fs_monitor_common_cfg * next;
};

struct fs_monitor_common_cfg * read_cfg(char * cfg_path);
int read_cfg_line(int fd , char * line);
void handle_cfg_line(char * line);

#endif /* _FS_MONITOR_CFG_H_ */
