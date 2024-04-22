#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen 함수 사용을 위해 추가
#define MAX_STACK_SIZE 100
#define MAX_SIZE 100

typedef int element; // 스택에 저장될 요소의 타입을 int로 변경

typedef struct {
    element stack[MAX_STACK_SIZE]; // 요소를 저장할 배열
    int top; // 스택의 꼭대기를 가리키는 인덱스
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s) {
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s) {
    return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1); // 비정상 종료
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
        if (ch >= '0' && ch <= '9') { // 입력이 숫자인 경우
            value = ch - '0'; // char를 int로 변환
            push(&s, value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // 연산자인 경우
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
        // 공백과 개행 문자를 무시
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