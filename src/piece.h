#pragma once

#include "cell.h"
#include <vector>
#include "renderer.h"

using namespace std;

class Piece {
private: 
    vector<pair<int, int>> _locs = {};
    bool _landed = false;
    int _a = 0;
    int _r = 0;
    int _g = 0;
    int _b = 0;
    int leftMost = 19;
    int topMost = 19;
    int bottomMost = 0;
    int rightMost = 0;
    pair<double, double> pivot;
    void moveX(int dx, vector<vector<Cell>> underlay);
    void moveY(int dy, vector<vector<Cell>> underlay);
    vector<pair<int, int>> newLocs;
public:
    Piece(vector<pair<int, int>>, int a, int r, int g, int b);
    Piece();
    void rotate(bool cw, vector<vector<Cell>> underlay);
    void update(int dx, int dy, bool cw, bool ccw, vector<vector<Cell>> underlay);
    void render(Renderer renderer);
    int getA() { return _a; }
    int getR() {return _r;}
    int getG() {return _g;}
    int getB() {return _b;}
    bool landed() { return _landed; };
    bool isAt(pair<int, int> loc);
    vector<pair<int, int>> locs() { return _locs; }
};