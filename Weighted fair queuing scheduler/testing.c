#include "IO_and_parsing_Module.h"
#include "Queue_Module.h"
#include "Heap.h"

void dani()
{
	char p_line[MAX_LINE_SIZE] = { 0 };
	int index_in_the_line = 0;
	node* head = NULL, * tail = NULL;
	//////////////////////
	head = initialize_head(head);
	tail = initialize_head(tail);
	head->next_node = tail;
	//TODO:combine into a func ^^^
	//////////////////////
	packet* local = NULL;
	while (NULL != fgets(p_line, MAX_LINE_SIZE, stdin)) {
		local = get_info_to_packet(p_line);
		print_packet(local);
		insert_3(&head, local, &tail);
	}
}
void udi()
{
	heap_test();
}
void main() {
	//dani();
	udi();
}