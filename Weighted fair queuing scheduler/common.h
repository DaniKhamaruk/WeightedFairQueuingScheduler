#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ADDR_IN_PACKET_SIZE 4
#define MAX_LINE_SIZE 10000//TOOD:need to check this
#define ASCII_NUMBER_OFFSET 48
#define ASCII_SPACE 32
#define ASCII_DOT 46
#define ASCII_CR_LF 10
typedef struct packet {
	int time, src_port, dst_port, length;
	float weight;
	int src_addr[ADDR_IN_PACKET_SIZE];
	int dst_addr[ADDR_IN_PACKET_SIZE];
}packet;
typedef struct node {
	packet* packet;
	struct node* next_node;
}node;
typedef struct link_id {
	int src_port, dst_port;
	int src_addr[ADDR_IN_PACKET_SIZE];
	int dst_addr[ADDR_IN_PACKET_SIZE];
	int first_time;
}link_id;
typedef struct flow_struct {
	node* head;
	node* tail;
	link_id id;
	float weight;
	int num_of_pkts;
}flow_struct;
typedef struct heap_struct {
	flow_struct* head;
}heap_struct;