#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



typedef enum {
    Num = 0,
    Plus = 1,
    Minus = 2,
    Multi = 3,
    Division = 4,
    Mod = 5,
    Power = 6,
    Sqrt = 7,
    Ln = 8,
    Log = 9,
    Sin = 10,
    Cos = 11,
    Tan = 12,
    Asin = 13,
    Acos = 14,
    Atan = 15,
    Lbracket = 16,
    Rbracket = 17,
    X = 18
} type_t;

/* priority 
    num     = 0
    +-      = 1
    * / mod = 2
    ^       = 3
    func    = 4
    ()      = 0
*/

typedef struct myStack {
  long double value;
  int priority;
  type_t type;
  struct myStack* next;
} stack;

/** @brief Creating stack.
 * 
 *  Create stack.
 *
 *  @return pointer on created stack.
 */
stack* create_stack();

/** @brief Adding element in stack
 * 
 *
 *  @param top pointer on stack.
 *  @param value value of number for adding(if add number).
 *  @param priority priority of adding element in calculations.
 *  @param type type of operation.
 *  @return true - SUCSESS, false - ERROR.
 */
bool push(stack **top, long double value, int priority, type_t type);

/** @brief Delete element from stack
 * 
 *
 *  @param top pointer on stack.
 */
void pop(stack **top);

/** @brief Help function for printing elements of stack.
 * 
 *
 *  @param top pointer on stack.
 */
void print_stack(stack* stack);

/** @brief Destroying stack.
 * 
 *
 *  @param top pointer on stack.
 */
void clear_stack(stack **top);

/** @brief Revesing of stack.
 * 
 *
 *  @param top pointer on stack.
 *  @return pointer on new reversed stack.
 */
stack* reverse_stack(stack** top);

#endif

