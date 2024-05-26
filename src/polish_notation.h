#ifndef _POLISH_NOTATION_
#define _POLISH_NOTATION_

#include "stack.h"
#include <math.h>
#include <string.h>

#define SUCSESS 0
#define ERROR 1
#define DEL '.'

/** @brief Calculate the result of input expression.
 *
 *
 *  @param result The result of calculation.
 *  @param input The string of expression.
 *  @return 0 - SUCSESS, 1 - ERROR.
 */
int calculate(long double* result, char* input, long double* x);

/** @brief Translates the expression in string to stack in infix notation.
 *
 *
 *  @param input The string of expression.
 *  @param infix The result of translation in stack.
 *  @return 0 - SUCSESS, 1 - ERROR.
 */
int string_to_infix(char* input, stack** infix);

/** @brief Add number to stack of infix expression.
 * 
 * Return false in case error of push to stack 
 * or wrong format of number(3.45.43 for example)
 *
 *
 *  @param string Current position of first digit of number in string.
 *  @param infix Stack for adding number.
 *  @return true - SUCSESS, false - ERROR.
 */
bool add_number(char** string, stack** infix);


/** @brief Сhecks if minus is unary.
 * 
 * Return false in case if minus is binary 
 * Return true in case if minus is unary
 *
 *
 *  @param string_pointer Current position of minus in string.
 *  @param infix Pointer of start of string.
 *  @return true - unary, false - binary.
 */
bool is_unary_minus(char** string_pointer, char* input);

/** @brief Convert infix notation to postfix.
 * 
 *  Convert infix notation to postfix
 *
 *  @param infix infix notation written in stack.
 *  @param postfix postfix notation written in stack.
 *  @return 0 - SUCSESS, 1 - ERROR.
 */
int infix_to_postfix(stack** infix, stack** postfix);

/** @brief Help function for printing stack.
 * 
 *  Prints stack
 *
 *  @param top top of stack.
 */
void print_notation(stack* top);

/** @brief Finction for calculating of expression in string format
 * 
 *  Calculat result of expression in postfix notation
 *
 *  @param result variable for result of calculation.
 *  @param variable value of variable in expression.
 *  @param top stack with expression in polish notation.
 *  @return 0 - SUCSESS, 1 - ERROR.
 */
int polish_calculate(long double* result, long double* variable, stack** top);

/** @brief Help function for calculating binary operations.
 * 
 *  Calculat result of binary operation setted by type.
 *
 *  @param type type of operation(1 - '+', 2 - '-', 3 - '*', 4 - '/', 5 - 'mod', 6 - 'pow', other - return NAN)
 *  @param value1 value of first operand.
 *  @param value2 value of fsecondirst operand.
 *  @return result of binary operation.
 */
long double binary_calculate(int type, long double value1, long double value2);

/** @brief Help function for calculating unary operations.
 * 
 *  Calculat result of unary operation setted by type.
 *
 *  @param type type of operation(7 - 'sqrt', 8 - 'ln', 9 - 'log', 10 - 'sin',
 *  11 - 'cos', 12 - 'tan', 13 - 'asin', 14 - 'acos', 15 - 'atan', other - return NAN)
 *  @param value1 value of first operand.
 *  @param value2 value of fsecondirst operand.
 *  @return result of binary operation.
 */
long double unary_calculate(int type, long double value);

/** @brief Help function for checking is binary operation could be calculated in PN, works as post validation.
 * 
 *  Helps validate expression.
 *
 *  @param top current position in stack with PN.
 *  @return 0 - SUCSESS, 1 - ERROR.
 */
int check_binary(stack* top);

/** @brief Help function for checking is unary operation could be calculated in PN, works as post validation.
 * 
 *  Helps validate expression.
 *
 *  @param top current position in stack with PN.
 *  @return 0 - SUCSESS, 1 - ERROR.
 */
int check_unary(stack* top);


#endif

