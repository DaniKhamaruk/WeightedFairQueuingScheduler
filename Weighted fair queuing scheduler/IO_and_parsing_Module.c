#include "IO_and_parsing_Module.h"


void fill_src_or_dst_addr_in_packet(packet *p_packet,int* p_addr,bool is_it_src) {
	if (is_it_src) {
		for (int i = 0; i < ADDR_IN_PACKET_SIZE; i++) {
			p_packet->src_addr[i] = p_addr[i];
		}
	}
	else {
		for (int i = 0; i < ADDR_IN_PACKET_SIZE; i++) {
			p_packet->dst_addr[i] = p_addr[i];
		}
	}
}
packet* initialize_packet() {
	packet* new_packet=NULL;
	if (NULL == (new_packet = calloc(1, sizeof(packet)))) {
		printf("Couldn't make new packet\n");
		return NULL;
	}
	return new_packet;
}
int get_time_or_port_from_string(char *p_line,int* p_addr_of_index) {
	int time = 0,i=0;
	i = *p_addr_of_index;
	while (ASCII_SPACE!= p_line[i]) {
		time = time * 10 +p_line[i]-ASCII_NUMBER_OFFSET;
		i++;
	}
	*p_addr_of_index = i+1;
	return time;
}
int get_length_from_string(char* p_line, int* p_addr_of_index) {
	int length = 0, i = 0;
	i = *p_addr_of_index;
	while (ASCII_SPACE != p_line[i]&&ASCII_CR_LF!= p_line[i]) {
		length = length * 10 + p_line[i] - ASCII_NUMBER_OFFSET;
		i++;
	}
	if (ASCII_SPACE == p_line[i]) {
		*p_addr_of_index = i + 1;
	}
	else {
		*p_addr_of_index = i;
	}
	return length;
}
void get_src_or_dst_addr_from_line(char* p_line,int* p_index_to_read_from,int* buffer_to_fill) {
	int index_to_read_from = *p_index_to_read_from;
	int part_of_addr =0, j = 0;
	while (ASCII_SPACE != p_line[index_to_read_from]) {
		while ((ASCII_DOT != p_line[index_to_read_from])&& (ASCII_SPACE != p_line[index_to_read_from])) {
			part_of_addr = part_of_addr * 10 + p_line[index_to_read_from] - ASCII_NUMBER_OFFSET;
			index_to_read_from++;
		}
		if (ASCII_SPACE != p_line[index_to_read_from]) {
			index_to_read_from++;
		}
		buffer_to_fill[j] = part_of_addr;
		j++;
		part_of_addr = 0;
	}
	*p_index_to_read_from = index_to_read_from+1;
	return;
}
void fill_packet_with_info(packet* p_packet_to_fill,int time,int* src_addr, int* dst_addr,
	int src_port,int dst_port,int length,float weight) {
	p_packet_to_fill->time = time;
	fill_src_or_dst_addr_in_packet(p_packet_to_fill, src_addr, true);
	p_packet_to_fill->src_port = src_port;
	fill_src_or_dst_addr_in_packet(p_packet_to_fill, dst_addr, false);
	p_packet_to_fill->dst_port = dst_port;
	p_packet_to_fill->length = length;
	p_packet_to_fill->weight = weight;
}
void print_packet(packet* p_packet_to_print) {
	printf("Time:%d\n", p_packet_to_print->time);
	printf("Source Address:%d.%d.%d.%d\n", p_packet_to_print->src_addr[0], p_packet_to_print->src_addr[1]
	, p_packet_to_print->src_addr[2], p_packet_to_print->src_addr[3]);
	printf("Source Port:%d\n", p_packet_to_print->src_port);
	printf("Destination Address:%d.%d.%d.%d\n", p_packet_to_print->dst_addr[0], p_packet_to_print->dst_addr[1]
		, p_packet_to_print->dst_addr[2], p_packet_to_print->dst_addr[3]);
	printf("Destination Port:%d\n", p_packet_to_print->dst_port);
	printf("Length:%d\n", p_packet_to_print->length);
	printf("Weight:%.3f\n\n", p_packet_to_print->weight);
}
float get_weight(char* p_line, int* p_index_to_read_from, bool * is_weight_given) {
	float weight = 0.0, new_remainder = 0.0;
	int whole_part = 0, remainder = 0, i = 0, j = 1;
	if (ASCII_CR_LF == p_line[*p_index_to_read_from]) {
		*is_weight_given = false;
		return (float)1;
	}
	else {
		*is_weight_given = true;
		i = *p_index_to_read_from;
		while (ASCII_DOT != p_line[i]) {
			whole_part = whole_part * 10 + (p_line[i] - ASCII_NUMBER_OFFSET);
			i++;
		}
		i++;
		while (ASCII_CR_LF != p_line[i]) {
			remainder = remainder * 10 + (p_line[i] - ASCII_NUMBER_OFFSET);
			j *= 10;
			i++;
		}
			
	}
	new_remainder = (float)remainder;
	new_remainder /= (float)j;
	weight = (float)(whole_part)+new_remainder;
	return weight;
}
packet* get_info_to_packet(char* p_line) {
	int index_in_the_line = 0, time, dst_addr[ADDR_IN_PACKET_SIZE] = { 0 },
		src_port = 0, dst_port = 0, length = 0;
	float weight = 1.0;
	int src_addr[ADDR_IN_PACKET_SIZE] = { 0 };
	packet* new_packet = initialize_packet();
	if (NULL == new_packet) {
		return NULL;
	}
	time = get_time_or_port_from_string(p_line, &index_in_the_line);
	get_src_or_dst_addr_from_line(p_line, &index_in_the_line,src_addr);
	src_port = get_time_or_port_from_string(p_line, &index_in_the_line);
	get_src_or_dst_addr_from_line(p_line, &index_in_the_line, dst_addr);
	dst_port = get_time_or_port_from_string(p_line, &index_in_the_line);
	length = get_length_from_string(p_line, &index_in_the_line);
	weight = get_weight(p_line, &index_in_the_line, &new_packet->is_weight_given);
	fill_packet_with_info(new_packet, time, src_addr, dst_addr, src_port, dst_port, length, weight);
	memcpy(new_packet->pkt_str, p_line, strlen(p_line));
	new_packet->is_pkt_in_WFQ = false;
	return new_packet;
}