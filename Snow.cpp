#include <csignal>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "Particle.h"

#define DELAY 30000
int snowflakeAmount = 300;
int maxX = 0, maxY = 0;
std::vector<Particle> particles;

void initParticles(){
	for(int i = 0; i < snowflakeAmount; i++){
		particles.push_back(Particle(rand() % maxX, rand() % maxY));
	}
}

void randomizeHeight(){
	for(int i = 0; i < snowflakeAmount; i++){
		int x = particles.at(i).getx();
		particles.at(i).respawn(x, rand() % maxY);
	}
}

void printParticles(){
	for(int i = 0; i < snowflakeAmount; i++){
		mvprintw(particles.at(i).gety(), particles.at(i).getx(), "*");
	}
}

void updatePositionsAndRespawnStale(){
	for(int i = 0; i < snowflakeAmount ; i++){
		particles.at(i).move();
		if(particles.at(i).gety()>maxY){
			particles.at(i).respawn(rand() % maxX, 0) ;
		}
	}
}

void do_resize(int signal){
	endwin();
	refresh();
	getmaxyx(stdscr, maxY, maxX);
	randomizeHeight();
}

int main(int argc, char** argv){
	// init random seed
	srand (time(NULL));
	// custom snowflake amount in command line arguments
	if(argc == 2){
		snowflakeAmount = atoi(argv[1]);
	}
	

	initscr();
	noecho();
	curs_set(false);

	getmaxyx(stdscr, maxY, maxX);

	initParticles();
	clear();
	printParticles();	
	refresh();
	std::signal(SIGWINCH, do_resize);
	
	while(true){
		clear();
		printParticles();
		refresh();
		updatePositionsAndRespawnStale();
		usleep(DELAY);
	}

	endwin();
	return 0;
}