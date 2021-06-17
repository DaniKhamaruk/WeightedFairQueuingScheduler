#pragma once
#include "common.h"
#include "Queue_Module.h"

void heap_test();

void init_heap(heap_struct* heap);
int insert_pkt_to_heap(heap_struct* heap, packet* pkt);
void update_heap(heap_struct* heap, float delta_time_to_update, flow_struct* WFQ);
heap_node* search_flow_to_send_his_pkt(heap_node* root, float total_weight);
packet* find_new_pkt_to_WFQ(flow_struct* flow);
packet* get_pkt_from_head_of_flow(flow_struct* flow);
void insert_new_pkt_to_WFQ(flow_struct* WFQ, flow_struct* root_flow);
