#pragma once
#include "Pendulum.h"

class SimplePendulum :
    public Pendulum
{
public:
    SimplePendulum(double px, double py, double L, double amplitude, double mass);

    void update(const double& gravity);
    void render();
};

