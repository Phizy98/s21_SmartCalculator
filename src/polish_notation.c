#include "polish_notation.h"

int calculate(long double* result, char* input, long double* x) {
  int correct = 0;
  stack* infix = NULL;
  stack* postfix = NULL;
  // create stacks for infix and postfix expressions
  infix = create_stack();
  postfix = create_stack();
  // translate input strint to infix stack
  correct += string_to_infix(input, &infix);
  if (correct == 0) {
    infix = reverse_stack(&infix);
    pop(&infix);  // delete first NUUL element
  }
  // printf("correct after string_to_infix: %d\n", correct);
  // infix = reverse_stack(&infix);
  // if(infix == NULL || correct != 0) return ERROR;
  // pop(&infix);    //delete first NUUL element
  // printf("Infix stack\n");
  // print_notation(infix);
  if (correct == 0) {
    infix_to_postfix(&infix, &postfix);
    postfix = reverse_stack(&postfix);
    pop(&postfix);
  }
  // printf("Postfix stack\n");
  // print_notation(postfix);

  if (correct == 0) correct += polish_calculate(result, x, &postfix);

  // printf("correct after valid: %d\n", correct);

  // printf("\nresult: %Lf\n", *result);
  clear_stack(&infix);
  clear_stack(&postfix);
  if (!correct)
    return SUCSESS;
  else
    return ERROR;

  // printf("================\n");
}

int string_to_infix(char* input, stack** infix) {
  bool correct = true;
  char* string_pointer = input;
  char current_char = ' ';
  while (*string_pointer != '\0') {
    current_char = *string_pointer;
    // printf("Current char: %c\n", current_char);
    if (current_char >= '0' && current_char <= '9') {
      correct &= add_number(&string_pointer, infix);
    } else if (current_char == 'x' || current_char == 'X') {
      correct &= push(infix, 0, 0, X);
    } else if (current_char == '+') {
      correct &= push(infix, 0, 1, Plus);
    } else if (current_char == '-') {
      if (is_unary_minus(&string_pointer, input)) {  // check unary '-'
        string_pointer++;
        correct &= add_number(&string_pointer, infix);
        (*infix)->value = -(*infix)->value;
      } else {
        correct &= push(infix, 0, 1, Minus);
      }
    } else if (current_char == '/') {
      correct &= push(infix, 0, 2, Division);
    } else if (current_char == '*') {
      correct &= push(infix, 0, 2, Multi);
    } else if (strncmp(string_pointer, "mod", 3) == 0) {
      correct &= push(infix, 0, 2, Mod);
      string_pointer += 2;
    } else if (current_char == '^') {
      correct &= push(infix, 0, 3, Power);
    } else if (current_char == '(') {
      correct &= push(infix, 0, 0, Lbracket);
    } else if (current_char == ')') {
      correct &= push(infix, 0, 0, Rbracket);
    } else if (strncmp(string_pointer, "cos(", 4) == 0) {
      correct &= push(infix, 0, 4, Cos);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 3;
    } else if (strncmp(string_pointer, "sin(", 4) == 0) {
      correct &= push(infix, 0, 4, Sin);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 3;
    } else if (strncmp(string_pointer, "tan(", 4) == 0) {
      correct &= push(infix, 0, 4, Tan);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 3;
    } else if (strncmp(string_pointer, "acos(", 5) == 0) {
      correct &= push(infix, 0, 4, Acos);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 4;
    } else if (strncmp(string_pointer, "asin(", 5) == 0) {
      correct &= push(infix, 0, 4, Asin);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 4;
    } else if (strncmp(string_pointer, "atan(", 5) == 0) {
      correct &= push(infix, 0, 4, Atan);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 4;
    } else if (strncmp(string_pointer, "sqrt(", 5) == 0) {
      correct &= push(infix, 0, 4, Sqrt);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 4;
    } else if (strncmp(string_pointer, "ln(", 3) == 0) {
      correct &= push(infix, 0, 4, Ln);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 2;
    } else if (strncmp(string_pointer, "log(", 4) == 0) {
      correct &= push(infix, 0, 4, Log);
      correct &= push(infix, 0, 0, Lbracket);
      string_pointer += 3;
    } else if (current_char == ' ') {
    } else {
      // printf("Char error\n");
      // printf("Char: '%d'\n", current_char);
      return ERROR;
    }
    string_pointer++;
    if (correct == false) {
      // printf("Other error\n");
      return ERROR;
    }
  }

  return SUCSESS;
}

bool add_number(char** string, stack** infix) {
  int count = 0;
  long double number = 0;
  sscanf(*string, "%Lf", &number);
  // printf("number before add: %Lf\n", number);
  if (push(infix, number, 0, Num) == false) return false;
  while ((**string >= '0' && **string <= '9') || **string == DEL) {
    if (**string == DEL) count++;
    if (count == 2) return false;
    (*string)++;
  }
  (*string)--;
  // printf("Add number last: %c\n", **string);

  return true;
}

bool is_unary_minus(char** string_pointer, char* input) {
  // char* maskOper = "+-*/d^(";
  // char* maskNum = "0123456789";
  char* current_char = *string_pointer;
  // if( current_char == input ||     //old
  //     ((strchr(maskOper, *(current_char - 1)) != NULL) && (strchr(maskNum,
  //     *(current_char - 1)) != NULL))) return true;
  // return false;
  if (current_char == input || *(current_char - 1) == '(') return true;
  return false;
}

