#pragma once

class GuiElement {
    virtual int xLoc();
    virtual int yLoc();
    virtual void draw();
    virtual void onInteract();
};