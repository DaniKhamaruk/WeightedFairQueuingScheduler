#pragma once
#include "common.h"

#include "Flow.h"
#include "Queue_Module.h"

bool is_flow_empty(flow_struct* flow);
void insert_pkt_to_flow(flow_struct* flow, packet* pkt);
void insert_flow_id(flow_id* id, packet* pkt);
flow_struct* insert_pkt_to_new_flow(packet* pkt);
bool is_pkt_belong_to_flow(flow_struct* flow, packet* pkt);
node* get_pkt_from_head_of_flow(flow_struct* flow);
bool delete_first_pkt_in_flow(flow_struct* flow);