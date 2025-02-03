#include <stdio.h>
#include <stdlib.h>

#define STACK_LIMIT 256
#define CHAR_LIMITER_SIZE 3

const char CLOSING_CHAR[CHAR_LIMITER_SIZE] = {')', ']', '}'};
const char OPENING_CHAR[CHAR_LIMITER_SIZE] = {'(', '[', '{'};

#define true 1
#define false 0
typedef int bool;

// function declarations:
// all related to stack operations and checking
// if char is a valid pair
void push(char *element, char stack_arr[], int *stack_size);
void pop(char stack_arr[], int *stack_size);
char peek(char stack_arr[], int *stack_size);
bool is_empty(int *stack_size);
bool is_full(int *stack_size);
void stack_overflow(void);
void stack_underflow(void);

bool is_closed_char(char *element, char stack_arr[], int *stack_size);
bool is_paired_char(char *element, char stack_arr[],  int *stack_size);

// function definitions
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
    char buffer;

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
    
    for (int i = 0; i < CHAR_LIMITER_SIZE; i++) {
        buffer = peek(stack_arr, size);
        if (buffer == OPENING_CHAR[i]) {
            return true;
        }
    }

    return false;
}


int main(void) {
    // stack size keeps track of the top of stack
    // initially setting to 0 and incrementing
    // by one every push and decrementing by
    // 1 every pop
    //
    // stack is filled with 0 initially
    char stack[STACK_LIMIT] = {0};
    char buffer;
    bool paired_flag = true;
    int stack_size = 0;

    printf("Enter parenthesees and/or braces: ");

    while ((buffer = getchar()) != '\n') {
        if (is_closed_char(&buffer, stack, &stack_size)) {
            if (is_empty(&stack_size)) {
                printf("stack is empty, first char is a closing char\n");
                paired_flag = false;
                break;
            }
            if (is_paired_char(&buffer, stack, &stack_size) == 0) {
                printf("char is not paired!\n");
                paired_flag = false;
                break;
            }
            pop(stack, &stack_size);
        } else {
            push(&buffer, stack, &stack_size);
        }
    }
    
    printf("\nFinished parsing: result:\nStack size: %d\n", stack_size);

    if (stack_size != 0 || paired_flag == 0) {
        printf("Parentheses/braces are NOT nested properly\n");
    } else {
        printf("Parentheses/braces are nested properly\n");
    }

    return 0;
}
