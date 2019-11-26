/*
 * fs_monitor_field_cfg.h
 *
 *  Created on: Nov 25, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_FIELD_CFG_H_
#define _FS_MONITOR_FIELD_CFG_H_

#include "fs_access_agent_consts.h"

struct fs_monitor_field_cfg {
	char field[DEFAULT_STR_LEN];
	int index;
	int size;

	struct fs_monitor_field_cfg * next;
};

struct fs_monitor_field_cfg * read_field_cfg(char * cfg_path);
int read_line_without_null_field_cfg(int fd , char * line);
void handle_field_cfg_line(char * line);

#endif /* _FS_MONITOR_FIELD_CFG_H_ */
