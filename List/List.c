// ---------------------------------------------------------------------
// List.c
// List ADT
// ---------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

// Structs

//NodeObj
typedef struct NodeObj {
int data;
struct NodeObj* previous;
struct NodeObj* next;
} NodeObj;

//ListObj
typedef struct ListObj{
Node front;
Node back;
int length;
} ListObj;

// Constructors-Destructors--------------------------------------------

//newNode()
Node newNode(int newData){
	Node N = malloc(sizeof(NodeObj));
	N->data = newData;
	N->previous = NULL;
	N->next = NULL;
	return(N);
}

//freeNode()
void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}

//newList
// returns a List which points to a new empty list object
List newList(void){
	List L=malloc(sizeof(ListObj));
	L->front=NULL;
	L->back=NULL;
	L->length=0;
	return(L);
}

//freeList()
// frees all heap memory associated with its List* argument,
// and sets *pL to NULL
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL){
		while(length(*pL)>0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL=NULL;
	}
}

//---------------------------------------------------------------------

// Access functions

// length()
// Returns the number of nodes in this List.
int length(List L){
		if (L==NULL){
			printf("Calling length() on NULL List reference");
			exit(1);
		}

	return(L->length);
} 

// frontValue()
// Returns the integer in the front Node.
// Precondition: L has at least one Node on it.
int frontValue(List L){
	if (L==NULL){
		printf("Calling frontValue() on NULL List reference");
		exit(1);
	}

	if(L->length <= 0){
		printf("Calling frontValue() on empty List");
		exit(1);
	}

	int val = L->front->data;
	return(val);
}

// backValue
// Returns the integer in the back Node.
// Precondition: L has at least one Node on it.
int backValue(List L){
	if (L==NULL){
		printf("Calling backValue() on NULL List reference");
		exit(1);
	}

	if(L->length <= 0){
		printf("Calling backValue() on empty List");
		exit(1);
	}

	int val = L->back->data;
	return(val);
}

// getValue()
// Returns the integer in Node N.
// Precondition: N is not NULL
int getValue(Node N){
	if(N == NULL){
		printf("Calling getValue() on NULL Node reference");
		exit(1);
	}

	return(N->data);
}

// equals()
// Returns 1 if List A and List B are the same integer
// sequence, otherwise returns 0.
int equals(List A, List B){
	if (A==NULL){
		printf("Calling equals() on NULL List reference");
		exit(1);
	}
	if (B==NULL){
		printf("Calling equals() on NULL List reference");
		exit(1);
	}
	if(A->length != B->length)
		return(0);
	Node a=A->front;
	Node b=B->front;
	while(a->next != NULL){
		if(a->data != b->data)
			return(0);
		a=a->next;
		b=b->next;
	}
	return(1);
}

//------------------------------------------------------------------

// Manipulation procedures 

// clear()
// Resets this List to the empty state.
void clear(List L){
	if (L==NULL){
		printf("Calling clear() on NULL List reference");
		exit(1);
	}
	
	while(length(L)>0){
		deleteFront(L);
	
	}
} 

// getFront
// If List is non-empty, returns the front Node, without
// changing the List. Otherwise, does nothing.
Node getFront(List L){
	if(L==NULL){
		printf("Calling getFront() on NULL List reference");
		exit(1);
	}
	if(L->length<=0){
		printf("Calling getFront() on empty List");
		exit(1);
	}

	return(L->front);
}

// getBack()
// If List is non-empty, returns the back Node, without
// changing the List. Otherwise, does nothing.
Node getBack(List L){
	if(L==NULL){
		printf("Calling getBack() on NULL List reference");
		exit(1);
	}
	if(L->length<=0){
		printf("Calling getBack() on empty List");
		exit(1);
	}

	return(L->back);
} 

// Without changing the List that N is on, returns the
// Node that is previous to Node N on its List. If
// there is no previous Node, returns NULL.
Node getPrevNode(Node N){
	if(N == NULL){
		printf("Calling getPrevNode() on NULL Node reference");
		exit(1);
	}
	if (N->previous == NULL)
		return(NULL);
	else
		return(N->previous);
}

