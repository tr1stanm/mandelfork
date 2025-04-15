#include "gfx.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <ostream>

SDL_Renderer *gfx::renderer = nullptr;

gfx::gfx(fractal *fractal) {
	isRunning = false;
	fractals = fractal;
	cnt = 0;
	//include some error checking in here that mandel_init has been run
	//or just run it from here maybe
}

int gfx::init(int winWidth, int winHeight) {
	width = winWidth;
	height = winHeight;
	window = SDL_CreateWindow("mandel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(window) renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer) {
		std::cout << "subsystems initialized.\n";
		isRunning = true;
	}
	else isRunning = false;
	return isRunning;
}

void gfx::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void gfx::render() {
	SDL_RenderClear(renderer);

	//put mandelbrot rendering stuff in here
	//drawpixel using mandelmap
	for(int j = 0; j < height; ++j) { 
		for(int i = 0; i < width; ++i) {
			SDL_SetRenderDrawColor(renderer, fractals->mandelmap[i][j].red,
							 fractals->mandelmap[i][j].green,
							 fractals->mandelmap[i][j].blue, 255);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}
	SDL_RenderPresent(renderer);
}

void gfx::renderDouble() {	//doesn't do anything yet other than make the image look like shit
	for(int j = 0; j < height/2; ++j) { 
		for(int i = 0; i < width/2; ++i) {
			SDL_SetRenderDrawColor(renderer, fractals->mandelmap[i][j].red,
							 fractals->mandelmap[i][j].green,
							 fractals->mandelmap[i][j].blue, 255);
			SDL_RenderDrawPoint(renderer, 2*i, 2*j);
			SDL_RenderDrawPoint(renderer, (2*i)-1, 2*j);
			SDL_RenderDrawPoint(renderer, 2*i, (2*j)-1);
			SDL_RenderDrawPoint(renderer, (2*i)-1, (2*j)-1);
		}
	}
	SDL_RenderPresent(renderer);
}

void gfx::update() {
	//invoke createbrot
	std::cout << "\riterations: " << cnt << std::flush;
	++cnt;
	fractals->createbrot(cnt);
}

bool gfx::running() {
	return isRunning;
}

gfx::~gfx() {}
