/*
 * fs_monitor_dir_file_cfg.h
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_DIR_FILE_CFG_H_
#define _FS_MONITOR_DIR_FILE_CFG_H_

#include "fs_access_agent_consts.h"
#include "fs_monitor_cfg.h"

struct fs_monitor_dir_file_cfg {
	char dir[DEFAULT_STR_LEN];
	char file[DEFAULT_STR_LEN];

	struct fs_monitor_dir_file_cfg * next;
};

struct fs_monitor_dir_file_cfg * convert_dir_file_cfg(struct fs_monitor_common_cfg * common_cfg);

#endif /* _FS_MONITOR_DIR_FILE_CFG_H_ */
