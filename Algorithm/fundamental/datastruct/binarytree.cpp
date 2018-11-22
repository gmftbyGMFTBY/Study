#include <iostream>
#include <stdio.h>
#include <string.h>

/*
   BinaryTree struct in the C node
   first-visit and middle-visit can get the after-visit

   build the binarytree need middle-visit and first-visit
 */

using namespace std;

struct Node {
    Node *lchild;
    Node *rchild;
    char c;    // other information of the node
}Tree[26];

int loc;

Node* create () {
    Tree[loc].lchild = Tree[loc].rchild = NULL;
    return &Tree[loc ++];
}

char str[30];
char str2[30];

void postorder (Node* T) {
    if (T -> lchild != NULL) {
        postorder(T -> lchild);
    }
    if (T -> rchild != NULL) {
        postorder(T -> rchild);
    }
    printf("%c", T -> c);
}

// s1 -> e1 first-order, s2 -> e2 middle order
Node* build(int s1, int e1, int s2, int e2) {
    Node* ret = create();
    ret -> c = str[s1];
    int rootidx;
    for (int i = s2; i <= e2; i++) {
        if (str2[i] == str[s1]) {
            rootidx = i;
            break;
        }
    }
    if (rootidx != s2) {
        ret -> lchild = build(s1 + 1, s1 + (rootidx - s2), s2, rootidx - 1);
    }

    if (rootidx != e2) {
        ret -> rchild = build(s1 + (rootidx - s2) + 1, e1, rootidx + 1, e2);
    }

    return ret;
}

int main () {
    while (scanf("%s", str) != EOF) {
        scanf("%s", str2);
        loc = 0;
        int L1 = strlen(str);
        int L2 = strlen(str2);
        Node* T = build(0, L1 - 1, 0, L2 - 1);
        postorder(T);
        printf("\n");
    }
    return 0;
}
