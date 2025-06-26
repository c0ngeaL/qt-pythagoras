#ifndef PYTHAGORAS_TREE_H
#define PYTHAGORAS_TREE_H

typedef struct {
    int x1, y1;
    int x2, y2;
    double length;
    double angle;
    int depth;
} Branch;

void generate_pythagoras_tree(char* buffer, int width, int height, int max_depth);

#endif