// Without changing the List that N is on, returns the
// Node that is next after Node N on its List. If
// there is no next Node, returns NULL.
Node getNextNode(Node N){ 
	if(N == NULL){
		printf("Calling getNextNode() on NULL Node reference");
		exit(1);
	}

	if (N->next == NULL)
		return(NULL);
	else
		return(N->next);
}

// prepend()
// Inserts a new Node into List L before the front
// Node that has data as its value. If List is empty,
// makes that new Node the only Node on the list.
void prepend(List L, int data){
	if(L == NULL){
		printf("Calling prepend() on NULL List reference");
		exit(1);
	}

	Node N = newNode(data);

	if (L->length<=0){
		L->front=N;
		L->back=N;
		N->next=NULL;
		N->previous=NULL;
	}
	else{
	L->front->previous = N;
	N->next = L->front;
	L->front = N;
	L->front->previous=NULL;
}
	(L->length)++;
}

// append()
// Inserts a new Node into List L after the back
// Node that has data as its value. If List is empty,
// makes that new Node the only Node on the list.
void append(List L, int data){
	if(L == NULL){
		printf("Calling append() on NULL List reference");
		exit(1);
	}
	Node N = newNode(data);

	if (L->length<=0){
		L->front=N;
		L->back=N;
		N->next=NULL;
		N->previous=NULL;
	}
	else{
	L->back->next = N;
	N->previous=L->back;
	L->back= N;
	L->back->next = NULL;
}
	L->length++;

}

// insertBefore()
// Insert a new Node into Node N’s list before
// Node N that has data as its value.
// Precondition: Node N is not NULL
void insertBefore(List L, Node N, int data){
		if(L == NULL){
		printf("Calling insertBefore() on NULL List reference");
		exit(1);
		}
	if(N == NULL){
		printf("Calling insertBefore() on NULL Node reference");
		exit(1);
	}

	if(L->front == N){
		prepend(L, data);
	}

	else{
	Node K = newNode(data);
	K->next = N;
	K->previous = N->previous;
	N->previous->next= K;
	N->previous = K;
	L->length++;
}
}

// insertAfter()
// Insert a new Node into Node N’s list after
// Node N that has data as its value.
// Precondition: Node N is not NULL
void insertAfter(List L, Node N, int data){
		if(L == NULL){
		printf("Calling insertAfter() on NULL List reference");
		exit(1);
		}

	if(N == NULL){
		printf("Calling insertAfter() on NULL Node reference");
		exit(1);
	}
	if(L->back == N){
		append(L, data);
	}

	else{
	Node K = newNode(data);
	K->previous = N;
	K->next = N->next;
	N->next->previous= K;
	N->next = K;
	L->length++;
}
}

// deleteFront()
// Deletes the front Node in List L.
// Precondition: L has at least one Node on it.
void deleteFront(List L){
	if(L == NULL){
		printf("Calling deleteFront() on NULL List reference");
		exit(1);
	}

	if(L->length <=0){
		printf("Calling deleteFront() on empty list");
		exit(1);
	}
	Node N = L->front;
	if( L->length == 1){
		L->front = NULL;
		L->back = NULL;
	}
	else{
	L->front = L->front->next;
	L->front->previous = NULL;
}
	freeNode(&N);
	L->length--;

}

// deleteBack()
// Deletes the back Node in List L.
// Precondition: L has at least one Node on it.
void deleteBack(List L){
	if(L == NULL){
		printf("Calling deleteBack() on NULL List reference");
		exit(1);
	}
	if(L->length <=0){
		printf("Calling deleteBack() on empty list");
		exit(1);
	}
	Node N = L->back;
	if( L->length == 1){
		L->front = NULL;
		L->back = NULL;
	}
	else{
	L->back = L->back->previous;
	L->back->next = NULL;
}
	freeNode(&N);
	L->length--;

}

// Other operations

// printList()
// Prints the values in List L from front to back
// to the file pointed to by out, formatted as a
// space-separated string.
// For those familiar with Java, this is similar
// to toString()in Java.
void printList(FILE* out, List L){
	Node N= L->front;
	while (N != NULL){
	fprintf(out, "%d ", N->data);
	N=N->next;
	}
	fprintf(out, "\n");
}

