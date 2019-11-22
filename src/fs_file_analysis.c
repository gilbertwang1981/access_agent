/*
 * fs_file_analysis.c
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "fs_access_agent_consts.h"
#include "fs_filed_linked_list.h"

int open_file(char * path , unsigned int offset) {
	int fd = -1;
	if (-1 == (fd = open(path , O_RDWR | O_CREAT , 0755))) {
		perror("打开文件失败");

		return -1;
	}

	if (-1 == lseek(fd , offset , SEEK_SET)) {
		perror("重置偏移失败");

		close_file(fd);

		return -1;
	}

	return fd;
}

struct field_linked_list * analysis_line(char * line) {
	struct field_linked_list *  ele_header = 0;

	char * token = strtok(line , "\t");
	int index = 0;
	while (token != 0) {
		struct field_linked_list * ele = (struct field_linked_list *)malloc(sizeof(struct field_linked_list));

		ele->index = index ++;
		ele->next = 0;
		(void)memset(ele->field , 0x00 , DEFAULT_STR_LEN);
		strcpy(ele->field , token);

		ele_header = add_field_linked_list(ele_header , ele);

		token = strtok(0 , "\t");
	}

	return ele_header;
}

int close_file(int fd) {
	if (-1 == close(fd)) {
		perror("关闭文件失败");

		return -1;
	}

	return 0;
}

int read_line(int fd , char * line) {
	if (-1 == fd) {
		perror("文件描述符失效");

		return -1;
	}

	char c = 0x00;
	int index = 0;
	int line_counter = 0;
	while (1 == read(fd , &c , 1)) {
		line_counter ++;
		if (c == '\n') {
			line[index] = '\0';

			return line_counter;
		}

		if ((c >= 0x41 && c <= 0x5a) ||
			(c >= 0x61 && c <= 0x7a) ||
			(c >= 0x20 && c <= 0x39) ||
			c == 0x09) {
			line[index ++] = c;
		} else {
			continue;
		}

		if (index == DEFAULT_LINE_BUUFER_SIZE - 1) {
			line[DEFAULT_LINE_BUUFER_SIZE - 1] = '\0';

			return line_counter;
		}
	}

	return 0;
}
