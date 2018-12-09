#include <stdio.h>
#include <iostream>
#include <stdlib.h>

struct Node {
    int x;
    Node* left;
    Node* right;
}node[1001];

int loc = 0;

Node* create (int x) {
    node[loc].left = node[loc].right = NULL;
    node[loc].x = x;
    return &node[loc++];
}

Node* insert (Node* p, int x) {
    if (p == NULL) {
        return create (x);
    }
    else if (p -> x < x) {
        // right
        p -> right = insert (p -> right, x);
    }
    else if (p -> x > x) {
        // left
        p -> left = insert (p -> left, x);
    }
    return p;
}

void preorder (Node* p) {
    printf("%d ", p -> x);
    if (p -> left != NULL) preorder(p -> left);
    if (p -> right != NULL) preorder(p -> right);
}

int main () {
    int x;
    Node* root = NULL;
    while (scanf("%d", &x) != EOF) {
        root = insert (root, x);
    }

    preorder (root);
    printf("\n");
    return 0;
}
