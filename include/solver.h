#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "tokenizer.h"
#include "ast.h"

// Simplifies the tree by rearranging it and solving
// as much as possible to give it a cleaner AST tree
void simplify(ASTNode* tree);

#endif