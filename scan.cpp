#include <map>
#include "scan.h"

// states of the scanner while scanning the input
typedef enum { START, INCOMMENT, INNUM, INID, INASSIGN, DONE, ERROR}state;

// maps for transormations
map<char, char> symbols = {{'+', '+'}, {'-', '-'}, {'*', '*'}, {'^', '^'}, {'/', '/'}, {'=', '='}, {'(', '('}, {')', ')'}};

map<string, string> reservedWords = { {"if", "if"}, {"then", "then"}, {"else", "else"}, {"end", "end"}, {"repeat", "repeat"}, {"until", "until"}, {"read", "read"}, {"write", "write"},
};

map<char, TokenType> specialTypes = {{'+', TokenType::PLUS}, {'-', TokenType::MINUS}, {'*', TokenType::MULT}, {'^', TokenType::POW}, {'/', TokenType::DIV}, {'=', TokenType::ASSIGN}, {'<', TokenType::LESSTHAN}, {'(', TokenType::OPENBRACKET}, {')', TokenType::CLOSEDBRACKET}, {';', TokenType::SEMICOLON},
};

map<string, TokenType> reservedTypes = { {"if", TokenType::IF}, {"then", TokenType::THEN}, {"else", TokenType::ELSE}, {"end", TokenType::END}, {"repeat", TokenType::REPEAT}, {"until", TokenType::UNTIL}, {"read", TokenType::READ}, {"write", TokenType::WRITE}};

// not nessesary used only for visualization
map<TokenType, char> spMap = {{TokenType::PLUS, '+'}, {TokenType::MINUS, '-'}, {TokenType::MULT, '*'}, {TokenType::POW, '^'}, {TokenType::DIV, '/'}, {TokenType::ASSIGN, '='}, {TokenType::LESSTHAN, '<'}, {TokenType::OPENBRACKET, '('}, {TokenType::CLOSEDBRACKET, ')'}, {TokenType::SEMICOLON, ';'},
};

map<TokenType, string> resMap = { {TokenType::IF, "if"}, {TokenType::THEN, "then"}, {TokenType::ELSE, "else"}, {TokenType::END, "end"}, {TokenType::REPEAT, "repeat"}, {TokenType::UNTIL, "until"}, {TokenType::READ, "read"}, {TokenType::WRITE, "write"}};

// scanner global variables
int inputTextIdx = 0;
int inputTextLimit = 0;
string inputText = "";
bool isError = false;

bool isSymbol(char symbol) { return symbols.find(symbol) != symbols.end(); }
bool isReservedWord(string word) { return reservedWords.find(word) != reservedWords.end(); }

// implemented via a finite state machine
// the first switch case produces output according to the current state and the other switch case switches between the states
Token getToken() {
    string output = ""; Token currentToken;
    inputTextIdx--;
    state currentState, nextState;
    int nextIndex;

    nextState = currentState = START;
    while (currentState != DONE) {
        currentState = nextState;
        nextIndex = inputTextIdx + 1;
        switch (currentState) {
        case START:
            if (isalpha(inputText[nextIndex]) || isdigit(inputText[nextIndex]) || isSymbol(inputText[nextIndex]) || inputText[nextIndex] == ':') {
                output += inputText[nextIndex];
                inputTextIdx++;
            }
            else if (inputText[nextIndex] == ' ' || inputText[nextIndex] == '\t' || inputText[nextIndex] == '\n') inputTextIdx++;
            else if (inputText[nextIndex] == '{') inputTextIdx++;
            else inputTextIdx++; // error
            if(isSymbol(inputText[inputTextIdx])) {
              currentToken.tType = specialTypes[inputText[inputTextIdx]];
            }
            break;
        case INCOMMENT:
            inputTextIdx++;
            break;
        case INASSIGN:
            if (inputText[nextIndex] == '=') {
                output += inputText[nextIndex];
                currentToken.tType = TokenType::ASSIGN;
                inputTextIdx++;
            }
            break;
        case INID:
            if (isalpha(inputText[nextIndex]) || isdigit(inputText[nextIndex])) {
                output += inputText[nextIndex];
                inputTextIdx++;
            }
            currentToken.tType = TokenType::IDENTIFIER;
            break;
        case INNUM:
            if (isdigit(inputText[nextIndex])) {
                output += inputText[nextIndex];
                inputTextIdx++;
            }
            currentToken.tType = TokenType::NUMBER;
            break;
        case DONE:
            inputTextIdx++;
            if (isReservedWord(output)) {
              currentToken.tType = reservedTypes[output];
            }
            currentToken.tVal = output;
            return currentToken;
            break;
        case ERROR:
            if(inputTextIdx == inputTextLimit && output == ""){
              currentToken.tVal = "EOF";
              currentToken.tType = TokenType::eof;
              return currentToken;
            }
            isError = true;
            currentToken.tType = TokenType::ERR;
            currentToken.tVal = output;
            return currentToken;
        default: // error
            break;
        }

        // transition from each state
        switch (currentState) {
        case START:
            if (inputText[nextIndex] == '{') nextState = INCOMMENT;
            else if (inputText[nextIndex] == ':') nextState = INASSIGN;
            else if (isalpha(inputText[nextIndex])) nextState = INID;
            else if (isdigit(inputText[nextIndex])) nextState = INNUM;
            else if (isSymbol(inputText[nextIndex])) nextState = DONE;
            else if (inputText[nextIndex] == ' ' || inputText[nextIndex] == '\t' || inputText[nextIndex] == '\n')  nextState = START;
            else nextState = ERROR;
            break;
        case INCOMMENT:
            if (inputText[nextIndex] == '}') nextState = START;
            else nextState = INCOMMENT;
            break;
        case INASSIGN:
            if (inputText[nextIndex] == '=') nextState = DONE;
            else nextState = ERROR;
            break;
        case INID:
            if (isalpha(inputText[nextIndex]) || isdigit(inputText[nextIndex])) nextState = INID;
            else nextState = DONE;
            break;
        case INNUM:
            if (isdigit(inputText[nextIndex])) nextState = INNUM;
            else nextState = DONE;
        case DONE:
            nextState = DONE; // not sure
            break;
        case ERROR:
            nextState = ERROR; // no way out
            break;
        default: // error
            break;
        }
    }
}

