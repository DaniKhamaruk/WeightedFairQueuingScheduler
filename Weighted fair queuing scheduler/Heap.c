#include <math.h>
#include "Heap.h"
#include "Flow.h"
#include "IO_and_parsing_Module.h"
#include "GPS_Module.h"
#pragma warning(disable : 4244) //Num of links < MAX_INT
#pragma warning(disable : 26451)//Num of links < MAX_INT

heap_node* create_heap_node()
{
	heap_node* new = NULL;
	if (NULL == (new = calloc(1, sizeof(heap_node)))) {
		printf("Couldn't make new heap_node\n");
		return NULL;
	}
	return new;
}
void init_heap(heap_struct *heap)
{
	heap->root = NULL;
	heap->size = 0;
	heap->total_weight = 0;
}
bool is_heap_empty(heap_struct *heap)
{
	return (heap->root == NULL);
}
bool search_nodes_rec(heap_node* root, packet* pkt, heap_node** res)
{
	if (root == NULL)
		return false;
	if (is_pkt_belong_to_flow(root->flow, pkt)) {
		*res = root;
		return true;
	}
	return search_nodes_rec(root->left_child, pkt, res) || search_nodes_rec(root->right_child, pkt, res);
}
flow_struct* search_flow(heap_struct* heap, packet* pkt)
{
	heap_node* res = NULL;
	search_nodes_rec(heap->root, pkt, &res); //if flow not in heap: res = NULL. else: res = flow;
	if (res != NULL)
		return res->flow;
	return NULL;
}
heap_node* get_end_of_heap(heap_node* root,int num_of_levels_to_go, int new_child_num)
{
	//new_child_num bit at index num_of_levels_to_go, telling if to go left(0) or right(1)
	if (num_of_levels_to_go == 0) //parent
		return root;
	else if ((new_child_num >> num_of_levels_to_go) % 2 == 0) //go left
		return get_end_of_heap(root->left_child, num_of_levels_to_go - 1, new_child_num);
	return get_end_of_heap(root->right_child, num_of_levels_to_go - 1, new_child_num); //go right
}
void insret_flow_to_heap(heap_struct* heap, flow_struct *flow)
{
	heap_node *last_parent = NULL, *new_node = create_heap_node();
	if (heap->root->left_child == NULL || heap->root->right_child == NULL)
		last_parent = heap->root;
	else 
		last_parent = get_end_of_heap(heap->root,ilogb(heap->size+1)-1,heap->size+1);
	new_node->flow = flow;
	if (last_parent->left_child == NULL)
		last_parent->left_child = new_node;
	else
		last_parent->right_child = new_node;
}
int get_total_weight(heap_node* root)
{
	if (root == NULL)
		return 0;
	if (!is_flow_empty(root->flow))
		return root->flow->weight + get_total_weight(root->left_child) + get_total_weight(root->right_child);
	else
		return get_total_weight(root->left_child) + get_total_weight(root->right_child);
}

int insert_pkt_to_heap(heap_struct* heap, packet *pkt)
{
	bool is_total_weight_changed = false;
	if (is_heap_empty(heap)) {
		heap->root = create_heap_node();
		if ((heap->root->flow = insert_pkt_to_new_flow(pkt)) == NULL)
			return EXIT_FAILURE;
		///////////////////////////////////////////////////////////////////////////
		heap->root->flow->gps_parameters.time_remain = (float)pkt->length;
		///////////////////////////////////////////////////////////////////////////
		is_total_weight_changed = true;
		heap->size++;
	}
	else {
		flow_struct* flow = search_flow(heap, pkt);
		if (flow == NULL) {  //new flow
			flow = insert_pkt_to_new_flow(pkt);
			if (flow == NULL)
				return EXIT_FAILURE;
			///////////////////////////////////////////////////////////////////////////
			flow->gps_parameters.time_remain = (float)pkt->length * (heap->total_weight+ pkt->weight) / pkt->weight;
			///////////////////////////////////////////////////////////////////////////
			insret_flow_to_heap(heap, flow);
			is_total_weight_changed = true;
			heap->size++;
		}
		else {
			is_total_weight_changed = is_flow_empty(flow);
			
			insert_pkt_to_flow(flow, pkt);
		}
	}
	if (is_total_weight_changed){
		heap->total_weight = get_total_weight(heap->root);
		//TODO: update GPS
		/*
			calc GPS to each node and fix the heap
		*/
	}
	return EXIT_SUCCESS;
}
void heap_test()
{
	heap_struct heap;
	init_heap(&heap);
	packet *pkt = get_info_to_packet("0 70.246.64.70 14770 4.71.70.4 11970 70\n");
	insert_pkt_to_heap(&heap, pkt);
	//bool a = delete_first_pkt_in_flow(heap.root->flow);
	pkt = get_info_to_packet("200 70.246.64.70 14770 4.71.70.4 11970 70 500.0\n");
	insert_pkt_to_heap(&heap, pkt);
	//a = delete_first_pkt_in_flow(heap.root->flow);
	pkt = get_info_to_packet("2612 173.253.160.44 36503 165.173.44.44 29583 173\n");
	insert_pkt_to_heap(&heap, pkt);
	//pkt = get_info_to_packet("2666 173.253.160.44 36503 165.173.44.44 29583 100\n");
	//insert_pkt_to_heap(&heap, pkt);
	pkt = get_info_to_packet("2770 1.1.1.1 36503 165.173.44.44 29583 5000 5.0\n");
	insert_pkt_to_heap(&heap, pkt);
	float total_weight_for_debug = (float)get_total_weight(heap.root);
	//float b = search_for_minimum_time_left_in_heap_recursive_float(heap.root,total_weight_for_debug);
	update_remaining_length_for_all_heap_recursive(heap.root, total_weight_for_debug, 7.0);
	heap.root = update_min_time_and_place_for_all_heap_recursive(heap.root, total_weight_for_debug, 7.0);
	
	//pkt = get_info_to_packet("2770 2.2.2.2 36503 165.173.44.44 29583 10 2.0\n");
	//insert_pkt_to_heap(&heap, pkt);
	//total_weight_for_debug = (float)get_total_weight(heap.root);
	//heap.root = update_min_time_for_all_heap_recursive(heap.root, total_weight_for_debug, 7.0);


	//free(pkt);
	//TODO: NEED TO FREE ALL OF THE PACKETS !
	return;
}