/*
 * fs_monitor_filter_cfg.h
 *
 *  Created on: Nov 29, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_FILTER_CFG_H_
#define _FS_MONITOR_FILTER_CFG_H_

#include "fs_access_agent_consts.h"
#include "fs_monitor_cfg.h"

struct fs_monitor_filter_cfg {
	char filter_key[DEFAULT_STR_LEN];
	char filter_value[DEFAULT_STR_LEN];

	struct fs_monitor_filter_cfg * next;
};

struct fs_monitor_filter_cfg * convert_filter_cfg(struct fs_monitor_common_cfg * common_cfg);

struct fs_monitor_filter_cfg * get_fs_monitor_filter_cfg(void);

#endif /* _FS_MONITOR_FILTER_CFG_H_ */
