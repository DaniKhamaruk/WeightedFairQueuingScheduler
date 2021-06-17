#include "IO_and_parsing_Module.h"
#include "Queue_Module.h"
#include "Heap.h"
#include "Flow.h"
#include <math.h>


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
	FILE* fp = NULL;
	fopen_s(&fp,"output.txt", "w");

	int global_time = 0;
	float time_to_next_pkt = 0, delta = 0;
	char p_line[MAX_LINE_SIZE] = { 0 };
	heap_struct heap;
	init_heap(&heap);
	fgets(p_line, MAX_LINE_SIZE, stdin);
	packet *pkt = get_info_to_packet(p_line), *pkt_to_send = NULL;
	bool new_pkt_arrived = true, no_more_new_pkt = false, WFQ_empty = false;
	flow_struct *WFQ = initialize_flow();
	heap_node* node_to_send_his_pkt = NULL;
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
		if (WFQ->gps_parameters.time_remain <= 0 || WFQ_empty) {
			if (!is_flow_empty(WFQ))
				delete_first_pkt_in_flow(WFQ);
			if (is_flow_empty(WFQ) && !is_flow_empty(heap.root->flow)) { //fetch new pkt to send
				node_to_send_his_pkt = search_flow_to_send_his_pkt(heap.root);
				insert_new_pkt_to_WFQ(WFQ, node_to_send_his_pkt->flow);
			}
			if (!is_flow_empty(WFQ)) {
				WFQ_empty = false;
				WFQ->gps_parameters.time_remain = (float)WFQ->head->packet->length;
			//TODO: uncomment	
				fprintf(stdout,"%d: %s", global_time, WFQ->head->packet->pkt_str);

				//////////////////////////////////////////////////////////
				//TODO: remove
				fprintf(fp, "%d: %s", global_time, WFQ->head->packet->pkt_str);
				//////////////////////////////////////////////////////////
			}
			else {
				WFQ_empty = true;
				WFQ->gps_parameters.time_remain = FLT_MAX;
			}
		}

		//preparation to next iteration
		delta = min(time_to_next_pkt, heap.root->flow->gps_parameters.time_remain);
		if (!is_flow_empty(WFQ))
			delta = min(delta, WFQ->gps_parameters.time_remain);
		delta = ceil(delta);
		update_heap(&heap, delta, WFQ);
		if (is_flow_empty(WFQ))
			WFQ_empty = true;
		else
			WFQ->gps_parameters.time_remain -= delta;
		if (!no_more_new_pkt) {
			time_to_next_pkt -= delta;
			if (time_to_next_pkt == 0) {
				new_pkt_arrived = true;
				time_to_next_pkt = FLT_MAX;
			}
		}
	}
	//TODO: free heap
	fclose(fp);


	free(WFQ);
}