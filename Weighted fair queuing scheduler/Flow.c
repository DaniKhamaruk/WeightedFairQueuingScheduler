#include "Flow.h"
#include "Queue_Module.h"
#include "IO_and_parsing_Module.h"

void init_link_id(flow_id*id)
{
	id->first_time = _CRT_INT_MAX;
	id->src_port = 0;
	id->dst_port = 0;
	for (int i = 0; i < ADDR_IN_PACKET_SIZE; i++) {
		id->src_addr[i] = 0;
		id->dst_addr[i] = 0;
	}
}
flow_struct* initialize_flow() {
	flow_struct* new_flow = NULL;
	if (NULL == (new_flow = calloc(1, sizeof(flow_struct)))) {
		printf("Couldn't make new flow\n");
		return NULL;
	}
	new_flow->weight = 1.0;
	init_link_id(&new_flow->id);
	return new_flow;
}
bool is_flow_empty(flow_struct* flow)
{
	return flow->num_of_pkts == 0;
}
void insert_pkt_to_flow(flow_struct* flow, packet* pkt)
{
	if (is_flow_empty(flow)) {
		flow->gps_parameters.length_remain = pkt->length;
		flow->weight = pkt->weight;
	}
	insert_node_in_queue(&flow->head, pkt, &flow->tail);
	flow->num_of_pkts++;
}
void insert_flow_id(flow_id* id, packet *pkt)
{
	for (int i = 0; i < ADDR_IN_PACKET_SIZE; i++) {
		id->src_addr[i] = pkt->src_addr[i];
		id->dst_addr[i] = pkt->dst_addr[i];
	}
	id->src_port = pkt->src_port;
	id->dst_port = pkt->dst_port;
	id->first_time = pkt->time;
}
flow_struct* insert_pkt_to_new_flow(packet* pkt)
{
	flow_struct* new = initialize_flow();
	if (new != NULL) {
		insert_flow_id(&new->id, pkt);
		insert_pkt_to_flow(new, pkt);
		new->gps_parameters.length_remain = (float)pkt->length;
	}
	return new;
}
bool ip_compare(flow_id id, packet *pkt)
{
	for (int i = 0; i < ADDR_IN_PACKET_SIZE; i++) {
		if (id.src_addr[i] != pkt->src_addr[i] || id.dst_addr[i] != pkt->dst_addr[i])
			return false;
	}
	return true;
}
bool port_compare(flow_id id, packet* pkt)
{
	return ((id.src_port == pkt->src_port) && (id.dst_port == pkt->dst_port));
}
bool is_pkt_belong_to_flow(flow_struct* flow, packet* pkt)
{
	if (flow == NULL || pkt == NULL)
		return false;
	flow_id id = flow->id;
	return (ip_compare(id, pkt) && port_compare(id, pkt));
}
bool delete_first_pkt_in_flow(flow_struct* flow)
{
	node* node_to_delete = flow->head;
	bool is_weight_changed = false;
	if (!is_flow_empty(flow)) {
		flow->head = flow->head->next_node;
		free(node_to_delete->packet);
		free(node_to_delete);
		if (flow->head != NULL) {
			//flow->head->next_node = NULL;
			is_weight_changed = (flow->weight != flow->head->packet->weight);
			flow->weight = flow->head->packet->weight;
		}
		flow->num_of_pkts--;
		if (is_flow_empty(flow)) {
			flow->head = NULL;
			flow->tail = NULL; 
		}
	}
	return is_weight_changed;
}
