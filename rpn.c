#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//
// function declarations
//
void push(int [], int *size_ptr, int element);
int pop(int [], int *size_ptr);
int peek(int [], int *size_ptr);
bool isfull(int [], int *size_ptr);
bool isempty(int *size_ptr);
void stackoverflow(void);
void stackunderflow(void);

bool isoperand(char *element_ptr);

int add(int *x, int *y);
int sub(int *x, int *y);
int mul(int *x, int *y);
int divide(int *x, int *y);
int eql(int [], int *size_ptr);

//
// function definitions
//
void push(int stack[], int *size_ptr, int element) {
    if (isfull(stack, size_ptr)) {
        stackoverflow();
    }
    stack[*size_ptr] = element;
    *size_ptr += 1;
}

int pop(int stack[], int *size_ptr) {
    if (isempty(size_ptr)) {
        stackunderflow();
    }
    int popped_item = stack[*size_ptr];
    *size_ptr -= 1;
    return popped_item;
}

int peek(int stack[], int *size_ptr) {
    if (isempty(size_ptr)) {
        return -1;
    }
    return stack[*size_ptr];
}

bool isfull(int *stack_size_ptr, int *size_ptr) {
    // to differentiate
    // stack size is the size of the array
    // the size parameter handles how full the stack is
    return (bool) *size_ptr >= *stack_size_ptr;
}

bool isempty(int *size_ptr) {
    return (bool) *size_ptr == 0;
}

void stackoverflow(void) {
    printf("Expression is too complex, terminating program...\n");
    exit(0);
}

void stackunderflow (void) {
    printf("Not enough operands, terminating program...\n");
    exit(0);
}

bool isoperand(char *element_ptr) {
    if (*element_ptr >= '0' && *element_ptr <= '9') {
        return true;
    }
    return false;
}

int add(int *x, int *y) {
    return *x + *y;
}

int sub(int *x, int *y) {
    return *x - *y;
}

int mul(int *x, int *y) {
    return *x * *y;
}

int divide(int *x, int *y) {
    return *x / *y;
}

int eql(int stack[], int *size_ptr) {
    // equals operation causes the top stack item to be
    // displayed afterwards
    // the stack is then cleared and the user is prompted to
    // enter another expression
    int peeked_value = peek(stack, size_ptr);
    *size_ptr = 0;
    return peeked_value;
}

//
// main program
//
int main(void) {
    // stack size handles the memory given to the stack
    // size handles tracking how full the stack is
    const int stack_size = 256;
    int stack[stack_size] = {0};
    int size = 0;

    return 0;
}
