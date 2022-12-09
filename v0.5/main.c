#include <stdio.h>
#include <Windows.h>
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
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("\t\t옮길 수 없습니다.\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        pop(toh);
        push(fromh, temp);
    }
}
void printHanoi(Stack* h1, Stack* h2, Stack* h3, int h)
{
    int i, j, k;
    for(i=0; i<=STACK_SIZE-h; i++) printf("\n");
    for(i=h-1; i>=0; i--) {
        printf("\t\t");
        for(j=0; j<h-h1->data[i]; j++) printf(" ");
        for(k=0; k<h1->data[i]*2-1; k++) printf("*");
        for(j=1; j<h-h1->data[i]; j++) printf(" ");
        if(k && i!=0) printf(" ");
        printf("\t");
        for(j=0; j<h-h2->data[i]; j++) printf(" ");
        for(k=0; k<h2->data[i]*2-1; k++) printf("*");
        for(j=1; j<h-h2->data[i]; j++) printf(" ");
        if(k && i!=0) printf(" ");
        printf("\t");
        for(j=0; j<h-h3->data[i]; j++) printf(" ");
        for(k=0; k<h3->data[i]*2-1; k++) printf("*");
        for(j=1; j<h-h3->data[i]; j++) printf(" ");
        if(k && i!=0) printf(" ");
        printf("\n");
    }
    printf("\t\t");
    for(int j=1; j<h; j++) printf(" ");
    printf("A");
    for(int j=1; j<h; j++) printf(" ");
    printf("\t");
    for(int j=1; j<h; j++) printf(" ");
    printf("B");
    for(int j=1; j<h; j++) printf(" ");
    printf("\t");
    for(int j=1; j<h; j++) printf(" ");
    printf("C");
    printf("\n\n\t\t");
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
    while(1) {
        printf("\n\n\t하노이탑의 크기를 지정해주세요.(입력 범위 3~10) : ");
        scanf("%d", &num);
        if(num < 3 || num > 10) {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            printf("\t\t입력범위를 벗어났습니다.");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            continue;
        }
        break;
	}
	for(int i=num; i>0; i--) push(&h1, i);
    system("cls");
	printHanoi(&h1, &h2, &h3, num);
	while(1) {
        printf("데이터 입력(보내는 위치/받는 위치) : ");
        scanf(" %c %c", &from, &to);
        system("cls");
        if(wrong(from) || wrong(to)) {
            printf("\n\n\t입력값이 잘못되었습니다.\n\n");
            printHanoi(&h1, &h2, &h3, num);
            continue;
        }
        move(from, to, &h1, &h2, &h3);
        count++;
        printHanoi(&h1, &h2, &h3, num);
		if(complete(&h3, num)) break;
		Sleep(500);
	}
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("\n\n\t하노이탑 옮기기에 성공하였습니다!\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\t총 %d번 이동하였습니다.\n\n\n", count);
	return 0;
}
