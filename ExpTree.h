//
// Created by Vallath Nandakumar on 11/15/17.
//

#ifndef _EXPTREE_H
#define _EXPTREE_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    bool isOperand;
    int operand;
    string optr;
    Node* left;
    Node* right;
    Node(bool isOperand, int operand, string optr) {
        left = nullptr;
        right = nullptr;
        this->isOperand = isOperand;
        this->operand = operand;
        this->optr = optr;
    }
    void print() {
        if (isOperand) {
            cout << operand << endl;
        } else {
            cout << optr << endl;
        }
    }
};
class ExpTree {
private:
    const int spaces_per_level = 4;
    Node* overallRoot;
    Node* add(Node* root, vector<Node*>&);
    void printTree(Node*, int);
    void printSpaces(int);
    int parse(Node*);
public:
    int parse();
    ExpTree(vector<Node*>& expr); // constructor
    void printTree();
};


#endif //DAY22_EXPRESSIONTREE_EXPTREE_H
