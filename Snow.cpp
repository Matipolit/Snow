#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "Particle.h"

#define DELAY 30000
int snowflakeAmount = 300;
int maxX = 0, maxY = 0;

void initParticles(std::vector<Particle>* particles){
	for(int i = 0; i < snowflakeAmount; i++){
		particles->push_back(Particle(rand() % maxX, rand() % maxY));
	}
}

void printParticles(std::vector<Particle>* particles){
	for(int i = 0; i < snowflakeAmount; i++){
		mvprintw(particles->at(i).gety(), particles->at(i).getx(), "*");
	}
}

void updatePositionsAndRespawnStale(std::vector<Particle>* particles){
	for(int i = 0; i < snowflakeAmount ; i++){
		particles->at(i).move();
		if(particles->at(i).gety()>maxY){
			particles->at(i).respawn(rand() % maxX) ;
		}
	}
}

int main(int argc, char** argv){
	// init random seed
	srand (time(NULL));
	// custom snowflake amount in command line arguments
	if(argc == 2){
		snowflakeAmount = atoi(argv[1]);
	}
	
	std::vector<Particle> particles;

	initscr();
	noecho();
	curs_set(false);

	getmaxyx(stdscr, maxY, maxX);

	initParticles(&particles);
	clear();
	printParticles(&particles);	
	refresh();

	while(true){
		clear();
		printParticles(&particles);
		refresh();
		updatePositionsAndRespawnStale(&particles);
		usleep(DELAY);
	}

	endwin();
	return 0;
}