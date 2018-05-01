//
// Created by jared on 4/23/18.
//
#include "Parse.h"
#include "ExpTree.h"
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

/* Function Definitions */
void whichName(const char*);
void tokenType(const char*);

/* Globals */
vector<Node*> expr;
map<string, int> table;

void pushSymbol(const char* token) {
    string s = token;
    auto opNode = new Node(false, 0, s);
    expr.push_back(opNode);
}
void pushNum(int x) {
    auto intNode = new Node(true, x, "\0");
    expr.push_back(intNode);
}
void pushNum(const char* token) {
    auto intNode = new Node(true, token_number_value, "\0");
    expr.push_back(intNode);
}
int evalTree() {
    auto tree = new ExpTree(expr);
    int res = tree->parse();
    expr.clear();
    return res;
}
// executes code for each name token
void whichName(const char* token) {
    string s = token;
    if(table.find(s) != table.end()) {
        cout << table[s] << flush;
    }
    if (!strcmp(token,"text")) {
        read_next_token();
        token = next_token();
        cout << token << flush;
        return;
    }
    if (!strcmp(token,"var")) {
        read_next_token();
        string var = token;
        read_next_token();
        int num = token_number_value;
        table.insert(make_pair(var, num));
        return;
    }
    if (!strcmp(token,"set")) {
        read_next_token();
        string var = token;
        int num = table[var];
        read_next_token();
        string a = token;
        while(a != "set" && a != "var" && a != "text" && a != "output") {
            if (next_token_type == SYMBOL) {
                pushSymbol(token);
                read_next_token();
                a = token;
                continue;
            }
            if (next_token_type == NUMBER) {
                pushNum(token);
                read_next_token();
                a = token;
                continue;
            }
            if (table.find(a) != table.end()) {
                num = table[token];
                pushNum(num);
                read_next_token();
                a = token;
            }
        }
        table[var] = evalTree();
        return;
    }
    if (!strcmp(token,"output")) {
        read_next_token();
        token = next_token();
        tokenType(token);
        return;
    }

}
// determines type of token and executes corresponding function
void tokenType(const char* token) {
    if(token[0] == '/' && token[1] == '/') {
        string s = peek_next_token();
        while (s != "var" && s != "set" && s != "output" && s != "text") {
            read_next_token();
            s = next_token();
        }
    }
    string s = token;
    if(table.find(s) != table.end()) {
        next_token_type = NUMBER;
        int num = table[s];
        pushNum(num);
        read_next_token();
        return tokenType(token);
    }
    if(next_token_type == SYMBOL){
        pushSymbol(token);
        read_next_token();
        return tokenType(token);
    }
    if(next_token_type == NUMBER){
        pushNum(token);
        read_next_token();
        return tokenType(token);
    }
    if(next_token_type == NAME){
        if(!expr.empty()) {
            int res = evalTree();
            cout << res << flush;
        }
        whichName(token);
    }

}

void run() {
    while(next_token_type != END) {
        const char *token = next_token();
        if(*token == '\0') {
            read_next_token();
            continue;
        }
        tokenType(token);
        string a = token;
        if(a != "set" && a != "var" && a != "text" && a != "output") {
            read_next_token();
        }
    }
}
int main() {
    set_input("test_grader.blip");
    run();
}