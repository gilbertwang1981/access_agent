/*
 * fs_log_field.h
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#ifndef _FS_LOG_FIELD_H_
#define _FS_LOG_FIELD_H_

#include "fs_filed_linked_list.h"

void get_forward_ip(struct field_linked_list * header , char * field_value);
void get_client_ip(struct field_linked_list * header , char * field_value);
void get_method(struct field_linked_list * header , char * field_value);
void get_status(struct field_linked_list * header , char * field_value);
void get_interface(struct field_linked_list * header , char * field_value);
void get_service_ip(struct field_linked_list * header , char * field_value);
void get_interface(struct field_linked_list * header , char * field_value);
void get_timestamp(struct field_linked_list * header , char * field_value);
void get_resp_time(struct field_linked_list * header , char * field_value);

#endif /* _FS_LOG_FIELD_H_ */
