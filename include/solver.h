#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "tokenizer.h"
#include "ast.h"

// checks whether a tree can be simplified
// into a number node, if all variable nodes
// are replaced. This checks for whether functions
// have the correct number of arguments
// cannot be used on an already simplified tree
bool canBeSimplified(ASTNode* tree);

// Simplifies the tree by rearranging it and solving
// as much as possible to give it a cleaner AST tree
// An error is thrown if the current tree is not valid
void simplify(ASTNode* tree);

// Evaluates the tree at a given x value
// Throws an invalid_argument error if tree cannot be simplified
double evaluateAtX(ASTNode* tree, double x);

#endif