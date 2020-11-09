#include <vector>
#include <algorithm>
#include <iostream>
#include "cell.h"
#include "piece.h"
#include "grid.h"
#include "constants.h"

using namespace std;

Grid::Grid() {
    // Fill underlay vector with empty cells
    underlay.resize(20);
    for(int i = 0; i < 20; ++i){
        vector<Cell> v(10);
        v.resize(10);
        for(int j = 0; j < 10; ++j) {
            v[j] = (Cell {0,0,0,0, false});
        }
        underlay[i] = v;
    }
    currentPiece = Piece();
    rightMost = windowWidth - ((windowWidth - gridWidth) / 2);
    bottomMost = windowHeight - ((windowHeight - gridHeight) / 2);
    leftMost = rightMost - gridWidth;
    topMost = bottomMost - gridHeight;
    cellWidth = gridWidth / 10;
    cellHeight = gridHeight / 20;
}

int Grid::update(int dx, int dy, bool cw, bool ccw) {
    int linesCleared = 0; 
    // Clear lines
    for(int i = 0; i < 19; ++i) {
        bool isClear = true;
        for(int j = 0; j < 10; ++j) {
            isClear = underlay[i][j].occupied && !currentPiece.isAt(make_pair(j, i)) && isClear;
        }
        if(isClear) {
            fill(underlay[i].begin(), underlay[i].end(), Cell {0,0,0,0, false});
            ++linesCleared;
        }
    }
    _score += linesCleared * linesCleared * 100;

    //Shift lines down
    for(unsigned int i = 0; i < underlay.size() - 1; ++i) {
        if(none_of(underlay[i].cbegin(), underlay[i].cend(), [](Cell c) {return c.occupied;})) {
            bool occByUs = false;
            for(unsigned int j = 0; j < underlay[i].size(); ++j) { occByUs = currentPiece.isAt(make_pair(j, i + 1 )) || occByUs; }
            if(!occByUs) { 
                underlay[i] = underlay[i + 1];
                fill(underlay[i + 1].begin(), underlay[i + 1].end(), Cell {0,0,0,0, false});
            }
        }
    }

    // Clear old locs

    for(pair<int, int> loc : currentPiece.locs()) { underlay[loc.second][loc.first] = Cell {0,0,0,0, false};}

    chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();

    if(chrono::duration_cast<chrono::milliseconds>(t - lastFall).count() >= 1200) {
        lastFall = t;
        dy = max(-1, dy - 1);
    }

    // Update controlled piece
    currentPiece.update(dx, dy, cw, ccw, underlay);

    // Update underlay after moves 
    for(pair<int, int> loc : currentPiece.locs()) { underlay[loc.second][loc.first] = Cell {currentPiece.getA(),
                                                                                            currentPiece.getR(),
                                                                                            currentPiece.getG(),
                                                                                            currentPiece.getB(),
                                                                                            true }; };

    if(currentPiece.landed()) currentPiece = Piece();
    return 1;
}

void Grid::render(Renderer renderer) {
    for(unsigned int i = 0; i < underlay.size(); ++i) {
        for(unsigned int j = 0; j < underlay[i].size(); ++j) {
            Cell jCell = underlay[i][j];
            int cellX = leftMost + j * cellWidth;
            int cellY = topMost + i * cellHeight;
            renderer.drawRect(cellX, bottomMost - cellY, cellWidth, cellHeight, 0, 50, 50, 50);
            if(jCell.occupied) renderer.fillRect(cellX + 2, bottomMost - cellY + 2, cellWidth - 2, cellHeight - 2, jCell.a, jCell.r, jCell.g, jCell.b);
        }
    }
    renderer.drawText(std::to_string(_score), scoreX, scoreY, scoreWidth, scoreHeight, 255, 255, 255, 255);
}