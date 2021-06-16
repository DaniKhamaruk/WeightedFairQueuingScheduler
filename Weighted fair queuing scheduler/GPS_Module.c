#include "GPS_Module.h"



void run_GPS_algorithem(heap_node* flow,int delta_time) {

}
//--------------------------------------------------------------

int minimum_time_out_of_two_int(int first_number,int seconed_number) {
	if (first_number < seconed_number) {
		return first_number;
	}
	else
		return seconed_number;
}
int minimum_time_out_of_three_int(int time_left, int time_right, int this_node_time) {
	int min_time = INFINITE_TIME_INT;
	min_time = minimum_time_out_of_two_int(time_left, time_right);
	min_time = minimum_time_out_of_two_int(min_time, this_node_time);
	return min_time;
}


int search_for_minimum_time_left_in_heap_recursive_int(heap_node* current_heap_node) {
	if (NULL == current_heap_node) {
		return INFINITE_TIME_INT;
	}
	int time_left = search_for_minimum_time_left_in_heap_recursive_int(current_heap_node->left_child);
	int time_right = search_for_minimum_time_left_in_heap_recursive_int(current_heap_node->right_child);
	int this_node_time = current_heap_node->flow->gps_parameters.time_to_finish;
	return minimum_time_out_of_three_int(time_left, time_right, this_node_time);
}

//--------------------------------------------------------------

float minimum_time_out_of_two_float(float first_number, float seconed_number) {
	if (first_number < seconed_number) {
		return first_number;
	}
	else
		return seconed_number;
}
float minimum_time_out_of_three_float(float time_left, float time_right, float this_node_time) {
	float min_time = INFINITE_TIME_FLOAT;
	min_time = minimum_time_out_of_two_float(time_left, time_right);
	min_time = minimum_time_out_of_two_float(min_time, this_node_time);
	return min_time;
}

float search_for_minimum_time_left_in_heap_recursive_float(heap_node* current_heap_node,float total_heap_weight) {
	if (NULL == current_heap_node) {
		return INFINITE_TIME_FLOAT;
	}
	float time_left = search_for_minimum_time_left_in_heap_recursive_float(current_heap_node->left_child, total_heap_weight);
	float time_right = search_for_minimum_time_left_in_heap_recursive_float(current_heap_node->right_child, total_heap_weight);
	float this_node_time = current_heap_node->flow->gps_parameters.length_remain;
	this_node_time = this_node_time * current_heap_node->flow->weight / total_heap_weight;
	return minimum_time_out_of_three_float(time_left, time_right, this_node_time);
}
//--------------------------------------------------------------

float get_weight_portion_from_packet(packet* pkt,float total_weight_of_heap) {
	float weight_portion = (pkt->weight) / total_weight_of_heap;
	return weight_portion;
}
heap_node* swap_nodes(heap_node* current_heap_node) {
	heap_node *temp_heap_node =current_heap_node, *temp_right_child_node = NULL, *temp_left_child_node = NULL;
	if (NULL != current_heap_node->left_child) {
		if (current_heap_node->flow->gps_parameters.length_remain > current_heap_node->left_child->flow->gps_parameters.length_remain) {
			temp_left_child_node = current_heap_node->left_child->left_child;
			temp_right_child_node = current_heap_node->left_child->right_child;
			temp_heap_node = current_heap_node->left_child;

			temp_heap_node->right_child = current_heap_node->right_child;
			temp_heap_node->left_child = current_heap_node;
			current_heap_node->left_child = temp_left_child_node;
			current_heap_node->right_child = temp_right_child_node;
		}
	}
	if (NULL != current_heap_node->right_child) {
		if (current_heap_node->flow->gps_parameters.length_remain > current_heap_node->right_child->flow->gps_parameters.length_remain) {
			temp_left_child_node = current_heap_node->right_child->left_child;
			temp_right_child_node = current_heap_node->right_child->right_child;
			temp_heap_node = current_heap_node->right_child;

			temp_heap_node->right_child = current_heap_node;
			temp_heap_node->left_child = current_heap_node->left_child;
			current_heap_node->left_child = temp_left_child_node;
			current_heap_node->right_child = temp_right_child_node;
		}
	}
	return temp_heap_node;
}
heap_node* update_min_time_for_all_heap_recursive(heap_node* current_heap_node,float total_weight_of_heap,
	float delta_time_to_run) {
	if (NULL != current_heap_node->left_child) {
		current_heap_node->left_child=update_min_time_for_all_heap_recursive(current_heap_node->left_child, total_weight_of_heap, delta_time_to_run);
	}
	if (NULL != current_heap_node->right_child) {
		current_heap_node->right_child=update_min_time_for_all_heap_recursive(current_heap_node->right_child, total_weight_of_heap, delta_time_to_run);
	}
	float weight_portion = get_weight_portion_from_packet(current_heap_node->flow->head->packet,total_weight_of_heap);
	current_heap_node->flow->gps_parameters.length_remain -= weight_portion*delta_time_to_run;
	return swap_nodes(current_heap_node);
}
