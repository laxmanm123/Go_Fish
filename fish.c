#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Grid {
    char data;
    int tileNum;
    struct Grid * up;
    struct Grid * down;
    struct Grid * left;
    struct Grid * right;
};

struct Node {
    int data;
    struct Node *next;
};

struct Player {
    struct Grid * curTile;
    int canMove;
    struct Node *score;
    int playerNum;
};
//grid setup functions
//struct Grid* setup(); 
struct Grid* makeBoard(); // creates the board, returns pointer to it
struct Grid* fillFish(struct Grid* head); // helper function, fills the board with the correct values

// hello there

//player functions
void playerMove(struct Player *p); // carries out player turn
int validMove(char *direction, int numMoves, struct Player* p); // helper function, checks if input move is valid, return 1 if true, 0 if false
int checkGameOver(struct Player *p); // checks game over for player, 1 if true, 0 if false
//ai functions
void aiMove(struct Player *p); // carries out ai turn

//linked list function
struct Node* insert(int data, struct Node* head); // adds new node with data to front of list
struct Node* newNode(int data); // returns new node with given data
void printList(struct Node* head); // prints linked list

//print functions
void printWelcome(); // prints welcome message
void printBoard(struct Grid* head); // prints game board
void printFinal(struct Player* p1, struct Player* p2); // calculates final score and prints winner 

int main() {
    struct Grid* head = makeBoard();
    struct Player *p1 = (struct Player*)malloc(sizeof(struct Player*));
    struct Player *ai = (struct Player*)malloc(sizeof(struct Player*));
    p1->curTile = head; 
    p1->playerNum = -1; 
    p1->canMove = 1; struct Node* pHead = (struct Node*)malloc(sizeof(struct Node*)); struct Node* aHead = (struct Node*)malloc(sizeof(struct Node*));
    p1->score = pHead; pHead->data = 1; pHead->next = NULL;  aHead->data = 1; aHead->next = NULL; 
    p1->curTile->data = -1;
    ai->curTile = head+35; 
    ai->playerNum = -2; 
    ai->canMove = 1; 
    ai->score = aHead;
    ai->curTile->data = -2;
    printWelcome();
    printBoard(head);
    int numPlayers = 2;
    while(p1->canMove == 1 || ai->canMove == 1) {
        if(p1->canMove == 1) {
            playerMove(p1);
        }
        if(ai->canMove == 1) {
            aiMove(ai);
        }
        printBoard(head);
        printf("----------------------------------\n");
    }
    printFinal(p1, ai);
    printf("Thanks for playing!!\n");
    return 0;    
}

void aiMove(struct Player *p) {
    if(checkGameOver(p) == 1) { // checks if ai has possible moves
        p->canMove = 0;
        printf("No more possible moves for AI!\n");
        return;
    }
    // 0 = UP, 1 = RIGHT, 2 = LEFT, 3 = DOWN
    int highestVal = 0;  // 4 = UPRIGHT, 5 = UPLEFT, 6 = DOWNRIGHT, 7 = DOWNLEFT
    int i;
    struct Grid *eye = p->curTile;
    struct Grid *target;
    int endReached = 0;
    for(i = 0; i < 7; i++) {
        while(endReached == 0) {
            switch(i) {
        case 0:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->up;
            break;
        case 1:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->right;
            break;
        case 2:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->left;
            break;
        case 3:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->down;
            break;
        case 4:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->up;
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->right;
            break;
        case 5:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->up;
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->left;
            break;
        case 6:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->down;
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->right;
            break;
        case 7:
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->down;
            if(eye == NULL) {
                endReached = 1;
                eye = p->curTile;
                break;
            }
            eye = eye->left;
            break;
    }
            
            if(eye == NULL || eye->data < 0) {
                endReached = 1;
            }
            else if(eye->data > highestVal) {
                    highestVal = eye->data;
                    target = eye;
            }
        }
        endReached = 0;
        eye = p->curTile;
    } // found highest Fish
    p->score = insert(p->curTile->data, p->score);
    p->curTile->data = -3; 
    p->curTile = target; 
    p->curTile->data = p->playerNum; 
    return;
}


