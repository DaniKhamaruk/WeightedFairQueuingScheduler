#pragma once
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
packet* initialize_packet();
void fill_src_or_dst_addr_in_packet(packet* p_packet, int* p_addr, bool is_it_src);
int get_time_or_port_from_string(char* p_line, int* p_addr_of_index);
void get_src_or_dst_addr_from_line(char* p_line, int* p_index_to_read_from, int* buffer_to_fill);
void fill_packet_with_info(packet* p_packet_to_fill, int time, int* src_addr, int* dst_addr,
	int src_port, int dst_port, int length, float weight);
void print_packet(packet* p_packet_to_print);
packet* get_info_to_packet(char* p_line);