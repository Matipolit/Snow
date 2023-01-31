#include <iostream>

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle{
  private:
    int x;
    int y;
    int timeSinceLastSwing;
    int lastSwingDirection;
    int swingTime;
    
  public:
    Particle(int begX, int begY);
    Particle();
    int getx();
    int gety();
    void move();
    void respawn(int begX);
};
#endif
