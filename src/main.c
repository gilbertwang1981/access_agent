/*
 * main.c
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#include "fs_init_daemon.h"
#include "fs_monitor_worker_pool.h"
#include "fs_monitor_log.h"

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc , char ** argv) {
	if (argc != 3) {
		ERROR_LOG("命令：./access_agent cfg_path isbg");

		return -1;
	}

	if (1 == atoi(argv[2])) {
		init_daemon();
	}

	signal(SIGPIPE , SIG_IGN);

	INFO_LOG("访问日志分析服务启动,%d" , getpid());

	if (-1 == init_worker_pool(DEFAULT_POOL_NAME , DEFUALT_POOL_MAX_SIZE , argv[1])) {
		ERROR_LOG("初始化任务池失败");

		return -1;
	}

	return 0;
}
