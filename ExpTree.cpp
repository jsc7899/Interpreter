//
// Created by Vallath Nandakumar on 11/15/17.
//

#include "ExpTree.h"
#include <string>
#define DEBUG true
ExpTree::ExpTree(vector<Node*>& expr) { // construct from expression vector
    overallRoot = add(overallRoot, expr);
}

// private method
Node* ExpTree::add(Node* root, vector<Node*>& expr) { // passing expr as a reference
    Node* first = expr[0]; // store the first element
    expr.erase(expr.begin()); // remove the first element
    root = first; // root points to the first token Node
    if (!(first->isOperand)) {// if first is an operator, add 2 operands
        if(first->optr == "!" || first->optr == "~") {
            root->left = add(root->left, expr);
        }
        else {
            root->left = add(root->left, expr);
            root->right = add(root->right, expr);
        }
    }
    return root; // return the new sub-tree
}

void ExpTree::printTree() {
    printTree(overallRoot, 0); // call helper method
}

void ExpTree::printSpaces(int level) { // print 4 spaces per level, for indentation
    for (int i = 0; i < level*4; i++) {
        cout << ' ';
    }
}

// private recursive helper method
void ExpTree::printTree(Node* root, int level) {
    if (root == nullptr) return;
    printTree(root->right, level+1); // print the right sub-tree
    printSpaces(level); // print the indentation for the root of sub-tree
    root->print(); // print the root
    printTree(root->left, level+1); // print the left sub-tree
}

int ExpTree::parse() {

    return parse(overallRoot);
}

int ExpTree::parse(Node* root) {
    int result;
    if(root == nullptr) return 0;

    if(root->optr == "+") {
        result = parse(root->left) + parse(root->right);
    }
    else if(root->optr == "-") {
        result = parse(root->left) - parse(root->right);
    }
    else if(root->optr == "%") {
        result = parse(root->left) % parse(root->right);
    }
    else if(root->optr == "/") {//TODO division by 0
        result = parse(root->left) / parse(root->right);
    }
    else if(root->optr == "*") {
        result = parse(root->left) * parse(root->right);
    }
    else if(root->optr == "<") {
        result = parse(root->left) < parse(root->right);
    }
    else if(root->optr == ">") {
        result = parse(root->left) > parse(root->right);
    }
    else if(root->optr == "<=") {
        result = parse(root->left) <= parse(root->right);
    }
    else if(root->optr == ">=") {
        result = parse(root->left) >= parse(root->right);
    }
    else if(root->optr == "==") {
        result = parse(root->left) == parse(root->right);
    }
    else if(root->optr == "!=") {
        result = parse(root->left) != parse(root->right);
    }
    else if(root->optr == "&&") {
        result = parse(root->left) && parse(root->right);
    }
    else if(root->optr == "||") {
        result = parse(root->left) || parse(root->right);
    }
    else if(root->optr == "~") {
        result = -(parse(root->left));
    }
    else if(root->optr == "!") {
        result = !(parse(root->left));
    }
    else {
        return root->operand;
    }
    return result;
}
