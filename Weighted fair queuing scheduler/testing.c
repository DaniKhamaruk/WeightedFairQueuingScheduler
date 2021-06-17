#include "IO_and_parsing_Module.h"
#include "Queue_Module.h"
#include "Heap.h"
#include "Flow.h"

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
		insert_node_in_queue(&head, local, &tail);
	}
}
void udi()
{
	heap_test();
}
void main() {
	//dani();
	//udi();

	/*V1
	global_time = 0;
	read first pkt
	new_pkt_arrived = true;
	while (true) {
		//current iteration
		if new_pkt_arrived
			insert_pkt_to_heap
			read next pkt
			calc time_to_next_pkt

		//preparation to next iteration
		delta = min(time_to_next_pkt, heap->root->gps_parameters.time_remain);
		update_heap(heap, delta);
		global_time += delta;
		time_to_next_pkt -= delta
		if time_to_next_pkt == 0
			new_pkt_arrived = true;
	}	
	*/



	/* V2
	global_time = 0;
	read first pkt
	new_pkt_arrived = true;
	while (true) {
		//current iteration
		if new_pkt_arrived
			insert_pkt_to_heap
			read next pkt
			calc time_to_next_pkt

		//preparation to next iteration
		delta = min(time_to_next_pkt, heap->root->gps_parameters.time_remain);
		update_heap(heap, delta);
		global_time += delta;
		time_to_next_pkt -= delta
		if time_to_next_pkt == 0
			new_pkt_arrived = true;
	}
	*/

	int global_time = 0;
	float time_to_next_pkt = 0, delta = 0;
	char p_line[MAX_LINE_SIZE] = { 0 };
	heap_struct heap;
	init_heap(&heap);
	fgets(p_line, MAX_LINE_SIZE, stdin);
	packet* pkt = get_info_to_packet(p_line);
	bool new_pkt_arrived = true, no_more_new_pkt = false, WFQ_empty = false;
	while (!no_more_new_pkt || !WFQ_empty) {
		global_time += delta;
		//current iteration
		if (new_pkt_arrived) {
			new_pkt_arrived = false;
			insert_pkt_to_heap(&heap, pkt);
			if (NULL != fgets(p_line, MAX_LINE_SIZE, stdin)) {
				time_to_next_pkt = pkt->time;  //reference point
				pkt = get_info_to_packet(p_line);
				time_to_next_pkt = pkt->time - time_to_next_pkt ;
			}
			else {
				no_more_new_pkt = true;
				time_to_next_pkt = FLT_MAX;
			}	
		}
		//preparation to next iteration
		delta = min(time_to_next_pkt, heap.root->flow->gps_parameters.time_remain);
		///////////////////////////////////////////////
		////TODO: remove
		if (!is_flow_empty(heap.root->flow)) {
			printf("before, global_time: %d\n", global_time);
			print_packet(heap.root->flow->head->packet);
			printf("%f %f\n\n", heap.root->flow->gps_parameters.time_remain, heap.root->flow->gps_parameters.length_remain);
		}
		///////////////////////////////////////////////
		update_heap(&heap, delta);
		///////////////////////////////////////////////
		////TODO: remove
		if (!is_flow_empty(heap.root->flow)) {
			printf("after, global_time: %d\n", (int)(global_time+delta));
			print_packet(heap.root->flow->head->packet);
			printf("%f %f\n\n", heap.root->flow->gps_parameters.time_remain, heap.root->flow->gps_parameters.length_remain);
		}
		///////////////////////////////////////////////
		if (heap.root->flow->num_of_pkts == 0)
			WFQ_empty = true;
		if (!no_more_new_pkt) {
			time_to_next_pkt -= delta;
			if (time_to_next_pkt == 0) {
				new_pkt_arrived = true;
				time_to_next_pkt = FLT_MAX;
			}
		}
	}
}