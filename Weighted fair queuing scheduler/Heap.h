#pragma once
#include "Queue_Module.h"

void heap_test();


int insert_pkt_to_heap(heap_struct* heap, packet* pkt);
void update_heap(heap_struct* heap, float delta_time_to_update);
