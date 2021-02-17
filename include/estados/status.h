#include "../fachada/sprite.h"

using namespace std;

#pragma once

class Status{
    protected:

    public:
        Status();
        virtual void handle() = 0;
        virtual void update(float) = 0;
        virtual void render(float) = 0;
};