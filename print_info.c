#include <stdio.h>
#include <limits.h>
#include "node.h"

#define TABSZ_MSG "Table size: %lu\n"
#define TOTAL_ENTRIES_MSG "Total entries: %lu\n"
#define LONGEST_MSG "Longest chain: %lu\n"
#define SHORTEST_MSG "Shortest chain: %lu\n"
#define EMPTY_MSG "Empty buckets: %lu\n"
#define TREES_WITHIN_REGION_MSG "Total trees within given region: %lu\n"


void print_info(node **htable, unsigned long tabsz) {
	// TODO: walk down the indices of the htable
	// iterate through each chain and update statistics
	// print out statistics at end
	//
	// NOTE: all your statistics variables should be of type
	// unsigned long
	//
	// NOTE: you may use ULONG_MAX if you want
	// (maximum value for unsigned long int)
	
	(void) htable; // suppress unused variable warnings
	(void) tabsz; // TODO: delete these once you start implementation
   unsigned long total_entries = 0;
   unsigned long longest = 0;
   unsigned long shortest = -1;
   unsigned long emptyCnt = 0;
   for(unsigned long i = 0; i < tabsz; i++) {
      unsigned chainLen = 0;
      for(node *j = *(htable + i); j != NULL; j = j->next, chainLen++) {}
      total_entries += chainLen;
      if(chainLen == 0) {
         emptyCnt++;
      }
      if(chainLen < shortest) {
         shortest = chainLen;
      }
      if(chainLen > longest) {
         longest = chainLen;
      }
   }
   printf(TABSZ_MSG, tabsz);
   printf(TOTAL_ENTRIES_MSG, total_entries);
   printf(LONGEST_MSG, longest);
   printf(SHORTEST_MSG, shortest);
   printf(EMPTY_MSG, emptyCnt);
}
