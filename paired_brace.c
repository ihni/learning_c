#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_LIMIT 256
#define CHAR_LIMITER_SIZE 3

const char CLOSING_CHAR[CHAR_LIMITER_SIZE] = {')', ']', '}'};
const char OPENING_CHAR[CHAR_LIMITER_SIZE] = {'(', '[', '{'};

//
// function declarations:
//
void push(char *element, char stack_arr[], int *stack_size);
void pop(char stack_arr[], int *stack_size);
char peek(char stack_arr[], int *stack_size);
bool is_empty(int *stack_size);
bool is_full(int *stack_size);
void stack_overflow(void);
void stack_underflow(void);

bool is_closed_char(char *element, char stack_arr[], int *stack_size);
bool is_paired_char(char *element, char stack_arr[],  int *stack_size);

void parse_input(char stack[], bool *ptr_paired_flag, int *ptr_stack_size); 

//
// function definitions:
//
void push(char *element, char stack_arr[], int *stack_size) {
    if (is_full(stack_size)) {
        stack_overflow();
    }
    stack_arr[*stack_size] = *element;
    *stack_size += 1;
}

void pop(char stack_arr[], int *stack_size) {
    if (is_empty(stack_size)) {
        stack_underflow();
    }
    stack_arr[*stack_size] = 0;
    *stack_size -= 1;
}

char peek(char stack_arr[], int *stack_size) {
    return stack_arr[*stack_size - 1];
}

bool is_full(int *stack_size) {
    return (STACK_LIMIT < *stack_size);
}

bool is_empty(int *stack_size) {
    return (*stack_size == 0);
}

void stack_overflow(void) {
    printf("Stack overflow occurred\nTerminating program...\n");
    exit(0);
}
void stack_underflow(void) {
    printf("Stack underflow occured\nTerminating program...\n");
    exit(0);
}

bool is_closed_char(char *element, char stack_arr[], int *stack_size) {
    for (int i = 0; i < CHAR_LIMITER_SIZE; i++) {
        if (*element == CLOSING_CHAR[i]) {
            return true;
        }
    }
    return false;
}

bool is_paired_char(char *element, char stack_arr[], int *size) {
    int matching_idx = 0;

    for (int i = 0; i < CHAR_LIMITER_SIZE; i++) {
        if (*element == CLOSING_CHAR[i]) {
            break;
        }
        matching_idx++;
    }

    // if character is not a part of the opening char arr
    if (matching_idx >= CHAR_LIMITER_SIZE) {
        return false;
    }
    
    // match open character with closing character's index
    if (peek(stack_arr, size) == OPENING_CHAR[matching_idx]) {
        return true;
    } else {
        return false;
    }
}

void parse_input(char stack[], bool *ptr_paired_flag, int *ptr_stack_size) {
    char buffer;
    while ((buffer = getchar()) != '\n') {
        if (is_closed_char(&buffer, stack, ptr_stack_size)) {
            if (is_empty(ptr_stack_size)) {
                *ptr_paired_flag = false;
                break;
            }
            if (is_paired_char(&buffer, stack, ptr_stack_size) == 0) {
                *ptr_paired_flag = false;
                break;
            }
            pop(stack, ptr_stack_size);
        } else {
            push(&buffer, stack, ptr_stack_size);
        }
    }
}

int main(void) {
    // stack size keeps track of the top of stack
    // initially setting to 0 and incrementing
    // by one every push and decrementing by
    // 1 every pop
    //
    // stack is filled with 0 initially
    char stack[STACK_LIMIT] = {0};
    bool paired_flag = true;
    int stack_size = 0;

    printf("enter parenthesees and/or braces: ");
    parse_input(stack, &paired_flag, &stack_size);

    if (stack_size != 0 || paired_flag == 0) {
        printf("parentheses/braces are not nested properly\n");
    } else {
        printf("parentheses/braces are nested properly\n");
    }

    return 0;
}
