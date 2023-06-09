#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "tokenizer.h"
#include "ast.h"

// Determines whether an AST is valid by checking
// whether it can be solved recursively, either with 
// or without plugging in numbers for a VAR node.
// Note: might refactor this into simplifying
bool isValidTree(ASTNode* tree);

// Simplifies the tree by rearranging it and solving
// as much as possible to give it a cleaner AST tree
void simplify(ASTNode* tree);

#endif