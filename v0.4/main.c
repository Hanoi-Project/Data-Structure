#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 10
typedef int element;
typedef struct{
	element data[STACK_SIZE];
	int top;
} Stack;

void initStack(Stack *h)
{
    h->top = -1;
    for(int i=0; i<STACK_SIZE; i++) h->data[i] = 0;
}
int isFull(Stack *h){return h->top == STACK_SIZE - 1;}
int isEmpty(Stack *h){return h->top == -1;}
void push(Stack *h, element data)
{
	if(isFull(h)) {
		printf("HanoiTower is full\n");
		return;
	}
	h->data[++h->top] = data;
}
element pop(Stack *h)
{
	if(isEmpty(h)) {
		printf("HanoiTower is empty\n");
		return 0;
	}
	int temp = h->data[h->top];
	h->data[h->top--] = 0;
	return temp;
}
Stack* toAdd(char loc, Stack* h1, Stack* h2, Stack* h3)
{
    if(loc == 'A' || loc == 'a') return h1;
    if(loc == 'B' || loc == 'b') return h2;
    if(loc == 'C' || loc == 'c') return h3;
}
int correct(Stack* h, int i)
{
    if(h->top < i-1) return 0;
    else if(h->top == 0) return 1;
    return h->data[h->top-i+1] < h->data[h->top-i];
}
int complete(Stack* h, int num)
{
    for(int i=num; i>0; i--) {
        if(!correct(h, i)) {
            return 0;
        }
    }
    return 1;
}
void move(char from, char to, Stack* h1, Stack* h2, Stack* h3)
{
    Stack* fromh;
    Stack* toh;
    element temp;
    fromh = toAdd(from, h1, h2, h3);
    toh = toAdd(to, h1, h2, h3);
    if(fromh->top == -1) return;
    temp = pop(fromh);
    push(toh, temp);
    if(!correct(toh, 1)) {
        printf("옮길 수 없습니다.\n");
        pop(toh);
        push(fromh, temp);
    }
}
void printHanoi(Stack* h1, Stack* h2, Stack* h3, int h)
{
    for(int i=h-1; i>=0; i--) {
        for(int j=0; j<h-h1->data[i]; j++) printf(" ");
        for(int j=0; j<h1->data[i]*2-1; j++) printf("*");
        for(int j=1; j<h-h1->data[i]; j++) printf(" ");
        for(int j=0; j<i; j++) printf(" ");
        printf("\t");
        for(int j=0; j<h-h2->data[i]; j++) printf(" ");
        for(int j=0; j<h2->data[i]*2-1; j++) printf("*");
        for(int j=1; j<h-h2->data[i]; j++) printf(" ");
        printf("\t");
        for(int j=0; j<h-h3->data[i]; j++) printf(" ");
        for(int j=0; j<h3->data[i]*2-1; j++) printf("*");
        for(int j=1; j<h-h3->data[i]; j++) printf(" ");
        printf("\n");
    }
}
int wrong(char data)
{
    return data!='a' && data!='b' && data!='c' && data!='A' && data!='B' && data!='C';
}

int main()
{
	int menu=1, count=0, num;
	char from, to;
	Stack h1, h2, h3;
	initStack(&h1);initStack(&h2);initStack(&h3);
	printf("하노이탑의 크기를 지정해주세요.(입력 범위 3~10) : ");
	while(1) {
        scanf("%d", &num);
        if(num < 3 || num > 10) {
            printf("입력범위를 벗어났습니다.");
            continue;
        }
        break;
	}
	for(int i=num; i>0; i--) push(&h1, i);
	printHanoi(&h1, &h2, &h3, num);
	while(1) {
        printf("데이터 입력 : ");
        scanf(" %c %c", &from, &to);
        if(wrong(from) || wrong(to)) {
            printf("입력값이 잘못되었습니다.\n\n");
            continue;
        }
        move(from, to, &h1, &h2, &h3);
        count++;
        printHanoi(&h1, &h2, &h3, num);
		if(complete(&h3, num)) break;
	}
    printf("하노이탑 옮기기에 성공하였습니다!\n");
	printf("총 %d번 이동하였습니다.\n", count);
	return 0;
}