int checkGameOver(struct Player *p) {
    struct Grid* cur = p->curTile;
    int numImpossibleMoves = 0;
    if(cur->down == NULL || cur->down->data < 0) {
        numImpossibleMoves++;
    }
    if(cur->up == NULL || cur->up->data < 0) {
        numImpossibleMoves++;
    }
    if(cur->left == NULL || cur->left->data < 0) {
        numImpossibleMoves++;
    }
    if(cur->right == NULL || cur->right->data < 0) {
        numImpossibleMoves++;
    }
    if(cur->down == NULL) {
        numImpossibleMoves++;
    }
    else {
        if(cur->down->right == NULL ||cur->down->right->data < 0) {
            numImpossibleMoves++;
        }
    }
    if(cur->down == NULL) {
        numImpossibleMoves++;
    }
    else {
        if (cur->down->left == NULL || cur->down->left->data < 0) {
        numImpossibleMoves++;
        }
    }
    if(cur->up == NULL) {
        numImpossibleMoves++;
    }
    else {
        if(cur->up->right == NULL || cur->up->right->data < 0) {
        numImpossibleMoves++;
        }
    }
    if(cur->up == NULL) {
        numImpossibleMoves++;
    }
    else { 
        if(cur->up->left == NULL || cur->up->left->data < 0) {
        numImpossibleMoves++;
        }
    }
    if(numImpossibleMoves == 8) {
        return 1;
    }
    else {
        return 0;
    }
}




void playerMove(struct Player* p) {
    if(checkGameOver(p) == 1) {
        p->canMove = 0;
        printf("No more possible moves for player!\n");
        return;
    }
    int done = 0; int numMoves;
    char *direction = (char*) malloc(20*sizeof(char));
    while(done == 0) {
            printf("Enter your move: ");
        scanf("%s %d", direction, &numMoves);
        if(numMoves > 5 || numMoves <= 0) {
            printf("Invalid move, please try again! ");
        }
        else if(validMove(direction, numMoves, p) == 1) {
            done = 1;
        }
        else {
            printf("Invalid move, please try again! ");
        }
    }
}

int validMove(char *direction, int numMoves, struct Player* p) {
        struct Grid* eye = p->curTile;
        int i;
        if(strcmp(direction, "UP") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->up;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"DOWN") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->down;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"LEFT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->left;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"RIGHT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->right;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"UPRIGHT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->up;
                eye = eye->right;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }    
        }
        else if(strcmp(direction,"DOWNRIGHT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->down;
                eye = eye->right;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"UPLEFT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->up;
                eye = eye->left;
                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"UPRIGHT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->up;
                eye = eye->right;

                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        else if(strcmp(direction,"DOWNLEFT") == 0) {
            for(i = 0; i < numMoves; i++) {
                eye = eye->down;
                eye = eye->left;

                if(eye == NULL || eye->data < 0) {
                    return -1;
                }
            }
        }
        p->curTile->data = -3;
        p->curTile = eye;
        p->score = insert(eye->data, p->score);
        p->curTile->data = p->playerNum;
        p->curTile->data = -1;
        return 1;
}






// node functions
struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node*));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Node* insert(int data, struct Node* head) {
    if(head->next==NULL) {
        head-> next = newNode(data);
        return head;
    }
    head->next = insert(data, head->next);    
    return head;
}

void printList(struct Node* head) {
    if(head->next == NULL) {
        printf("%d=", head->data);
        return;
    }
    printf("%d+", head->data);
    printList(head->next);
}
int sums(struct Node* head) {
    if(head->next == NULL) {
        return head->data;
    }

    return head->data + sums(head->next);
    
}







//board functions
// struct Grid* setup() {
//     struct Grid* head = makeBoard();
//     struct Player p1 = {head, 1, 1, 1, 0, 1};
//     p1.curTile->data = -1;
//     struct Player Ai = {head+35, 6, 6, 1, 0, 0};
//     Ai.curTile->data = -2;
//     struct Grid* temp = head;
//     printWelcome();
//     printBoard(head);
// }

