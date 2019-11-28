/*
 * fs_monitor_field_cfg.h
 *
 *  Created on: Nov 25, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_FIELD_CFG_H_
#define _FS_MONITOR_FIELD_CFG_H_

#include "fs_access_agent_consts.h"
#include "fs_monitor_cfg.h"

struct fs_monitor_field_cfg {
	char field[DEFAULT_STR_LEN];
	int index;
	int size;

	struct fs_monitor_field_cfg * next;
};

struct fs_monitor_field_cfg * convert_field_cfg(struct fs_monitor_common_cfg * common_cfg);

#endif /* _FS_MONITOR_FIELD_CFG_H_ */
