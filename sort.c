// Ariana Jansma
// CPSC 246
// 09/09/2022
// This progam implemente MergeSort and its helper function merge. 
// MergeSort was implemented recursively while merge is iterative.
// The goal of the project was to get comfortable working with C.

#include <stdio.h>
#include <stdlib.h>

// struct representing a linked list 
struct node{
    int data;
    struct node * next;
} ;

// merge function assists the mergeSort function by sorting two
// linked lists
struct node * merge(struct node * head1, struct node * head2){
    // check if one of the heads is null
    if(head1 == NULL){
        return head2;
    }
    else if(head2 == NULL){
        return head1;
    }

    // Create Nodes Needed for Function
    struct node * newhead;
    newhead = (struct node*)malloc(sizeof(struct node));

    struct node * currNode;
    currNode = (struct node*)malloc(sizeof(struct node));

    struct node * nextNode;
    nextNode = (struct node*)malloc(sizeof(struct node));

    // check which number is next is sorted list
    if(head1->data >= head2->data){
        // new head points to head2
        newhead = head2;
        // advance list
        head2 = head2->next;
    }

    else{
        // new head points to head1
        newhead = head1;
        // advance list
        head1 = head1->next;
    }

    currNode = newhead;

    //merge lists
    while(head1 != NULL && head2 != NULL){
        if(head1->data <= head2->data){
            // add node to list
            nextNode = head1;
            // advance list
            head1 = head1->next;
        }
        else{
            // add node to list
            nextNode = head2;
            // advance list
            head2 = head2->next;
        }

        //assign next node
        currNode->next = nextNode;
        //move forward
        currNode = nextNode;
    }

    // merge last item in list depending on which head still has data
    if(head1 != NULL){
        currNode->next = head1;
    }
    else if(head2 != NULL){
        currNode ->next = head2;
    }

    return newhead;

} 

// This function returns the size of the linked list
int findSize(struct node * head){
    int size = 0;
    // count up number of nodes
    while(head != NULL){
        size++;
        head = head->next;
    }
    return size;
} 

// this function cuts the current list in half
struct node * cutList(struct node * currHead, int size){
    // create second list head
    struct node * head2;
    head2 = (struct node*)malloc(sizeof(struct node));

    // flip to middle of list
    for(int i = 1; i < size/2; i++){
        currHead = currHead->next;
    }

    // head 2 points to second half of list
    head2 = currHead->next;

    // end of first list points to null
    currHead->next = NULL;

    return head2;
}

// this function implements the mergeSort method
struct node * mergeSort(struct node* head, int size){
    //create second head for list 2
    struct node * head2;
    head2 = (struct node*)malloc(sizeof(struct node));

    //check if size of current array is greater than 0 or 1
    if(findSize(head) <= 1){
        // if not bigger then return head
        return head;
    }

    // 2.1 cut current array in half
    head2 = cutList(head, size);

    // 2.2 Recursively call Merge Sort and 2.3 call merge
    head = merge(mergeSort(head, findSize(head)), mergeSort(head2, findSize(head2)));

    return head;

}

//this function prints the current linked list
void printList(struct node * head){
    // print each node in the list
    while(head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    //new line
    printf("\n");
}

// this function creates a new node and adds it to the list
void addNode(struct node * head, int data){
    // create new node
    struct node * newNode;
    newNode = (struct node*)malloc(sizeof(struct node));

    // traverse to end of list
    while(head->next != NULL){
        head = head->next;
    }

    // add new node
    newNode->data = data;
    newNode->next = NULL;
    head->next = newNode;
}

// main program featuring test code  
int main() {  
    // test merge function
    
    // create test head 1
    struct node * test1 = NULL;
    test1 = (struct node*)malloc(sizeof(struct node));
    test1->data = 1;

    // add nodes
    addNode(test1, 5);
    addNode(test1, 8);

    // create test head 2
    struct node * test2 = NULL;
    test2 = (struct node*)malloc(sizeof(struct node));
    test2->data = 2;

    // add nodes
    addNode(test2, 6);
    addNode(test2, 7);
    
    // print nodes
    printf("Lists before merge funtion: \n");
    printList(test1);
    printList(test2);

    // call merge
    test1 = merge(test1, test2);
    
    printf("List after merge function: \n");
    printList(test1);

    // test the mergesort function:
    // create head and allocate memory
    struct node * head1 = NULL;
    head1 = (struct node*)malloc(sizeof(struct node));
    head1->data = 1;

    // add nodes to list
    addNode(head1, 5);
    addNode(head1, 19);
    addNode(head1, 2);
    addNode(head1, 90);
    addNode(head1, 13);
    addNode(head1, 7);

    // print original list
    printf("Unsorted list: \t");
    printList(head1);

    // merge sort
    head1 = mergeSort(head1, findSize(head1));

    // print sorted list
    printf("Sorted List: \t");
    printList(head1);

    return 0;
}