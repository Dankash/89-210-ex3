#include "ConnectGrid.h"
#include "Neighbors.h"
#include <queue>
#include <iterator>
using namespace std;


void ConnectGrid::connect(Grid *grid, Location* root, int row, int col) {

    grid->resetGrid();

    for (int i = 0; i < grid->getRow(); ++i) {
        for (int j = 0; j < grid->getCol(); ++j) {
            cout << "cG:: " << i << "," << j <<" ";
            if (grid->getLocations()[i][j] == *root) {
                root = &(grid->getLocations()[i][j]);
                break;
            }
        }
        cout <<endl;
    }

    cout<< "after first loop connect grid $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

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
//        if (q.front()->getDistance() != -1 && q.front()->getDistance() != 0)
//            current->setDistance(1000);
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