#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node{

	struct Node* next;
	char* word;
};

//HELPER FUNCTION THAT PRINTS OUT AND FREES UP A LINKED LIST.
void printAndFreeLL(struct Node** frontPtr){

	if(*frontPtr == NULL){

		printf("\n");
		return;
	}

	struct Node* currNode = *frontPtr;
	struct Node* nextNode = NULL;

	while(currNode != NULL){

		nextNode = currNode -> next;
		printf("%s\n", currNode -> word);
		free(currNode -> word);
		free(currNode);
		currNode = nextNode;
	}

	return;
}

//HELPER FUNCTION THAT FINDS THE "GREATER" OF TWO NODES. RETURNS -1 IF THE FIRST
//NODE IS GREATER, 0 IF THEY ARE EQUAL, AND 1 IF THE SECOND NODE IS GREATER.
//"GREATER" IS DEFINED AS CONTAINING A WORD THAT IS TO APPEAR BEFORE ANOTHER IN
//THE OUTPUT, PER THE ASSIGNMENT SPECIFICATION.
int nodeCmp(struct Node** node1Ptr, struct Node** node2Ptr){

	struct Node* node1 = *node1Ptr;
	struct Node* node2 = *node2Ptr;
	int wordLen1 = -1;
	int wordLen2 = -1;

	if(node1 != NULL && node1 -> word != NULL){

		wordLen1 = strlen(node1 -> word);
	}

	if(node2 != NULL && node2 -> word != NULL){

		wordLen2 = strlen(node2 -> word);
	}

	int minLen = -1;

	if(wordLen1 > wordLen2){	minLen = wordLen2;}

	else{				minLen = wordLen1;}

	int testDex = 0;

	for(; testDex < minLen; testDex++){

		//NODE1 IS UPPERCASE, NODE 2 IS NOT.
		if(isupper(node1 -> word[testDex]) &&
			!isupper(node2 -> word[testDex])){

			return -1;
		}

		//NODE2 IS UPPERCASE, NODE 1 IS NOT.
		else if(!isupper(node1 -> word[testDex]) &&
			isupper(node2 -> word[testDex])){

			return 1;
		}

		//BOTH NODES ARE UPPERCASE OR BOTH NODES ARE LOWERCASE.
		else{

			if(node1 -> word[testDex] > node2 -> word[testDex]){

				return -1;
			}

			else if(node1 -> word[testDex] < node2 -> word[testDex]){

				return 1;
			}

			continue;
		}
	}

	if(minLen == wordLen1){	

		return 1;
	}

	if(minLen == wordLen2){		return -1;}

	return 0;
}

//HELPER FUNCTION FOR INSERTING A NEW WORD (ENCAPSULATED IN A NODE) INTO A
//LINKED LIST SUCH THAT IT REMAINS SORTED.
void insert(struct Node** frontPtr, char** newWordPtr){

	struct Node* front = *frontPtr;
	struct Node* newNode = malloc(sizeof(struct Node));

	if(newNode == NULL){	printf("Ran out of space.\n");}

	newNode -> next = NULL;
	newNode -> word = *newWordPtr;

	//INSERTS NEW-NODE INTO AN EMPTY LINKED LIST.
	if(front == NULL){

		front = newNode;
		*frontPtr = front;
		return;
	}

	//INSERTS NEW-NODE AT THE FRONT OF A LINKED LIST.
	else if(nodeCmp(&front, &newNode) >= 0){

		newNode -> next = front;
		front = newNode;
		*frontPtr = front;
		return;
	}

	//INSERTS NEW-NODE DIRECTLY AFTER THE FRONT-NODE (FOR WHEN THE
	//FRONT-NODE IS THE ONLY ONE IN THE LINKED LIST).
	else if(front -> next == NULL && 
		nodeCmp(&front, &newNode) <= 0){

		front -> next = newNode;
		*frontPtr = front;
		return;
	}

	//INSERTS NEW-NODE AT ITS CORRECT LOCATION IN A LINKED LIST
	//SUCH THAT THE LINKED LIST REMAINS SORTED.
	else{

		struct Node* addAfterNode = front;
		struct Node* addBeforeNode = front -> next;

		while(addBeforeNode != NULL &&
			nodeCmp(&addBeforeNode, &newNode) == -1){

			addBeforeNode = addBeforeNode -> next;
			addAfterNode = addAfterNode -> next;
		}

		addAfterNode -> next = newNode;
		newNode -> next = addBeforeNode;
		*frontPtr = front;
		return;
	}
}

int main(int argc, char** argv){

	if(argc != 2){

		printf("Must enter 1 argument.\n");
		return EXIT_FAILURE;
	}

	int inputLen = strlen(argv[1]);
	struct Node* front = malloc(sizeof(struct Node));

	if(front == NULL){    printf("Ran out of space.\n");}

	front = NULL;
	int currIndex = 0;
	int currBegex = 0;

	//BOOLEAN VARIABLE USED TO HANDLE SITUATIONS WHERE THE LAST CHARACTER OF
	//THE INPUT IS ALPHABETIC.
	int lastIsLetter = 0;

	for(; currIndex < inputLen; currIndex++){

		if(currIndex == inputLen - 1 && isalpha(argv[1][currIndex])){

			lastIsLetter = 1;
		}

		if(isalpha(argv[1][currIndex]) && !lastIsLetter){	continue;}

		else if(currBegex != currIndex || lastIsLetter){

			char* newWord = 
				malloc((currIndex - currBegex + lastIsLetter + 1) * 
				sizeof(char));

			if(newWord == NULL){    printf("Ran out of space.\n");}

			int tempDex = 0;

			for(; currBegex + tempDex < currIndex + lastIsLetter; tempDex++){

				newWord[tempDex] = argv[1][currBegex + tempDex];
			}

			newWord[tempDex + lastIsLetter] = '\0';
			insert(&front, &newWord);
			currBegex = currIndex + 1;
		}

		else{	currBegex++;}
	}

	printAndFreeLL(&front);
	return EXIT_SUCCESS;
}





