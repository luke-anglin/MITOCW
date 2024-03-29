// Luke Anglin
// lta9vw
// Date: 
// linkedList.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Class
#define PUSH_FRONT 	0
#define PUSH_BACK 	1
#define POP_FRONT 	2
#define POP_BACK 	3
#define PRINT_LIST 	4
#define HELP 		5
#define QUIT 		6
#define INVALID 	7

#define BUFFER_SIZE 20

void printOptions();
int readInput(int* val);
int isNumber(const char* token);
int isEmpty(const char* input);

	// Vars for linked list 
struct listNode * root;
struct listNode {
	int data; 
	struct listNode * next;
	struct listNode * prev; 
};

void insertAtHead(int n, struct listNode * prev) {
	if (prev == NULL) {
		// then create a new node
		struct listNode * new_node = malloc(sizeof(struct listNode));
		// set its data to n 
		new_node -> data = n;
		new_node -> next = NULL;
		new_node -> prev = NULL;
		root = new_node;
	}
	// If the next node is null
	else if (prev -> next == NULL) {
		// then create a new node
		struct listNode * new_node = malloc(sizeof(struct listNode));
		// set its data to n 
		new_node -> data = n;
		new_node -> next = NULL;
		new_node -> prev = prev;
		// set prev next to point to it 
		prev -> next = new_node;
	}
	else {
		// otherwise recurse by setting the previous to next node
		prev = prev -> next ;
		insertAtHead(n, prev);
	}
}
void insertAtTail(int n) {
	
	struct listNode * new_node = malloc(sizeof(struct listNode));
	new_node -> next = root;
	new_node -> data = n;
	new_node -> prev = NULL;
	if (root == NULL) {
		root = new_node;
	}
	else {
		new_node -> next = root;
		root -> prev = new_node;
		root = new_node;

	}

}


void removeHead(struct listNode * prev) {
	if (prev == NULL) {
		
	}
	else if (prev -> next == NULL && prev -> prev == NULL) root = NULL;
	// If the next node is null
	else if (prev -> next == NULL) {
		// set prev's next pointer to null
		if (prev -> prev)
			prev -> prev -> next = NULL;
		// Delete the node
		free(prev);

	}
	else {
		// otherwise recurse by setting the previous to next node
		prev = prev -> next ;
		removeHead(prev);
	}
}
void removeTail(struct listNode * prev) {
	if (prev != NULL && prev -> next == NULL) {
		root = NULL;
	}
	else if (prev != NULL && prev -> next != NULL) {
		root = prev -> next;
		free(prev -> prev );
	}
	else root = NULL; 
}


void printList(struct listNode * root) {
	if (root == NULL) {
		printf("\n");
	}
	else {
		printf("%d ", root -> data);
		// Set root to next
		struct listNode * next = root -> next;
		printList(next);
	}
}

void tearDown(struct listNode * root) {
	if (root != NULL) {
		while (root -> next != NULL){
			root = root->next ;
			free(root);
		}
	}
}

int main() {


	// TODO: INSTANTIATE YOUR LINKED LIST HERE.
	root = NULL;

	//----END----
	

	int option, val;
	printOptions();

	do {
		option = readInput(&val);
		//struct list_item* node;

		switch(option){
			case PUSH_FRONT:				// push onto front of list
				// TODO: Insert code to push val onto front of linked list here.
				insertAtHead(val, root);

				//----END----
			break;
			case PUSH_BACK: 				// push onto back of list
				// TODO: Insert code to push val onto back of linked list here.
				insertAtTail(val);

				//----END----
			break;
			case POP_FRONT: 				// remove from front of list
				// TODO: Insert code to remove from front of linked list here.
				// If list is empty, do nothing.
				removeHead(root);

				//----END----
			break;
			case POP_BACK:					// remove from back of list
				// TODO: Insert code to remove from back of linked list here.
				// If list is empty, do nothing.
				removeTail(root);

				//----END----
			break;
			case PRINT_LIST:				// print list
				// TODO: Insert code to print list forwards here.
				// Simply print each element separated by a space as shown below:
				// Elements: 1 2 3 4 5 
			printf("Elements: ");
			printList(root);


				//----END----
			break;
			case HELP: 						// print menu
			printOptions();
			break;
			case QUIT: 						// quit
			break;
			case INVALID: 					// bad input
			fprintf(stderr,"Invalid command or operand, please input a valid command or help to see the list again.\n");
			break;
		}

	} while(option != QUIT);

	// TODO: free any memory used by your linked list here
	
	tearDown(root);
	//----END----

	return 0;
}



//---------------------------------------
//NOTE: EVERYTHING BELOW THIS LINE SHOULD NOT BE TOUCHED. IT HANDLES INPUT AND SUCH FOR YOU
//---------------------------------------

int readInput(int* val){
	char input[BUFFER_SIZE]="";
	while(isEmpty(input)){
		printf("Enter command: ");
		fgets(input, BUFFER_SIZE, stdin);
		input[strcspn(input, "\n")] = 0;
	}

	char* token = strtok(input, " ");
	
	if ((strcmp(token, "af")) == 0){
		token = strtok(NULL, " ");
		if (isNumber(token)){
			*val = atoi(token);
			return PUSH_FRONT;
		} else return INVALID;
	} else if ((strcmp(token, "ab")) == 0){
		token = strtok(NULL, " ");
		if (isNumber(token)){
			*val = atoi(token);
			return PUSH_BACK;
		} else return INVALID;
	} else if ((strcmp(token, "rf")) == 0){
		return POP_FRONT;
	} else if ((strcmp(token, "rb")) == 0){
		return POP_BACK;
	} else if ((strcmp(token, "p")) == 0){
		return PRINT_LIST;
	} else if((strcmp(token, "help")) == 0){
		return HELP;
	} else if((strcmp(token, "-1")) == 0){
		return QUIT;
	} else {
		return INVALID;
	}
}

void printOptions(){
	printf("----------------------------------------------------\n");
	printf("This test harness operates with one linked list.\n");
	printf("Use any of the following options to manipulate it:\n");
	printf("\t* af <num> --- add integer to front\n");
	printf("\t* ab <num> --- add integer to back\n");
	printf("\t* rf       --- remove front element\n");
	printf("\t* rb       --- remove back element\n");
	printf("\t* p        --- print list forward\n");
	printf("\t* help     --- print off this list\n");
	printf("\t* -1       --- exit harness\n\n");
}

int isNumber(const char* token){
	int length, i = 0;
	if (token == NULL)	return 0;
	if(token[0] == '-') 	i = 1;
	length = strlen(token);
	for (; i < length; i++){
		if (!isdigit(token[i]))
			return 0;
	}

	return 1;
}

int isEmpty(const char* input){
	while (*input != '\0'){
		if (!isspace((unsigned char)*input))
			return 0;
		input++;
	}

	return 1;
}