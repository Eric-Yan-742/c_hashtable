#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"

#define MIN_TAB_SZ 3
#define DEFAULT_TAB_SZ 1873
#define QUERY_SUCCESS_FORMAT "found tree id=%s, x=%.5f, y=%.5f\n" 
#define QUERY_FAILURE_FORMAT "could not find tree with id=%s\n"

int main(int argc, char **argv) {
	int s_flag;
	unsigned long tabsz;
	// TODO: parse opts with getopt and initialize these variables
   s_flag = 0;
   tabsz = DEFAULT_TAB_SZ;
   int c;
   while((c = getopt(argc, argv, "st:")) != -1) {
      switch(c) {
         case 's':
            s_flag = 1;
            break;
         case 't':
            tabsz = strtoul(optarg, NULL, 10);
            break;
         case '?':
            return EXIT_FAILURE;
         default:
            abort();
      }
   }
   if(tabsz < MIN_TAB_SZ) {
      tabsz = DEFAULT_TAB_SZ;
   }

   
	// TODO: initialze htable
	// using calloc so all buckets are initialized to NULL
	node **htable = calloc(tabsz, sizeof(node*));
	if (htable == NULL) {
		return EXIT_FAILURE;
	}
	
	// TODO: get filename and call load_table;
	
   char *filename = argv[optind];

   if (load_table(htable, tabsz, filename) == -1) {
      fprintf(stderr, "error in load_table\n");
      free(htable);
      return EXIT_FAILURE;
   }
   
   /* Print out the hash table (for test) */
   //for(unsigned long i = 0; i < tabsz; i++) {
   //   printf("No. %lu bucket\n", i);
   //   for(node *j = *(htable + i); j != NULL; j = j->next) {
   //      printf("id: %s, x: %f, y: %f\n", j->id, j->xcoord, j->ycoord);
   //   }
   //}
   size_t bufsz = 0;
   char *buf = NULL; 
   
   // read one line at a time from stdin, do a lookup for that id
    
   ssize_t bytes;
   int successCnt = 0;
   while ((bytes = getline(&buf, &bufsz, stdin)) > 0) {
      // replace the \n, if it exists (for hashing)
      if (buf[bytes - 1] == '\n') buf[bytes - 1] = '\0';

      // TODO: read a line from stdin and perform a lookup
      // if the tree is found, print its x and y to stdout
      // using QUERY_SUCCESS_FORMAT
      //
      // if the tree is not found, print a message to **stdout**
      // using QUERY_FAILURE_FORMAT
      //
      // keep track of the number of successful queries
      node *res = NULL;
      for(unsigned long i = 0; i < tabsz; i++) {
         res = node_lookup(*(htable + i), buf);
         if(res != NULL) {
            break;
         }
      }
      if(res == NULL) { //If tree is not found
         fprintf(stdout, QUERY_FAILURE_FORMAT, buf);          
      } else { //If tree is found
         fprintf(stdout, QUERY_SUCCESS_FORMAT, buf, res->xcoord, res->ycoord);
         successCnt++;
      }
   }
   printf("%d successful queries\n", successCnt);

   // if -s called then print stats
   if (s_flag) {
      // TODO: output the stats 
      print_info(htable, tabsz);
   }

   // TODO: free all allocated memory associated with the table 
   // using delete_table()
   delete_table(htable, tabsz);
   htable = NULL;
   free(buf);  // free the buffer allocated by getline()
   buf = NULL;

   return EXIT_SUCCESS;
} 
