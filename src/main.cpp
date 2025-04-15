#include "mandelbrot.hpp"
#include "gfx.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <ostream>

int main(int argc, char **argv) {
	fractal fractals;
	gfx gfx(&fractals);
	int frameAmt, width, height;
	double scale = 1;
	char response;
	frameAmt = 100;

	std::cout << "How many pixels wide should the canvas be? ";
	std::cin >> width;
	std::cin.ignore();
	std::cout << "How many pixels high should the canvas be? ";
	std::cin >> height;
	std::cin.ignore();
	std::cout << "What scale should the zoom be? (default is 1) ";
	std::cin >> scale;
	std::cin.ignore();
	
	fractals.mandel_init(width, height, scale);
	gfx.init(width, height);
	while(gfx.running()) {		
		gfx.handleEvents();
		gfx.render();
		gfx.update();
	}

	std::cout << "\nFirst frame with divergence at this scale: " << fractals.firstDivergent << std::endl;

/*
	std::cout << "\nExport frames to folder? (y/n) ";
	std::cin >> response;
	std::cin.ignore();
	if(response == 'y' || response == 'Y') {
		std::cout << "How many frames? ";
		std::cin >> frameAmt;
		std::cin.ignore();
		fractals.exportAnim(frameAmt, width, height, scale);
	}
*/

	std::cout << "Quitting program..." << std::endl;

	return 0;
}
