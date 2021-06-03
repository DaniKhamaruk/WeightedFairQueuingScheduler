#pragma once

typedef struct node {
	packet* packet;
	struct node* next_node;
}node;
node* create_new_node(packet* p_new_packet);
bool is_stack_empty(node* head);
node* insert(node* head, packet* p_new_packet);
node* pop(node* head);