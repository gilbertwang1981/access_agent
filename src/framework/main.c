/*
 * main.c
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#include "fs_init_daemon.h"
#include "fs_monitor_worker_pool.h"
#include "fs_monitor_log.h"
#include "fs_monitor_sys_cfg.h"
#include "fs_monitor_cfg.h"

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , char ** argv) {
	if (argc != 2) {
		ERROR_LOG("命令：./access_agent cfg_file_path, "
				"比如：./access_agent /root/access_agent/config/fs_monitor.cfg");

		return -1;
	}

	struct fs_monitor_common_cfg * common_cfg = read_cfg(argv[1]);
	if (common_cfg == 0) {
		ERROR_LOG("初始化配置文件失败");

		return -1;
	}

	struct fs_monitor_sys_cfg * sys_cfg = convert_sys_cfg(common_cfg);
	if (sys_cfg == 0) {
		ERROR_LOG("加载系统配置错误");

		return -1;
	}

	if (1 == sys_cfg->is_daemon) {
		init_daemon();
	}

	signal(SIGPIPE , SIG_IGN);

	INFO_LOG("访问日志分析服务启动,%d" , getpid());

	if (-1 == init_worker_pool(DEFAULT_POOL_NAME , DEFUALT_POOL_MAX_SIZE , strtol(sys_cfg->separator , '\0', 16) , common_cfg)) {
		ERROR_LOG("初始化任务池失败");

		return -1;
	}

	return 0;
}
