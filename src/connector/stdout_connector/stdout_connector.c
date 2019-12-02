/*
 * stdout_connector.c
 *
 *  Created on: Dec 2, 2019
 *      Author: gilbert
 */


#include "stdout_connector.h"

#include <stdio.h>

int connnect_to_source(char * snd_buffer , int buffer_size , char * logbuffer) {
	printf("标注输出connector，消息内容：%s\n" , logbuffer);

	return 0;
}
