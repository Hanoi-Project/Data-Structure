#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 10
typedef int element;
typedef struct{
	element data[STACK_SIZE];
	int top;
} Stack;

void initStack(Stack *h){h->top = -1;}
int isFull(Stack *h){return h->top == STACK_SIZE - 1;}
int isEmpty(Stack *h){return h->top == -1;}
void push(Stack *h, element data)
{
	if(isFull(h)) {
		printf("stack is full\n");
		return;
	}
	h->data[++h->top] = data;
}
element pop(Stack *h)
{
	if(isEmpty(h)) {
		printf("stack is empty\n");
		return 0;
	}
	return h->data[h->top--];
}
Stack* toAdd(char loc, Stack* h1, Stack* h2, Stack* h3)
{
    if(loc == 'A') return h1;
    if(loc == 'B') return h2;
    if(loc == 'C') return h3;
}
void move(char from, char to, Stack* h1, Stack* h2, Stack* h3)
{
    Stack* fromh;
    Stack* toh;
    element temp;
    fromh = toAdd(from, h1, h2, h3);
    toh = toAdd(to, h1, h2, h3);
    temp = pop(fromh);
    printf("%d\n", temp);
    push(toh, temp);
}
void printHanoi(Stack* h1, Stack* h2, Stack* h3)
{
    int i;
    printf("|");
    for(i=0; i<=h1->top; i++) printf(" %d |", h1->data[i]);
    printf("\n|");
    for(i=0; i<=h2->top; i++) printf(" %d | ", h2->data[i]);
    printf("\n|");
    for(i=0; i<=h3->top; i++) printf(" %d | ", h3->data[i]);
    printf("\n");
}

int main()
{
	int menu=1;
	char from, to;
	Stack h1, h2, h3;
	initStack(&h1);initStack(&h2);initStack(&h3);
	push(&h1, 3);push(&h1, 2);push(&h1, 1);
	printHanoi(&h1, &h2, &h3);
	while(menu) {
		printf("1:move, 0:stop : ");
		scanf("%d", &menu);
		switch(menu) {
			case 1 :
				printf("데이터 입력 : ");
				scanf(" %c %c", &from, &to);
				move(from, to, &h1, &h2, &h3);
				printHanoi(&h1, &h2, &h3);
				break;
			case 0 :
				break;
			default :
				printf("잘못된 입력 입니다. \n");
				break;
		}
	}
	return 0;
}
