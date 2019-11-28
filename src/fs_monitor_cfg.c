/*
 * fs_monitor_cfg.c
 *
 *  Created on: Nov 27, 2019
 *      Author: gilbert
 */

#include "fs_monitor_cfg.h"
#include "fs_monitor_log.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static struct fs_monitor_common_cfg * fs_monitor_cfg = 0;

int read_cfg_line(int fd , char * line) {
	char c = 0x00;
	int index = 0;
	int line_counter = 0;
	while (1 == read(fd , &c , 1)) {
		line_counter ++;

		if (c == '\n') {
			line[index] = '\0';

			return line_counter;
		}

		line[index ++] = c;

		if (index == DEFAULT_LINE_BUFFER_SIZE - 1) {
			line[DEFAULT_LINE_BUFFER_SIZE - 1] = '\0';

			return line_counter;
		}
	}

	line[index] = '\0';

	return line_counter;
}

void handle_cfg_line(char * line) {
	if (strstr(line , "[") != 0 && strstr(line , "]") != 0 && strstr(line , "=") == 0) {
		struct fs_monitor_common_cfg * cfg_item = (struct fs_monitor_common_cfg *)malloc(sizeof(struct fs_monitor_common_cfg));
		cfg_item->items = 0;
		cfg_item->next = 0;
		if (strstr(line , ",") != 0) {
			cfg_item->item_type = CFG_ITEM_TYPE_ARRAY;
			char * token = strtok(line , ",");
			if (token != 0) {
				(void)strcpy(cfg_item->item , &line[1]);
			}
		} else {
			cfg_item->item_type = CFG_ITEM_TYPE_KV;

			int pos = strlen(line);
			line[pos - 1] = '\0';
			(void)strcpy(cfg_item->item , &line[1]);
		}

		if (fs_monitor_cfg == 0) {
			fs_monitor_cfg = cfg_item;
		} else {
			cfg_item->next = fs_monitor_cfg;
			fs_monitor_cfg = cfg_item;
		}
	} else {
		if (fs_monitor_cfg != 0) {
			struct fs_monitor_cfg_item * item = (struct fs_monitor_cfg_item *)malloc(sizeof(struct fs_monitor_cfg_item));
			item->next = 0;
			item->items = 0;
			if (fs_monitor_cfg->item_type == CFG_ITEM_TYPE_KV) {
				item->index = -1;

				char * token = strtok(line , "=");
				if (token != 0) {
					(void)strcpy(item->key , token);

					token = strtok(0 , "=");
					if (token != 0) {
						(void)strcpy(item->value , token);
					}
				}

				if (fs_monitor_cfg->items == 0) {
					fs_monitor_cfg->items = item;
				} else {
					item->next = fs_monitor_cfg->items;
					fs_monitor_cfg->items = item;
				}
			} else {
				char * token = strtok(line , "=");
				if (token != 0) {
					char tmpTok[DEFAULT_STR_LEN] = {0};
					(void)strcpy(tmpTok , token);

					token = strtok(0 , "=");
					if (token != 0) {
						(void)strcpy(item->value , token);
					}

					char * s = strtok(tmpTok , "[");
					if (s != 0) {
						(void)strcpy(item->key , s);
						s = strtok(0 , "[");
						if (s != 0) {
							int pos = strlen(s);
							s[pos - 1] = '\0';
							item->index = atoi(s);
						}
					}
				}

				if (fs_monitor_cfg->items == 0) {
					fs_monitor_cfg->items = item;
				} else {
					item->next = fs_monitor_cfg->items;
					fs_monitor_cfg->items = item;
				}
			}
		}
	}
}

struct fs_monitor_common_cfg * read_cfg(char * cfg_path) {
	int fd = -1;
	if (-1 == (fd = open(cfg_path , O_RDWR | O_CREAT , 0755))) {
		ERROR_LOG("打开文件失败,%s" , cfg_path);

		return 0;
	}

	char line[DEFAULT_LINE_BUFFER_SIZE] = {0};
	while (read_cfg_line(fd , line) > 0) {
		if (strlen(line) > 0 && line[0] != '#') {
			handle_cfg_line(line);
		}

		(void)memset(line , 0x00 , DEFAULT_LINE_BUFFER_SIZE);
	}

	(void)close(fd);

	return fs_monitor_cfg;
}
