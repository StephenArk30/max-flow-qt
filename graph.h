#ifndef GRAPH_H
#define GRAPH_H


class graph {
private:
    int m, n, a, b;

    int *level;

    int dfs(int current_point, int max_flow);

    bool bfs();

public:
    int **adj;
    graph(int mm, int nn, int aa, int bb);

    ~graph();

    bool dinic();

    void print_connection();
};

#endif // GRAPH_H
