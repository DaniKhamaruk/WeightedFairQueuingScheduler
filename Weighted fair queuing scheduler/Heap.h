#pragma once
#include "Queue_Module.h"

void heap_test();


int insert_pkt_to_heap(heap_struct* heap, packet* pkt);
int get_total_weight(heap_node* root);

