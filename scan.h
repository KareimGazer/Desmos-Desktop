#ifndef SCAN_H
#define SCAN_H
#include <string>

using namespace std;

// tokens to be recognized by the scanner
enum class TokenType{
    SEMICOLON, IF, THEN, ELSE, END, REPEAT, UNTIL, IDENTIFIER, ASSIGN, READ, WRITE, LESSTHAN, EQUAL, PLUS, MINUS, MULT, POW, DIV, OPENBRACKET, CLOSEDBRACKET, NUMBER, ERR, eof
};

typedef struct Token{
  enum TokenType tType;
  string tVal;
}Token;

// each node represents an opertation and two operands
class TreeNode{
public:
  TreeNode * left;
  TreeNode * right;
  enum TokenType token_type;
  unsigned char value;
  TreeNode(){
    left = nullptr; right = nullptr;
  }
};

// scanner global variables
extern string inputText; //string of the input equation
extern int inputTextIdx; // points to next char to be processed
extern int inputTextLimit; // last index of the input + 1 (the limit)
extern bool isError; // error indicator to terminate

/*
 input: void
 output: A token to be parsed by the parser
*/
Token getToken();
#endif // SCAN_H
