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
	return h->data[h->top--];
}
Stack* toAdd(char loc, Stack* h1, Stack* h2, Stack* h3)
{
    if(loc == 'A' || loc == 'a') return h1;
    if(loc == 'B' || loc == 'b') return h2;
    if(loc == 'C' || loc == 'c') return h3;
}
void move(char from, char to, Stack* h1, Stack* h2, Stack* h3)
{
    Stack* fromh;
    Stack* toh;
    element temp;
    fromh = toAdd(from, h1, h2, h3);
    toh = toAdd(to, h1, h2, h3);
    temp = pop(fromh);
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
int correct(Stack* h, int i)
{
    return h->data[h->top-i+1]+1 == h->data[h->top-i];
}
int complete(Stack* h, int num)
{
    for(int i=num-1; i>0; i--) {
        if(!correct(h, i)) {
            return 0;
        }
    }
    return 1;
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
	scanf("%d", &num);
	if(num < 3 || num > 10) {
        printf("입력범위를 벗어났습니다.");
        return 0;
	}
	for(int i=num; i>0; i--) push(&h1, i);
	printHanoi(&h1, &h2, &h3);
	while(1) {
        printf("데이터 입력 : ");
        scanf(" %c %c", &from, &to);
        if(wrong(from) || wrong(to)) {
            printf("입력값이 잘못되었습니다.\n\n");
            continue;
        }
        move(from, to, &h1, &h2, &h3);
        count++;
        printHanoi(&h1, &h2, &h3);
		if(complete(&h3, num)) break;
	}
    printf("하노이탑 옮기기에 성공하였습니다!\n");
	printf("총 %d번 이동하였습니다.\n", count);
	return 0;
}
