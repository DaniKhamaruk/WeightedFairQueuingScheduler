#pragma once

typedef struct node {
	packet* packet;
	struct node* next_node;
}node;
node* create_new_node();
bool is_stack_empty(node* head);
node* insert(node* head, node* new_node);
node* pop(node* head);