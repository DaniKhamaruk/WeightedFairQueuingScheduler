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
node* insert(node* head, packet* p_new_packet) {
	node* new_node = create_new_node(p_new_packet);
	node* temp = head;
	if (NULL == head) {
		return new_node;
	}
	while (NULL != temp->next_node) {
		temp = temp->next_node;
	}
	temp->next_node = new_node;
	//TODO:need to check
	return head;
}
node* insert_2(node* head, packet* p_new_packet,node* tail) {
	node* new_node = create_new_node(p_new_packet);
	node* temp_node = head;
	if (NULL == head->packet) {
		temp_node = head;
		head = new_node;
		head->next_node = tail;
		free(temp_node);
	}
	else {
		if (NULL == tail->packet) {
			temp_node = tail;
			tail = new_node;
			tail = tail->next_node;
			free(temp_node);
		}
		else {
			tail->next_node = new_node;
			tail = tail->next_node;
		}
	}
	return head;
}
void insert_3(node** head, packet* p_new_packet,node** tail) {
	node* new_node = create_new_node(p_new_packet);
	node* temp_node = *head;
	if (NULL == (*head)->packet) {
		temp_node = *head;
		*head = new_node;
		(*head)->next_node = *tail;
		free(temp_node);
	}
	else {
		if (NULL == (*tail)->packet) {
			temp_node = *tail;
			*tail = new_node;
			(*tail)->next_node = NULL;
			(*head)->next_node = *tail;
			free(temp_node);
		} 
		else{
			(*tail)->next_node = new_node;
			(*tail) = (*tail)->next_node;
		}
	}
	/*return tail;*/
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