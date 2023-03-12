#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <algorithm>

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


int height(Node * root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

bool isLeaf(Node* root)
{
    return (root != NULL) && (!root->left && !root->right);
}

bool equalPaths(Node * root)
{
    // Add your code below
    if (root == NULL) return true;
    else if ((isLeaf(root->left) && !root->right) || (isLeaf(root->right) && !root->left)) return true;
    return (height(root->left) == height(root->right));
}



