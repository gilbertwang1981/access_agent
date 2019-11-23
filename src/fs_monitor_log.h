/*
 * fs_monitor_log.h
 *
 *  Created on: Nov 23, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_LOG_H_
#define _FS_MONITOR_LOG_H_

#include <syslog.h>

#define DEBUG_LOG(message , ...) syslog(LOG_USER | LOG_DEBUG , message , ##__VA_ARGS__);

#define INFO_LOG(message , ...) syslog(LOG_USER | LOG_INFO , message , ##__VA_ARGS__);

#define ERROR_LOG(message , ...) syslog(LOG_USER | LOG_ERR , message , ##__VA_ARGS__);

#define WARN_LOG(message , ...) syslog(LOG_USER | LOG_WARNING , message , ##__VA_ARGS__);

#endif /* _FS_MONITOR_LOG_H_ */
