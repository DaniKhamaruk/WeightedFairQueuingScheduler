#include <assert.h>
#include "Heap.h"
#include "Flow.h"
#include "IO_and_parsing_Module.h"

void init_heap(heap_struct *heap)
{
	heap->head = NULL;
}
bool is_heap_empty(heap_struct *heap)
{
	return (heap->head == NULL);
}
flow_struct* search_flow(heap_struct* heap)
{
	return NULL;
}
void insret_flow_to_heap(heap_struct* heap, flow_struct *flow)
{

}
int insert_pkt_to_heap(heap_struct* heap, packet *pkt)
{
	if (is_heap_empty(heap)) {
		if ((heap->head = insert_pkt_to_new_flow(pkt)) == NULL)
			return EXIT_FAILURE;
	}
	else {
		flow_struct* flow = search_flow(heap);
		if (flow == NULL) {  //new flow
			flow = insert_pkt_to_new_flow(pkt);
			if (flow == NULL)
				return EXIT_FAILURE;
			insret_flow_to_heap(heap, flow);
		}
		else {
			insert_pkt_to_flow(flow, pkt);
		}
	}
	return EXIT_SUCCESS;
}
void heap_test()
{
	heap_struct heap;
	init_heap(&heap);
	assert(heap.head == NULL);
	assert(is_heap_empty(&heap) == true && "heap is empty");
	packet *pkt = get_info_to_packet("0 70.246.64.70 14770 4.71.70.4 11970 70\n");
	assert(insert_pkt_to_heap(&heap, pkt) == EXIT_SUCCESS);
	assert(is_heap_empty(&heap) == false && "heap is not empt");
}