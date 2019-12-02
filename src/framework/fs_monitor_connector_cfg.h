/*
 * fs_monitor_connector_cfg.h
 *
 *  Created on: Dec 2, 2019
 *      Author: gilbert
 */

#ifndef _FRAMEWORK_FS_MONITOR_CONNECTOR_CFG_H_
#define _FRAMEWORK_FS_MONITOR_CONNECTOR_CFG_H_


#include "fs_access_agent_consts.h"
#include "fs_monitor_cfg.h"

struct fs_monitor_connector_cfg {
	char connector[DEFAULT_STR_LEN];

	struct fs_monitor_connector_cfg * next;
};

struct fs_monitor_connector_cfg * convert_connector_cfg(struct fs_monitor_common_cfg * common_cfg);

struct fs_monitor_connector_cfg * get_fs_monitor_connector_cfg(void);

#endif /* _FRAMEWORK_FS_MONITOR_CONNECTOR_CFG_H_ */
