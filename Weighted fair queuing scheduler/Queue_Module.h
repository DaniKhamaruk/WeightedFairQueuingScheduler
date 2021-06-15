#pragma once
#include "common.h"


node* create_new_node(packet* p_new_packet);
bool is_queue_empty(node* head);
void insert_node_in_queue(node** head, packet* p_new_packet, node** tail);
node* initialize_head(node* head);
node* pop(node* head);