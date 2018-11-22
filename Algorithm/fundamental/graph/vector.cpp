#include <iostream>
#include <stdio.h>
#include <vector>
#define N 10

using namespace std;

struct Edge {
    int nextnode;
    int cost;
};

/*
   vector for link table
       1. edge[i].clear()    clear the link table
       2. edge[i].push_back[Edge()]    push the Edge struct into the link table
       3. edge[i].size()     the size of this link table (long int %ld)
       4. edge[i][index]     we can use the index to access the link table's element
       5. edge[i].erase()
            delete the i element in edge[i]
            edge[i].erase(edge[i].begin() + i, edge[i].begin() + i + 1)
 */

int main () {
    vector<Edge> edge[N];    // edge[i] means the node i's link table
    // init
    for (int i = 0; i < N; i ++) edge[i].clear();

    // push_back
    Edge tmp;
    tmp.nextnode = 3;
    tmp.cost = 38;
    edge[1].push_back(tmp);

    // size and access
    printf("%ld\n", edge[1].size());

    for (int i = 0; i < edge[1].size(); i ++) {
        int nextnode = edge[1][i].nextnode;
        int cost = edge[1][i].cost;
        printf("%d %d\n", nextnode, cost);
    }

    // delete
    edge[1].erase(edge[1].begin(), edge[1].begin() + 1);
    
    printf("--------------------------\n");

    vector<vector<int>> matrix;
    for (int i = 0; i < 3; i++) {
        vector<int> tmp;
        for (int j = 0; j < 3; j++) {
            tmp.push_back(0);
        }
        matrix.push_back(tmp);
    }

    for (int i = 0; i < matrix.size(); i ++) {
        for (int j = 0; j < matrix[i].size(); j ++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
