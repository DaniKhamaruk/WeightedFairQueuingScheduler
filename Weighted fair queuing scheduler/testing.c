#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "IO_and_parsing_Module.h"
#include "Stack_Module.h"

void test_main() {


	char p_line[MAX_LINE_SIZE] = { 0 };
	int index_in_the_line = 0;
	packet* local = NULL;
	while (NULL != fgets(p_line, MAX_LINE_SIZE, stdin)) {
		local = get_info_to_packet(p_line);
		print_packet(local);
	}
}