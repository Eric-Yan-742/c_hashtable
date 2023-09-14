#include <stdlib.h>
#include <string.h>
#include "node.h"

node *insert_node(node *front, char* id, double x, double y) {
	// TODO: create a node, copy in the parameter fields
	// make sure that you do a deep copy
   node *newNode;
   if((newNode = malloc(sizeof(node))) == NULL) {
      return NULL;
   }
   if((newNode->id = malloc(strlen(id) + 1)) == NULL) {
      return NULL;
   }
   strcpy(newNode->id, id);
   newNode->xcoord = x;
   newNode->ycoord = y;

	// TODO: link the new node into the chain 
   newNode->next = front;
	// TODO: return the new head of the chain if the function succeeded
	return newNode;
}


