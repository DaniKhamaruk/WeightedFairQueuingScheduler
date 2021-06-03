#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "IO_and_parsing_Module.h"
#include "Queue_Module.h"



node* create_new_node() {
	node* new_node = NULL;
	if (NULL == (new_node = (node*)calloc(1, sizeof(node)))) {
		printf("Couldn't allocate memory for stack");
		return NULL;
	}
	return new_node;
}

bool is_stack_empty(node* head) {
	return (NULL == head);
}
node* insert(node* head, node* new_node) {
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
node* pop(node* head) {
	node* temp_head = head;
	if (NULL == head) {
		return NULL;
	}
	head = head->next_node;
	return temp_head;
	//TODO: need to check if returning static allocation is fine
}

void main_2() {

	//TODO:Func for tail
	return;
}