struct Grid* makeBoard() {
    struct Grid* head = (struct Grid*)malloc(sizeof(struct Grid)*36);
    struct Grid* cur = head;
    int i; int y = 1; int x = 1; int tileNum = 1;
    for(i = 0; i < 36; i++) {
        cur->tileNum=tileNum;
        cur->data = 0;
        if((tileNum % 6) != 1 ) {
            cur->left = cur-1;
        }
        else {
            cur->left = NULL;
        }
        if((tileNum % 6) != 0) {
            cur->right = cur + 1;
        } 
        else {
            cur->right = NULL;
        }
        if((tileNum - 6) > 0) {
            cur->up = cur - 6;
        }
        else {
            cur->up = NULL;
        }
        if((tileNum + 6) <= 36) {
            cur->down = cur + 6;
        }
        else{
            cur->down = NULL;
        }
        tileNum++;
        cur++;
    }
    return fillFish(head);
}

struct Grid* fillFish(struct Grid* head) {
    //scuffed implementation
    struct Grid* temp = head;
    int i;
    temp->data = 1;
    for(i = 0; i < 5; i++) {
        temp = temp->right;
        temp->data = 1;
    }
    for(i = 0; i < 5; i++) {
        temp = temp->down;
        temp->data = 1;
    }
    for(i = 0; i < 5; i++) {
        temp = temp->left;
        temp->data = 1;
    }
    for(i = 0; i < 4; i++) {
        temp = temp->up;
        temp->data = 1;
    }
    for(i = 0; i < 4; i++) {
        temp = temp->right;
        temp->data = 2;
    }
    for(i = 0; i < 3; i++) {
        temp = temp->down;
        temp->data = 2;
    }
    for(i = 0; i < 3; i++) {
        temp = temp->left;
        temp->data = 2;
    }
    for(i = 0; i < 3; i++) {
        temp = temp->up;
        temp->data = 2;
    }
    temp = temp->right;
    for(i = 0; i < 2; i++) {
        temp = temp->down;
        temp->data = 3;
    }
    temp = temp->right;
    temp->data = 3;
    temp = temp->up;
    temp->data = 3;
    //fix this later
    //
    // int i; int index = 0; int curFish = 1; int tileNum = 0;
    // int direction = 1; // 1 = right, 2 = down, 3 = left, 4 = up
    // struct Grid* temp = head;
    // while(index < 10) {
    //     for(i = 0; i < 7; i++) {
    //         temp->data =  curFish;
           
    //         moveTile(direction, temp);
    //         tileNum++;
    //     }
        
    //     index++;
    //     if(direction == 4) {
    //         direction = 0;
    //     }
    //     else {
    //         direction++;
    //     }
    //     if(index == 4) {
    //         curFish = 2;
    //     }
    //     else if(index == 8) {
    //         curFish = 3;
    //     }
    // }
     return head;
}

void printBoard(struct Grid* head) {
    int i,j,temp;
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 6; j++) {
            temp=head->data;
            if(temp == -1){
                printf("P ");
            }
            else if(temp > 0) {
                printf("%d ", temp);
            }
            else if(temp == -2) {
                printf("A ");
            }
            else {
                printf("- ");
            }
            head++;
        }
        printf("\n");
    }
    return;
}

void printFinal(struct Player* p1, struct Player* p2) {
    int pScore = sums(p1->score);
    int aiScore = sums(p2->score);
    printf("The final player score is: ");
    printList(p1->score);
    printf("%d\n", pScore);
    printf("The final Ai score is: ");
    printList(p2->score);
    printf("%d\n", aiScore);
    if(pScore == aiScore) {
        printf("Its a tie!!\n");
    }
    else if(pScore < aiScore) {
        printf("You lose!");
    }
    else {
        printf("Congradulations! You win!!");
    }

}
 
void printWelcome() {
    printf("------------------------------------------------------\n");
    printf("Welcome to 'Hey, that's my fish!'\n");
    printf("The rules are simple, move from tile to tile, gathering fish as you go along.\n");
    printf("However, you cannot move through an empty space or another player. \n");
    printf("The possible directions are: UP, RIGHT, LEFT, DOWN, UPRIGHT, DOWNRIGHT, UPLEFT, and DOWNLEFT.\n");
    printf("Enter your moves in the format: DIRECTION NUM_SPACES\n");
    printf("Best of luck to you!!\n");
    printf("------------------------------------------------------\n");
    return;
}