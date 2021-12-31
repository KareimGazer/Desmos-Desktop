#include "parse.h"


// check these values
Token token = {TokenType::NUMBER, ""};
double Xunknown = 0;

void match(enum TokenType expectedTokenType){
  // advances the token to the next char
  if(token.tType == expectedTokenType) token = getToken();
  else error();
}

void error(void){
  fprintf(stderr, "Error\n");
  exit(1);
}

TreeNode* equ(void){
  TreeNode *temp = new TreeNode();
  temp = Exp();
  while(token.tType == TokenType::PLUS || token.tType == TokenType::MINUS){
    TreeNode * newTemp = new TreeNode();
    newTemp->token_type = token.tType;
    if(token.tType == TokenType::PLUS) newTemp->value = '+';
    else newTemp->value = '-';

    match(token.tType);
    newTemp->left = temp;
    newTemp->right = Exp();
    temp = newTemp;
  }
  return temp;
}

TreeNode* Exp(void){
  TreeNode *temp = new TreeNode();
  temp = term();
  while(token.tType == TokenType::MULT || token.tType == TokenType::DIV){
    TreeNode * newTemp = new TreeNode();
    newTemp->token_type = token.tType;
    if(token.tType == TokenType::MULT) newTemp->value = '*';
    else newTemp->value = '/';

    match(token.tType);
    newTemp->left = temp;
    newTemp->right = term();
    temp = newTemp;
  }
  return temp;
}

TreeNode* term(void){
  TreeNode *temp = new TreeNode();

  temp = factor();
  while(token.tType == TokenType::POW){
    TreeNode * newTemp = new TreeNode();
    newTemp->token_type = token.tType;
    newTemp->value = '^';

    match(token.tType);
    newTemp->left = temp;
    newTemp->right = factor();
    temp = newTemp;
  }
  return temp;
}

TreeNode* factor(void){
  TreeNode *temp = new TreeNode();

  if(token.tType == TokenType::OPENBRACKET){
    match(TokenType::OPENBRACKET);
    temp = equ();
    match(TokenType::CLOSEDBRACKET);
  }
  else if(token.tType == TokenType::NUMBER){
    temp->value = stoi(token.tVal);
    temp->token_type = TokenType::NUMBER; // kind of exp
    token = getToken();
  }
  else if(token.tType == TokenType::IDENTIFIER){
    temp->value = 0;
    temp->token_type = TokenType::IDENTIFIER; // kind of exp
    token = getToken();
  }
  else error();
  return temp;
}

double calc(TreeNode * root){
  double left, right; left = right = 0.0;
  if(root->left != nullptr) {
    left = calc(root->left);
  }

  if(root->right != nullptr) right = calc(root->right);
  if(left == 0 && right == 0) {
    if(root->token_type == TokenType::NUMBER) return root->value;
    else return Xunknown;
  }
  else return operation(left, right, root->value);
}

double operation(double num1, double num2, char op){
  switch(op){
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num1 / num2;
    case '^': return pow(num1, num2);
    default: return 0;
  }
}
