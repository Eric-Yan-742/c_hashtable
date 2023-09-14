#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

#define MAX_LINELEN 100 
#define FILE_OPEN_ERR_MSG "error in load_table while opening file %s\n"
#define DUPLICATE_ID_MSG "load_table duplicate entry: %s\n"
#define INSERTION_ERROR_MSG "load_table could not create node for %s\n"

int load_table(node **htable, unsigned long int tabsz, char *filename) {

	FILE *fp = NULL;
	// TODO: open the file and check that it was successful
   if((fp = fopen(filename, "r")) == NULL) {
      fprintf(stderr, FILE_OPEN_ERR_MSG, filename);
      return -1;
   }

	// TODO: loop through the file and read one line at a time using fgets
	// see manual page for fgets for information on parameters
	char buf[MAX_LINELEN + 1]; // input buffer for fgets
   const char *delim = ",";
	while (fgets(buf, MAX_LINELEN + 1, fp) == buf) {
		// TODO: for each line, use strtok to break it into columns
		// (convert the second and third columns to doubles)
      char * id = strtok(buf, delim);
      char *second_col_str = strtok(NULL, delim);
      char *third_col_str = strtok(NULL, delim);
      double x = atof(second_col_str);
      double y = atof(third_col_str);
		// TODO: get the corresponding chain for this entry
      unsigned long hashVal = hash(id) % tabsz;
		node *chain = *(htable + hashVal);
		// TODO: check that the node doesn't already exist in table
      if(node_lookup(chain, id) != NULL) { //Found duplicate entries
         fprintf(stderr, DUPLICATE_ID_MSG, id);
         continue;
      }
		// TODO: add non-duplicate node to the front of its chain
      *(htable + hashVal) = insert_node(chain, id, x, y);
	}
   fclose(fp);
	return 0;
}
