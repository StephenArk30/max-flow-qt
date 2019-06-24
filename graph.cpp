#include <queue>
#include <iostream>
#include <string.h>
#include "graph.h"

using namespace std;

/**
 * 0: start; m+n+1: destination
 * 1 to m: paper; m+1 to m+n: reviewer
 * */
graph::graph(int mm, int nn, int aa, int bb) : m(mm), n(nn), a(aa), b(bb) {
    adj = new int *[m + n + 2];
    level = new int[m + n + 2];

    int i, j;
    for (i = 0; i < m + n + 2; ++i) {
        adj[i] = new int[m + n + 2];
        memset(adj[i], 0, sizeof(int) * (m + n + 2));
        if (i == 0)
            for (j = 1; j <= m; ++j) adj[i][j] = a;
        else if (i <= m)
            for (j = m + 1; j < m + n + 1; ++j) adj[i][j] = 1;
        else if (i != m + n + 1) adj[i][m + n + 1] = b;
    }
}

graph::~graph() {
    for (int i = 0; i < m + n + 2; ++i) delete[] adj[i];
    delete[] adj;
    delete[] level;
}

bool graph::dinic() {
//    if (a > n || a*m > b*n) return false;
    int max_flow = 0;
    while (bfs()) max_flow += dfs(0, a);
    return max_flow == a * m;
}

/**
 * max_flow arrive node1, node1 try to find a path to transfer remain_flow, till remain_flow == 0
 * or if remain_flow can't be sent completely, return transferred flow (max_flow - remain_flow)
 * */
int graph::dfs(int current_point, int max_flow) {
    if (current_point == m + n + 1) return max_flow;
    int temp;
    int remain_flow = max_flow;

    for (int i = 0; i < m + n + 2; ++i) {
        if (adj[current_point][i] > 0 && level[i] == level[current_point] + 1) {
            temp = dfs(i, min(remain_flow, adj[current_point][i]));
            if (temp > 0) {
                remain_flow -= temp;
                adj[i][current_point] += temp; // add reverse edge
                adj[current_point][i] -= temp; // minus current edge
                if (remain_flow == 0) return max_flow;
            }
        }
    }
    return (max_flow - remain_flow);
}

bool graph::bfs() {
    memset(level, -1, sizeof(int) * (m + n + 2));
    queue<int> q;
    q.push(0);
    level[0] = 0;
    int current_point, i;
    while (!q.empty()) {
        current_point = q.front();
        q.pop();
        for (i = 0; i < m + n + 2; ++i) {
            if (adj[current_point][i] > 0 && level[i] < 0) {
                level[i] = level[current_point] + 1;
                q.push(i);
            }
        }
    }
    return level[m + n + 1] > 0;
}

void graph::print_connection() {
    cout << "paper\treviewer\n";
    for (int i = m + 1; i < m + n + 1; ++i)
        for (int j = 1; j < m + 1; ++j)
            if (adj[i][j] > 0) cout << j << "\t\t" << i - m << endl;
}
