#pragma once
#include "common.h"
#include "Queue_Module.h"

void heap_test();

void init_heap(heap_struct* heap);
int insert_pkt_to_heap(heap_struct* heap, packet* pkt);
void update_heap(heap_struct* heap, float delta_time_to_update, flow_struct* WFQ);
heap_node* search_flow_to_send_his_pkt(heap_node* root);
