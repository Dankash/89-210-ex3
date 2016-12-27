#include "ConnectGrid.h"
#include "Neighbors.h"
#include <queue>
#include <iterator>
using namespace std;


void ConnectGrid::connect(Grid &grid, Location* root, int row, int col) {

    for(int i = 0; i < row; ++i) {
        for (int j = 0; j < col ; ++j) {
            grid.getLocations()[i][j].setDistance(1000);
            grid.getLocations()[i][j].setParent(NULL);
        }
    }

    Location* current;
    queue <Location*> q;
    root->setDistance(0);
    q.push(root);

    std::list<Location*> neighbors;// = std::list<Location*>();
    list<Location*>::iterator it;
    list<Location*>::iterator end;

    while (!q.empty()) {
        if (!neighbors.empty())
            neighbors.clear();
        current = q.front();
        q.pop();
        Neighbors::neighborsList(grid, *current, neighbors);
        if(neighbors.empty())
            continue;
        it = neighbors.begin();
        end = neighbors.begin();
        std::advance(end, neighbors.size()-1);

        for (int i = 0; i < neighbors.size(); ++i) {
            if ((*it)->getDistance() == 1000) {
                (*it)->setDistance(current->getDistance() + 1);
                (*it)->setParent(current);
                q.push((*it));
            }
            if(it != end)
                std::advance(it, 1);
        }
    }
}