int infix_to_postfix(stack** infix, stack** postfix) {
  stack* infix_top = *infix;
  stack* operators = create_stack();
  if (*infix == NULL || *postfix == NULL) return ERROR;
  while (infix_top->next != NULL) {
    if (infix_top->type == Num || infix_top->type == X) {  // Number
      // printf("добавить к выходной строке\n");
      push(postfix, infix_top->value, infix_top->priority, infix_top->type);
    } else if (infix_top->type == Lbracket) {  // Open bracket
      // printf("поместить в стек\n");
      push(&operators, infix_top->value, infix_top->priority, infix_top->type);
    } else if (infix_top->type == Rbracket) {  // Close bracket
      // printf("1) присоединить содержимое стека до скобки в обратном порядке к
      // выходной строке; 2) удалить скобку из стека.\n");
      while ((operators->next != NULL) && (operators->type != Lbracket)) {
        push(postfix, operators->value, operators->priority, operators->type);
        pop(&operators);
      }
      if (operators->next != NULL) {
        pop(&operators);
      }
    } else if ((infix_top->type > 0) && (infix_top->type < 16)) {
      // print_notation(operators);
      // if(operators->next != NULL && operators->priority >=
      // infix_top->priority) printf("1) присоединить стек в обратном порядке к
      // выходной строке; 2) поместить новую операцию в стек.\n");
      // else
      // printf("поместить в стек\n");
      while (operators->next != NULL &&
             operators->priority >= infix_top->priority) {
        push(postfix, operators->value, operators->priority, operators->type);
        pop(&operators);
      }
      push(&operators, infix_top->value, infix_top->priority, infix_top->type);
    }
    infix_top = infix_top->next;
  }
  while (operators->next != NULL) {
    push(postfix, operators->value, operators->priority, operators->type);
    pop(&operators);
  }

  clear_stack(&operators);
  return SUCSESS;
}

// void print_notation(stack* top) {
//     if(top == NULL) {
//         printf("Empty stack\n");
//     }
//     while (top->next != NULL) {
//         if(top->type == X) printf("x ");
//         if(top->type == Num) printf("%.3Lf ", top->value);
//         if(top->type == Plus) printf("+ ");
//         if(top->type == Minus) printf("- ");
//         if(top->type == Multi) printf("* ");
//         if(top->type == Division) printf("/ ");
//         if(top->type == Mod) printf("mod ");
//         if(top->type == Power) printf("^ ");
//         if(top->type == Sqrt) printf("sqrt ");
//         if(top->type == Ln) printf("ln ");
//         if(top->type == Log) printf("log ");
//         if(top->type == Sin) printf("sin ");
//         if(top->type == Cos) printf("cos ");
//         if(top->type == Tan) printf("tan ");
//         if(top->type == Asin) printf("asin ");
//         if(top->type == Acos) printf("acos ");
//         if(top->type == Atan) printf("atan ");
//         if(top->type == Lbracket) printf("( ");
//         if(top->type == Rbracket) printf(") ");
//         top = top->next;
//     }
//     printf("\n");
// }

int polish_calculate(long double* result, long double* variable, stack** top) {
  stack* postfix = *top;
  long double value = 0;
  stack* help = create_stack();
  int correct = SUCSESS;

  while (postfix->next != NULL) {
    if (postfix->type == Num) {
      push(&help, postfix->value, postfix->priority, postfix->type);
    } else if (postfix->type == X) {
      push(&help, *variable, postfix->priority, Num);
    } else if (postfix->type > 0 && postfix->type < 7) {
      if (check_binary(help) != SUCSESS) {
        clear_stack(&help);
        return ERROR;
      }
      value =
          binary_calculate(postfix->type, help->next->value,
                           help->value);  // check is real help.next and help
      pop(&help);
      pop(&help);
      push(&help, value, 0, 0);
    } else if (postfix->type > 6 && postfix->type < 16) {
      if (check_unary(help) != SUCSESS) {
        clear_stack(&help);
        return ERROR;
      }
      value = unary_calculate(postfix->type, help->value);  // check help
      pop(&help);
      push(&help, value, 0, 0);
    }
    postfix = postfix->next;
  }
  if (help->next->next != NULL) correct = ERROR;
  *result = help->value;
  clear_stack(&help);

  return correct;
}

int check_binary(stack* top) {
  if (top->next == NULL || top->next->next == NULL) return ERROR;
  if (top->type != Num || top->next->type != Num) return ERROR;
  return SUCSESS;
}
int check_unary(stack* top) {
  if (top->next == NULL || top->type != Num) return ERROR;
  return SUCSESS;
}

long double binary_calculate(int type, long double value1, long double value2) {
  long double result = 0;
  if (type == 1) {
    result = value1 + value2;
  } else if (type == 2) {
    result = value1 - value2;
  } else if (type == 3) {
    result = value1 * value2;
  } else if (type == 4) {
    result = value1 / value2;
  } else if (type == 5) {
    result = fmodl(value1, value2);
  } else if (type == 6) {
    result = powl(value1, value2);
  } else
    return NAN;

  return result;
}

long double unary_calculate(int type, long double value) {
  long double result = 0;
  if (type == 7) {
    result = sqrtl(value);
  } else if (type == 8) {
    result = logl(value);
  } else if (type == 9) {
    result = log10l(value);
  } else if (type == 10) {
    result = sinl(value);
  } else if (type == 11) {
    result = cosl(value);
  } else if (type == 12) {
    result = tanl(value);
  } else if (type == 13) {
    result = asinl(value);
  } else if (type == 14) {
    result = acosl(value);
  } else if (type == 15) {
    result = atanl(value);
  } else
    return NAN;

  return result;
}

// int main() {
//    printf("Start\n");
//    long double res = 0;
//    long double x = 0;
//    calculate(&res, "tan(0)*(cos(0)/sin(0))", &x);    //=1493,    23 65 * 12 6
//    / - 6 6 0 cos * - sin + printf("res: %LF\n", res); printf("END!\n");
//     // long double a = INFINITY/NAN;
//     // printf("%LF", a);

//    return 0;
// }
