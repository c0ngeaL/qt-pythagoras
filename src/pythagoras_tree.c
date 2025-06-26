#include "pythagoras_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EMPTY ' '
#define FILLED '#'

void draw_line(char* buffer, int width, int height, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
            buffer[y1 * (width + 1) + x1] = FILLED;
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
void draw_rect(char* buffer, int width, int height, int x1, int y1, int L, double a1) {
    int x2 = x1 + (int)(L * cos(a1));
    int y2 = y1 - (int)(L * sin(a1));
    int x3 = x1 + (int)(L * sqrt(2) * cos(a1 + M_PI/4));
    int y3 = y1 - (int)(L * sqrt(2) * sin(a1 + M_PI/4));
    int x4 = x1 + (int)(L * cos(a1 + M_PI/2));
    int y4 = y1 - (int)(L * sin(a1 + M_PI/2));
    draw_line(buffer, width, height, x1, y1, x2, y2);
    draw_line(buffer, width, height, x2, y2, x3, y3);
    draw_line(buffer, width, height, x3, y3, x4, y4);
    draw_line(buffer, width, height, x4, y4, x1, y1);
}

void build_branch(char* buffer, int width, int height, Branch branch) {
    if (branch.depth <= 0) return;

    branch.x2 = branch.x1 + (int)(branch.length * cos(branch.angle));
    branch.y2 = branch.y1 - (int)(branch.length * sin(branch.angle));

    draw_line(buffer, width, height, branch.x1, branch.y1, branch.x2, branch.y2);

    Branch left = {
        .x1 = branch.x2,
        .y1 = branch.y2,
        .length = branch.length * 0.7,
        .angle = branch.angle + M_PI / 4,
        .depth = branch.depth - 1
    };

    Branch right = {
        .x1 = branch.x2,
        .y1 = branch.y2,
        .length = branch.length * 0.7,
        .angle = branch.angle - M_PI / 4,
        .depth = branch.depth - 1
    };

    build_branch(buffer, width, height, left);
    build_branch(buffer, width, height, right);
}
void generate_pythagoras_tree(char* buffer, int width, int height, int max_depth) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y * (width + 1) + x] = EMPTY;
        }
        buffer[y * (width + 1) + width] = '\n';
    }
    buffer[height * (width + 1)] = '\0';
    Branch trunk = {
        .x1 = width / 2,
        .y1 = height - 1,
        .length = height / 3,
        .angle = M_PI / 2,
        .depth = max_depth
    };

    build_branch(buffer, width, height, trunk);
}
