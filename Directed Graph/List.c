#include <stdlib.h>
#include "List.h"

List newList(void) {
    List l = (struct ListObj *) malloc(sizeof(struct ListObj));
    l->back = NULL;
    l->front = NULL;
    l->length = 0;
    return l;
}

Node newNode(int data) {
    Node node = (struct NodeObj *) malloc(sizeof(struct NodeObj));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void freeList(List *pL) {
    clear(*pL);
    free(*pL);
}

int length(List L) {
    return L->length;
}

int frontValue(List L) {
    return L->front->data;
}

int backValue(List L) {
    return L->back->data;
}

int getValue(Node N) {
    return N->data;
}

int equals(List A, List B) {
    Node b = B->front;
    Node a = A->front;
    for (; a != NULL && b != NULL; a = a->next, b = b->next) {
        if (a != b)
            break;
    }
    if (a != NULL || b != NULL)
        return 0;
    return 1;
}

void clear(List L) {
    if (L == NULL)
        return;
    if (L->front == NULL && L->back == NULL)
        return;
    while (getFront(L) != NULL) {
        deleteFront(L);
    }
}

Node getFront(List L) {
    return L->front;
}

Node getBack(List L) {
    return L->back;
}


void prepend(List L, int data) {
    if (L == NULL)
        return;
    insertBefore(L, getFront(L), data);
}

void append(List L, int data) {
    if (L == NULL)
        return;
    insertAfter(L, getBack(L), data);
}


void deleteFront(List L) {
    Node front = getFront(L);
    deleteNode(L, front);
}

void deleteBack(List L) {
    Node back = getBack(L);
    deleteNode(L, back);
}

void detachNode(List L, Node N) {
    if (N == NULL)
        return;
    Node n = NULL; 
    for (n = L->front; n != NULL; n = n->next) {
        if (n == N)
            break;
    }
    if (n == NULL)
        return;
    n = N->next;
    Node p = N->prev;
    if (n != NULL) {
        n->prev = p;
    }
    if (p != NULL) {
        p->next = n;
    }
    if (L->front == N) {
        L->front = n;
    }
    if (L->back == N) {
        L->back = p;
    }
    L->length -= 1;
}

void printList(FILE *out, List L) {
    for (Node n = L->front; n != NULL; n = n->next) {
        fprintf(out, "%d ", n->data);
    }
//    fprintf(out, "\n");
}

Node getPrevNode(Node N) {
    return N->prev;
}

Node getNextNode(Node N) {
    return N->next;
}

void insertBefore(List L, Node N, int data) {
    if (L == NULL)
        return;

    if (N == NULL && L->length != 0) {
        return;
    }
    Node node = newNode(data);
    if (N == NULL) {
        L->front = node;
        L->back = node;
        L->length = 0;
    } else {
        Node tmp = N->prev;
        N->prev = node;
        node->next = N;
        node->prev = tmp;
        if (L->front == N)
            L->front = node;
        if (tmp != NULL)
            tmp->next = node;
    }
    L->length += 1;
}

void insertAfter(List L, Node N, int data) {
    if (L == NULL)
        return;

    if (N == NULL && L->length != 0) {
        return;
    }
    Node node = newNode(data);
    if (N == NULL) {
        L->front = node;
        L->back = node;
        L->length = 0;
    } else {
        Node tmp = N->next;
        N->next = node;
        node->prev = N;
        node->next = tmp;
        if (L->back == N)
            L->back = node;
        if (tmp != NULL)
            tmp->prev = node;
    }
    L->length += 1;
}

void deleteNode(List L, Node N) {
    detachNode(L, N);
    free(N);
    //N = NULL;
}

void attachNodeBetween(List L, Node N, Node N1, Node N2) {
    if (L == NULL || N == NULL || (N1 == NULL && N2 == NULL))
        return;
    if (N1 != NULL && N1->next != N2)
        return;
    if (N2 != NULL && N2->prev != N1)
        return;
    if (N1 != NULL)
        N1->next = N;
    if (N2 != NULL)
        N2->prev = N;
    N->prev = N1;
    N->next = N2;
    L->length += 1;
}

