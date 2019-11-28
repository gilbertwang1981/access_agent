/*
 * fs_monitor_sys_cfg.h
 *
 *  Created on: Nov 28, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_SYS_CFG_H_
#define _FS_MONITOR_SYS_CFG_H_

#include "fs_access_agent_consts.h"
#include "fs_monitor_cfg.h"

struct fs_monitor_sys_cfg {
	char separator[DEFAULT_STR_LEN];
	int is_daemon;
	int is_from_begin;
};

struct fs_monitor_sys_cfg * convert_sys_cfg(struct fs_monitor_common_cfg * common_cfg);

struct fs_monitor_sys_cfg * get_fs_monitor_sys_cfg(void);

#endif /* _FS_MONITOR_SYS_CFG_H_ */
