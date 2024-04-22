#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen �Լ� ����� ���� �߰�
#define MAX_STACK_SIZE 100
#define MAX_SIZE 100

typedef int element; // ���ÿ� ����� ����� Ÿ���� int�� ����

typedef struct {
    element stack[MAX_STACK_SIZE]; // ��Ҹ� ������ �迭
    int top; // ������ ����⸦ ����Ű�� �ε���
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
    s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s) {
    return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// ���� �Լ�
void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1); // ������ ����
    }
    else return s->stack[(s->top)--];
}

int eval(char exp[]) {
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        printf("expression : %c\n", exp[i]);
        if (ch >= '0' && ch <= '9') { // �Է��� ������ ���
            value = ch - '0'; // char�� int�� ��ȯ
            push(&s, value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // �������� ���
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
        // ����� ���� ���ڸ� ����
        else if (ch == ' ' || ch == '\n') {
            continue;
        }
    }
    return pop(&s);
}

int main(void) {
    char expression[MAX_SIZE];
    int result;
    printf("postfix Expression: ");
    fgets(expression, sizeof(expression), stdin);
    result = eval(expression);
    printf("Result %d\n", result);
    return 0;
}