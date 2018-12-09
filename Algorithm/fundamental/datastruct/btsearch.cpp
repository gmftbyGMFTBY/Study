#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
/*
   the same btsort have the same preorder and the same inorder
 */

struct Node {
    Node* lchild;
    Node* rchild;
    int c;
}Tree[110];

int loc;

using namespace std;

Node* create () {
    Tree[loc].lchild = Tree[loc].rchild = NULL;
    return &Tree[loc++];
}

char str1[25], str2[25];
int size1, size2;
char* str;
int* size;

void postorder (Node* T) {
    if (T -> lchild != NULL) {
        postorder(T -> lchild);
    }
    if (T -> rchild != NULL) {
        postorder(T -> rchild);
    }

    // be careful that (*size)++ not *(size)++
    str[(*size) ++] = T -> c + '0';
}

void inorder (Node* T) {
    if (T -> lchild != NULL) inorder(T -> lchild);
    str[(*size) ++] = T -> c + '0';
    if (T -> rchild != NULL) inorder(T -> rchild);
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
    return T;
}

int main () {
    int n;
    char tmp[12];
    while (scanf("%d", &n) != EOF && n != 0) {
        loc = 0;
        Node* T = NULL;
        scanf("%s", tmp);

        // create the binarysort tree
        for (int i = 0; tmp[i] != 0; i ++) {
            T = insert(T, tmp[i] - '0');
        }

        size1 = 0;
        str = str1;
        size = &size1;

        // put the inorder string and postorder string together to judge whether the same
        postorder(T);
        inorder(T);
        str1[size1] = 0;

        while (n--) {
            scanf("%s", tmp);
            Node* T2 = NULL;
            for (int i = 0; tmp[i] != 0; i ++) {
                T2 = insert(T2, tmp[i] - '0');
            }
            size2 = 0;
            str = str2;
            size = &size2;
            postorder(T2);
            inorder(T2);
            str2[size2] = 0;
            puts(strcmp(str1, str2) == 0 ? "YES" : "NO");
        }
    }
    return 0;
}
