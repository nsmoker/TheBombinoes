#include "piece.h"
#include "constants.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include<ctime>
#include<iostream>

using namespace std;

void Piece::moveX(int dx, vector<vector<Cell>> underlay) {
    bool canProceed = true;
    for(auto loc : newLocs) {
        if(loc.first + dx > 9 || loc.first + dx < 0) {
            canProceed = false; 
        }
        if(underlay[loc.second][loc.first + dx].occupied) {
            canProceed = isAt(make_pair(loc.first + dx, loc.second)) && canProceed; 
        }    
    }
    if(canProceed) {
        for(unsigned int i = 0; i < 4; ++i) {
            newLocs[i] = make_pair(newLocs[i].first + dx, newLocs[i].second);
        }    
        pivot = make_pair(pivot.first + dx, pivot.second);
    }
}

void Piece::moveY(int dy, vector<vector<Cell>> underlay) {
    bool canProceed = true;
    for(auto loc : newLocs) {
        if(loc.second + dy > 19 || loc.second + dy < 0) {
            canProceed = false; 
            break;
        }
        if(underlay[loc.second + dy][loc.first].occupied) {
            canProceed = isAt(make_pair(loc.first, loc.second + dy)) && canProceed; 
        }       
    }
    if(canProceed) {
        for(unsigned int i = 0; i < 4; ++i) {
            newLocs[i] = make_pair(newLocs[i].first, newLocs[i].second + dy);
        }
        pivot = make_pair(pivot.first, pivot.second + dy);
    } else {
        _landed = true;
    }
}

Piece::Piece(vector<pair<int, int>> locs, int a, int r, int g, int b) {
    _locs = locs;
    _a = a;
    _r = r;
    _b = b;
    _g = g;
    for(auto loc : _locs) {
        if(loc.first > rightMost) rightMost = loc.first;
        if(loc.first < leftMost) leftMost = loc.first;
        if(loc.second > bottomMost) bottomMost = loc.second;
        if(loc.second < topMost) topMost = loc.second;
    }
    pivot = make_pair( (leftMost + rightMost) / 2.0, (topMost + bottomMost) / 2.0);
    newLocs = _locs;
}

Piece pieceI = Piece({
        pair<int, int>(2, 19),
        pair<int, int>(3, 19),
        pair<int, int>(4, 19),
        pair<int, int>(5, 19)
    }, 255, 173, 216, 230);

Piece pieceO = Piece({
        pair<int, int>(3, 19),
        pair<int, int>(4, 19),
        pair<int, int>(3, 18),
        pair<int, int>(4, 18)
    }, 255, 255, 255, 0);

Piece pieceJ = Piece({
        pair<int, int>(3, 19),
        pair<int, int>(4, 19),
        pair<int, int>(5, 19),
        pair<int, int>(5, 18)
    }, 255, 0, 0, 139);

Piece pieceL = Piece({
        pair<int, int>(3, 19),
        pair<int, int>(4, 19),
        pair<int, int>(5, 19),
        pair<int, int>(3, 18)
    }, 255, 255, 165, 0);

Piece pieceS = Piece({
        pair<int, int>(4, 19),
        pair<int, int>(4, 18),
        pair<int, int>(5, 18),
        pair<int, int>(5, 17)
    }, 255, 0, 255, 0);


Piece pieceZ = Piece({
        pair<int, int>(5, 19),
        pair<int, int>(5, 18),
        pair<int, int>(4, 18),
        pair<int, int>(4, 17)
    }, 255, 255, 0, 0);

Piece pieceT = Piece({
        pair<int, int>(3, 19),
        pair<int, int>(4, 19),
        pair<int, int>(4, 18),
        pair<int, int>(5, 19)
    }, 255, 255, 0, 255);

vector<Piece> allPieces = { pieceI, pieceJ, pieceL, pieceO, pieceS, pieceT, pieceZ };

Piece::Piece() {
    srand(time(NULL));
    Piece pci = allPieces[rand() % 6];
    _locs = pci.locs();
    _a = pci.getA();
    _r = pci.getR();
    _g = pci.getG();
    _b = pci.getB();
    for(auto loc : _locs) {
        if(loc.first > rightMost) rightMost = loc.first;
        if(loc.first < leftMost) leftMost = loc.first;
        if(loc.second > bottomMost) bottomMost = loc.second;
        if(loc.second < topMost) topMost = loc.second;
    }
    pivot = make_pair( (leftMost + rightMost) / 2.0, (topMost + bottomMost) / 2.0);
    newLocs = _locs;
}

void Piece::rotate(bool cw, vector<vector<Cell>> underlay) {
    vector<pair<int, int>> ns;
    for(auto loc : newLocs) {
        double centerX = (double) loc.first + 0.5;
        double centerY = (double) loc.second + 0.5;
        pair<int, int> newLoc = make_pair(pivot.first + pivot.second - centerY, pivot.second - pivot.first + centerX);
        ns.push_back(newLoc);
    }
    bool canProceed = true;
    for(auto loc : ns) {
        if(loc.first > 9 || loc.first < 0 || loc.second > 19 || loc.second < 0 
        || (underlay[loc.second][loc.first].occupied && !isAt(loc))) {
            canProceed = false;
            break;
        }
    }
    if(canProceed) { 
        newLocs = ns;
    }
}

void Piece::update(int dx, int dy, bool cw, bool ccw, vector<vector<Cell>> underlay) {
    newLocs = _locs;
    if(cw) rotate(true, underlay);
    if(ccw) rotate(false, underlay);
    moveX(dx, underlay);
    moveY(dy, underlay);
    _locs = newLocs;
}

bool Piece::isAt(pair<int, int> loc) { 
    bool ret = false;
    for(auto locp : newLocs) {
        if(locp.first == loc.first && locp.second == loc.second) {
            ret = true;
        }
    }
    return ret; 
}

Piece pieceNo(int i) { return allPieces[i]; }