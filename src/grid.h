#pragma once

#include<vector>
#include "cell.h"
#include "piece.h"
#include "renderer.h"
#include <chrono>

using namespace std;
class Grid {
private:
    vector<vector<Cell>> underlay;
    int _score = 0;
    Piece currentPiece;
    int leftMost;
    int topMost;
    int rightMost;
    int bottomMost;
    int cellWidth;
    int cellHeight;
    chrono::high_resolution_clock::time_point lastFall;
public:
    Grid();
    int update(int dx, int dy, bool cw, bool ccw);
    vector<vector<Cell>> viewUnderlay() { return underlay; }
    void render(Renderer renderer);
};
