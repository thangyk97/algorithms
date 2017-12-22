/**
 * Author: Thangkt
 * reference: https://www.geeksforgeeks.org/a-search-algorithm/
 */
#include <iostream>
#include <set>
#include <math.h>

using namespace std;

const int COL = 10;
const int ROW = 9;

// coordinate of cell
struct coordinate {
    int x;
    int y;
};
typedef pair<double, pair<int, int>> myPair; // first is f = g + h, second is coordinate of cell
// Cell 
struct cell {
    coordinate parent; // coordinate of parent to find path
    int g;
};

cell searchMap[ROW][COL]; // only use to find path
bool close[ROW][COL]; 
bool openList[ROW][COL];
set<myPair> open;

void aStarAlgorithms(int grid[ROW][COL], coordinate start, coordinate destination);
bool isEqual(coordinate a, coordinate b);
void printPath(cell cell);
bool isValid(int x, int y);
bool expand(myPair p, coordinate temp, int grid[ROW][COL], coordinate destination);
double heuristic(coordinate a, coordinate b);

int main() {

    int grid[ROW][COL] = // 0 is wall, 1 is available cell
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    
    coordinate start;
    start.x = 8;
    start.y = 0;

    coordinate destination;
    destination.x = 0;
    destination.y = 9;

    aStarAlgorithms(grid, start, destination);

    return 0;
}

void aStarAlgorithms(int grid[ROW][COL], coordinate start, coordinate destination) {
    // Check start cell is destination
    if (isEqual(start, destination)) {
        printf("start is destination !");
        return;
    }
    // Set start cell
    searchMap[start.x][start.y].g = 0;
    open.insert(make_pair(0.0, make_pair(start.x, start.y)));
    openList[start.x][start.y] = true;

    // Loop to traveral cell
    while (!open.empty()) {
        coordinate temp;
        // erase cell from open
        myPair p = *open.begin(); // Find the move
        open.erase(open.begin());
        /* expand and add cell to open */
        int dentaX[] = {1, 1,  1, 0,  0, -1, -1, -1};
        int dentaY[] = {0, 1, -1, 1, -1,  1,  0, -1};
        
        for (int i = 0; i < 8; i++) {
            temp.x = p.second.first + dentaX[i];
            temp.y = p.second.second + dentaY[i];
            if (expand(p, temp, grid, destination)) {
                return;
            }
        }
    }
}

bool expand(myPair p, coordinate temp, int grid[ROW][COL], coordinate destination) {
    int x = temp.x;
    int y = temp.y;
    if (isValid(x, y) // check cell in search map
        && grid[x][y] // check cell is not wall
        && !openList[x][y] // check cell is not in open list
        && !close[x][y]) { //check cell is not in close list
        
        searchMap[x][y].parent.x = p.second.first;
        searchMap[x][y].parent.y = p.second.second;
        searchMap[x][y].g = searchMap[p.second.first][p.second.second].g + 1;

        if (isEqual(temp, destination)) {
            cout<<"the path is: ";
            printPath(searchMap[x][y]);
            cout<<"("<<temp.x<<", "<<temp.y<<")"<<endl;
            return true;
        }
        open.insert( 
            make_pair(heuristic(temp, destination) + searchMap[x][y].g, 
                      make_pair(x,y))
            ); 
        openList[x][y] = true; 
        
    }
    return false;
}

double heuristic(coordinate a, coordinate b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

void printPath(cell cell) {
    if (cell.g == 0) {
        return;
    }
    printPath(searchMap[cell.parent.x][cell.parent.y]);
    cout<<"("<<cell.parent.x<<", "<<cell.parent.y<<")->";
}

bool isValid(int x, int y) {
    if (x >= 0 && x < ROW && y >= 0 && y < COL) {
        return true;
    } else {
        return false;
    }
}

bool isEqual(coordinate a, coordinate b) {
    if (a.x == b.x && a.y == b.y) {
        return true;
    } else {
        return false;
    }
}