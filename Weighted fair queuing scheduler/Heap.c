#include <assert.h>
#include "Heap.h"
#include "Flow.h"
#include "IO_and_parsing_Module.h"

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
	heap->head = NULL;
}
bool is_heap_empty(heap_struct *heap)
{
	return (heap->head == NULL);
}
bool search_nodes_rec(heap_node* head, packet* pkt, heap_node* res)
{
	if (head == NULL)
		return false;
	if (is_pkt_belong_to_flow(head->flow, pkt)) {
		res = head;
		return true;
	}
	return search_nodes_rec(head->left_flow, pkt, res) || search_nodes_rec(head->right_flow, pkt, res);
}
flow_struct* search_flow(heap_struct* heap, packet* pkt)
{
	heap_node* res = NULL;
	search_nodes_rec(heap->head, pkt, res); //if flow not in heap: res = NULL. else: res = flow;
	if (res != NULL)
		return res->flow;
	return NULL;
}
void insret_flow_to_heap(heap_struct* heap, flow_struct *flow)
{

}
int insert_pkt_to_heap(heap_struct* heap, packet *pkt)
{
	if (is_heap_empty(heap)) {
		heap->head = create_heap_node();
		if ((heap->head->flow = insert_pkt_to_new_flow(pkt)) == NULL)
			return EXIT_FAILURE;
	}
	else {
		flow_struct* flow = search_flow(heap, pkt);
		if (flow == NULL) {  //new flow
			flow = insert_pkt_to_new_flow(pkt);
			if (flow == NULL)
				return EXIT_FAILURE;
			insret_flow_to_heap(heap, flow);
		}
		else {
			insert_pkt_to_flow(flow, pkt);
			//TODO: update GPS
		}
	}
	return EXIT_SUCCESS;
}
void heap_test()
{
	heap_struct heap;
	init_heap(&heap);
	packet *pkt = get_info_to_packet("0 70.246.64.70 14770 4.71.70.4 11970 70\n");
	insert_pkt_to_heap(&heap, pkt);
	return;
}