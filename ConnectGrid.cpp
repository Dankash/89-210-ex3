#include "ConnectGrid.h"
#include "Neighbors.h"
#include <queue>
#include <iterator>
using namespace std;


void ConnectGrid::connect(Grid *grid, Location* root, int row, int col) {

    int i,j;
    int neighborsSize;
    grid->resetGrid();

    for (i = 0; i < grid->getRow(); ++i) {
        for (j = 0; j < grid->getCol(); ++j) {
            if (grid->getLocations()[i][j] == *root) {
                root = &(grid->getLocations()[i][j]);
                break;
            }
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
        //Neighbors::neighborsList(grid, *current, neighbors);
        neighbors = current->getNeighbors();
        //cout<< "after neighbors: " << endl;

        if(neighbors.empty())
            continue;
        it = neighbors.begin();
        end = neighbors.begin();
        std::advance(end, neighbors.size()-1);

        neighborsSize = (int) neighbors.size();
        for (i = 0; i < neighborsSize; i++) {

            //cout << "point " << ((*it))->getPoint() << endl;
            //cout << "neighborsSize = " << neighborsSize << ", connect grid second loop: " << i << endl;

            if ((*it)->getDistance() == 10000) {
                (*it)->setDistance(current->getDistance() + 1);
                (*it)->setParent(current);
                q.push((*it));
            }

            std::advance(it, 1);
        }
    }

}