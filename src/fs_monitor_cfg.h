/*
 * fs_monitor_cfg.h
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_CFG_H_
#define _FS_MONITOR_CFG_H_

#include "fs_access_agent_consts.h"

struct fs_monitor_cfg {
	char dir[DEFAULT_STR_LEN];
	char file[DEFAULT_STR_LEN];
	char host[DEFAULT_STR_LEN];
	int port;

	struct fs_monitor_cfg * next;
};

struct fs_monitor_cfg * read_cfg(char * cfg_path);
int read_line_without_null(int fd , char * line);
void handle_cfg_line(struct fs_monitor_cfg * cfg , char * line);

#endif /* _FS_MONITOR_CFG_H_ */
