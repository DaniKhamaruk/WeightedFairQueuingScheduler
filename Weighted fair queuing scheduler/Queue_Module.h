#pragma once

typedef struct node {
	packet* packet;
	struct node* next_node;
	struct node* tail_node;
}node;
node* create_new_node(packet* p_new_packet);
bool is_queue_empty(node* head);
node* insert(node* head, packet* p_new_packet);
node* insert_2(node* head, packet* p_new_packet, node* tail);
void insert_3(node** head, packet* p_new_packet, node** tail);
node* initialize_head(node* head);
node* pop(node* head);