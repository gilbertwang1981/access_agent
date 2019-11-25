/*
 * fs_monitor_dir_file_cfg.h
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_DIR_FILE_CFG_H_
#define _FS_MONITOR_DIR_FILE_CFG_H_

#include "fs_access_agent_consts.h"

struct fs_monitor_dir_file_cfg {
	char dir[DEFAULT_STR_LEN];
	char file[DEFAULT_STR_LEN];
	char host[DEFAULT_STR_LEN];
	int port;

	struct fs_monitor_dir_file_cfg * next;
};

struct fs_monitor_dir_file_cfg * read_dir_file_cfg(char * cfg_path);
int read_line_without_null_dir_file_cfg(int fd , char * line);
void handle_dir_file_cfg_line(struct fs_monitor_dir_file_cfg * cfg , char * line);

#endif /* _FS_MONITOR_DIR_FILE_CFG_H_ */
