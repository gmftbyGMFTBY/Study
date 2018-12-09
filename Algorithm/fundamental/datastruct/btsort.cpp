#include <iostream>
#include <string.h>
#include <stdlib.h>

/*
   middle-visit is a sorted sequence
 */

using namespace std;

struct Node {
    Node* lchild;
    Node* rchild;
    int c;
}Tree[100];

int loc;
Node* create() {
    Tree[loc].lchild = Tree[loc].rchild = NULL;
    return &Tree[loc++];
}

void postorder (Node* T) {
    if (T -> lchild != NULL) postorder(T -> lchild);
    if (T -> rchild != NULL) postorder(T -> rchild);
    printf("%d", T -> c);
}

void inorder (Node* T) {
    if (T -> lchild != NULL) inorder(T -> lchild);
    printf("%d", T -> c);
    if (T -> rchild != NULL) inorder(T -> rchild);
}

void preorder (Node* T) {
    printf("%d", T -> c);
    if (T -> lchild != NULL) preorder(T -> lchild);
    if (T -> rchild != NULL) preorder(T -> rchild);
}

Node* insert (Node* T, int x) {
   if (T == NULL) {
       T = create();
       T -> c = x;
       return T;
   } 
   else if (x < T -> c) {
       T -> lchild = insert(T -> lchild, x);
   }
   else if (x > T -> c) {
       T -> rchild = insert(T -> rchild, x);
   }
   return T;    // return T node itself
}

int main () {
    int n;
    while (scanf("%d", &n) != EOF) {
        loc = 0;
        Node* T = NULL;
        for (int i = 0; i < n; i++) {
            int x;
            scanf("%d", &x);
            T = insert(T, x);
        }
        preorder(T);
        printf("\n");
        inorder(T);
        printf("\n");
        postorder(T);
        printf("\n");
    }
    return 0; 
}
