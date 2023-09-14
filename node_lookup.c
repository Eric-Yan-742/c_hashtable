#include <string.h>
#include "node.h"

node *node_lookup(node *front, char *id) {
	// TODO: step through the chain pointed to by front
	// use function like strcmp to compare the id to the current node
	// if found return a pointer to the node, else return NULL
	
   while(front != NULL) {
      if(strcmp(front -> id, id) == 0) {
         return front;
      }
      front = front -> next;
   }

	return NULL; 
}
