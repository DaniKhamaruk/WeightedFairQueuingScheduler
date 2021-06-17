#pragma once
#include "common.h"




float minimum_time_out_of_two_float(float first_number, float seconed_number);
float minimum_time_out_of_three_float(float time_left, float time_right, float this_node_time);
float search_for_minimum_time_left_in_heap_recursive_float(heap_node* current_heap_node, float total_heap_weight);
float get_weight_portion_from_packet(packet* pkt, float total_weight_of_heap);
heap_node* update_min_time_and_place_for_all_heap_recursive(heap_node* current_heap_node, float total_weight_of_heap);
void update_remaining_length_for_all_heap_recursive(heap_node* current_heap_node, float total_weight_of_heap,
	float delta_time_to_run);