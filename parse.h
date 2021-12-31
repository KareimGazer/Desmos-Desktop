#ifndef PARSE_H
#define PARSE_H
#include <math.h>
#include "scan.h"

extern Token token; // the global token variable (current next token)
extern double Xunknown;
extern bool errMsg;

/*
 input: void
 output: void
 displays error to console in case of error in parsing
*/
void error(void);

/*
 input: void
 output: void
 gets new token from the input if its valid
*/
void match(enum TokenType expectedTokenType);

/*
 input: void
 output: node representing expression containig + or - which are the lowest precedence
*/
TreeNode* equ(void);

/*
 input: void
 output: node representing expression containig * or / which are the second lowest precedence
*/
TreeNode* Exp(void);

/*
 input: void
 output: node representing expression containig ^ which is the highest precedence
*/
TreeNode* term(void);

/*
 input: void
 output: node representing a factor "expression between parentheses."
*/
TreeNode* factor(void);

/*
 input: node representing equation
 output: double representing the value of the equation substituting the global var Xunknown.
 calculates the equation according to the tree build by the parser using the equ function (see parse.cpp).
*/
double calc(TreeNode * node);

/*
 input: num1: first number (double).
        num2: second number (double).
        op: binary operation to be executed on the input numbers (char).
 output: operation result (double).
*/
double operation(double num1, double num2, char op);

#endif // PARSE_H
