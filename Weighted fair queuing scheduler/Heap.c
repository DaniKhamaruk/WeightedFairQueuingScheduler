#include <assert.h>
#include "Heap.h"

void init_heap(heap_struct *heap)
{
	heap->head = NULL;
}
bool is_heap_empty(heap_struct heap)
{
	return (heap.head == NULL);
}
int insert_pkt_to_heap(heap_struct* heap)
{
	return EXIT_FAILURE;
}
void heap_test()
{
	heap_struct heap;
	init_heap(&heap);
	assert(heap.head == NULL);
	assert(is_heap_empty(heap) == true && "heap is empty");
	packet *pkt = get_info_to_packet("0 70.246.64.70 14770 4.71.70.4 11970 70\n");
	assert(insert_pkt_to_heap(&heap) == EXIT_SUCCESS);
	assert(is_heap_empty(heap) == false && "heap is not empt");
}