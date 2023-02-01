#include "Particle.h"

int randDir(){
  if(rand() % 2 == 0){
    return -1;
  }
  return 1;
}

int getRandSwingTime(){
  return rand() % 20 + 10;
}

Particle::Particle(int begX, int begY){
  x = begX;
  y = begY;
  timeSinceLastSwing = 0;
  lastSwingDirection = randDir();
  swingTime = getRandSwingTime();
}

Particle::Particle(){
  x = 0;
  y = 0;
  timeSinceLastSwing = 0;
  lastSwingDirection = randDir();
  swingTime = getRandSwingTime();
}

int Particle::getx(){
  return x;
}

int Particle::gety(){
  return y;
}

void Particle::move(){
  y++;
  x+=lastSwingDirection;
  timeSinceLastSwing++;
  if(timeSinceLastSwing>swingTime){
    lastSwingDirection *= -1;
    timeSinceLastSwing = 0;
    swingTime = getRandSwingTime();
  }
}

void Particle::respawn(int begX, int begY){
  x = begX;
  y = begY;
  timeSinceLastSwing = 0;
}