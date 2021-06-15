#include "Queue_Module.h"


node* initialize_head(node* head) {
	node* null_node = create_new_node(NULL);
	//head->packet = NULL;
	//head->next_node = NULL;
	return null_node;
}
node* create_new_node(packet* p_new_packet) {
	node* new_node = NULL;
	if (NULL == (new_node = (node*)calloc(1, sizeof(node)))) {
		printf("Couldn't allocate memory for stack");
		return NULL;
	}
	new_node->next_node = NULL;
	new_node->packet = p_new_packet;
	return new_node;
}

bool is_queue_empty(node* head) {
	return (NULL == head);
}
void insert_node_in_queue(node** head, packet* p_new_packet,node** tail) {
	node* new_node = create_new_node(p_new_packet);
	if (NULL == *head) { 
		*head = new_node;
		*tail = *head;
	}
	else if ((*head)->next_node == NULL) {
		(*head)->next_node = new_node;
		*tail = new_node;
	}
	else {
		(*tail)->next_node = new_node;
		*tail = new_node;
	}
}
node* pop(node* head) {
	node* temp_head = head;
	if (NULL == head) {
		return NULL;
	}
	head = head->next_node;
	free(temp_head);
	return head;
	//TODO: need to check if returning static allocation is fine
}

void main_2() {

	//TODO:Func for tail
	return;
}