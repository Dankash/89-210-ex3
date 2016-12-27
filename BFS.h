
#ifndef ASS1_BFS_H
#define ASS1_BFS_H

#include "Grid.h"
#include <stack>
using namespace std;

/**
 * prints the way from the source to the destination point.
 */
class BFS {
public:
    /**
 * prints the way from the source to the
 * destnation point.
 * @param grid - reference of the  grid.
 * @param source - source point.
 * @param destination - destination point.
 */
    static std::stack<Point> bfs(Grid& grid, Point source, Point destination);
};


#endif //ASS1_BFS_H