// detachNode()
// Removes N from List L by making the Node before
// Node N link to the Node that’s after Node N as its
// next Node, and making the Node after Node N link to
// the Node that’s before Node N as its previous Node.
//
// After detachNode, Node N should have NULL as both its
// next and previous Nodes.
//
// Special cases:
//
// If Node N is the front the List L, then the Node after
// Node N becomes the front of List L, which should have
// a NULL previous Node.
//
// If Node N is the back of List L, then the Node before
// Node N becomes the back of List L, which should have
// a NULL next Node.
//
// Precondition: N is not NULL and N is a Node on List L.
void detachNode(List L, Node N){
	if(L == NULL){
		printf("Calling detachNode() on NULL List reference");
		exit(1);
	}
	if(N == NULL){
		printf("Calling detachNode() on NULL Node reference");
		exit(1);
	}
	
	int found = 0;
	Node M = L->front;
	while(M != NULL){
		if (M == N)
			found = 1;
		M=M->next;
	}
	if(found==0){
		printf("N is not on the List");
		exit(1);
	}

	if (L->front == N){
		L->front = N->next;
		L->front->previous = NULL;
	}

		else if ( L->back == N){
		L->back = N->previous;
		L->back->next = NULL;
	}

	else{
		N->previous->next = N->next;
		N->next->previous = N->previous;
	}

	N->next = NULL;
	N->previous = NULL;
}

//deleteNode()
// This operation is optional.
// Deletes Node N from List L.
// Removes N from List L by making the Node before
// Node N link to the Node that’s after Node N as its
// next Node, and making the Node after Node N link to
// the Node that’s before Node N as its previous Node.
//
// Special cases:
//
// If Node N is the front the List L, then the Node after
// Node N becomes the front of List L, which should have
// a NULL previous Node.
//
// If Node N is the back of List L, then the Node before
// Node N becomes the back of List L, which should have
// a NULL next Node.
//
// Precondition: N is not NULL and N is a Node on List L.
void deleteNode(List L, Node N){
	if(L == NULL){
		printf("Calling deleteNode() on NULL List reference");
		exit(1);
	}
	if(N == NULL){
		printf("Calling deleteNode() on NULL Node reference");
		exit(1);
	}

	int found = 0;
	Node M = L->front;
	while(M != NULL){
		if (M == N)
			found = 1;
		M=M->next;
	}
	if(found==0){
		printf("N is not on the List");
		exit(1);
	}

	if(L->front == N){
		L->front = N->next;
		L->front->previous=NULL;
	}

	else if(L->back == N){
		L->back = N->previous;
		L->back->next=NULL;
	}

	else{
		N->previous->next=N->next;
		N->next->previous=N->previous;
	}

	freeNode(&N);
			(L->length)--;
}

// attachNodeBetween()
// This operation is optional.
// Attaches Node N between Nodes N1 and N2. Makes N1's
// next Node be N, and N's previous Node be N1. Makes
// N2's previous Node be N, and N's next Node be N2.
//
// Special cases:
//
// If N1 is NULL and N2 is the front of List L, makes N
// the front of List L, which should have a NULL
// previous Node, and whose next Node should be N2.
//
// If N1 is the back of List L and N2 is NULL, makes N
// the back of List L, which should have a NULL next
// Node, and whose previous Node should be N1.
//
// Preconditions: N1 and N2 are adjacent nodes on List
// L, with N2 being N1's next node and N1's being N2's
// previous node. If N1 is NULL, then N2 is the front of
// list L. If N2 is NULL, then N1 is the back of List L.
void attachNodeBetween(List L, Node N, Node N1, Node N2){
	if(L == NULL){
		printf("Calling attachNodeBetween() on NULL List reference");
		exit(1);
	}
	if(N == NULL){
		printf("Calling attachNodeBetween() on NULL Node reference");
		exit(1);
	}

	if(N1 == NULL && L->front == N2){
		N->next = N2;
		N2->previous=N;
		L->front = N;
		N->previous=NULL;
	}

	else if(N2 == NULL && L->back == N1){
		N1->next=N;
		N->next = NULL;
		N->previous=N1;
		L->back = N;
	}
	else if(N1->next == N2 && N2->previous == N1){
		N->next = N2;
		N->previous = N1;
		N1->next = N;
		N2->previous = N;
	}

	else{
		printf("Nodes not adjacent");
		exit(1);
	}
}







