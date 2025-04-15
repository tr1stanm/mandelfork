#include "mandelbrot.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>
#include <cmath>

fractal::fractal() {
	firstDivergent = -1;	
}

int fractal::mandelbrot(std::complex<double>& z, std::complex<double> c, int maxIter) {
	//can be used to output one frame if there aren't preceding ones
	
	int iter = 0;

	while(iter < maxIter) {
		z = z*z + c;
		if(abs(z) > 2) break;
		++iter;
	}
	return iter;
}

void fractal::mandelframe(pixel& pix, int currentIter) {
	if(!pix.divergent) {
		pix.z = pix.z*pix.z + pix.c;
		if(abs(pix.z) > 2) {
			pix.divergent = true;
			pix.howDivergent = currentIter;
			if(firstDivergent < 0) firstDivergent = currentIter;
			return;
		}
	}
}

void fractal::mandel_init(int width, int height, double scale) {
	xshift = -0.15431199967861176;
	yshift = -1.0386210766520199;

//	xshift = -0.4465643538242148;
//	yshift = 1.5702929400993941;
	
	imgwidth = width;
	imgheight = height;
	int imgratio = width/height;	//necessary?
	quadwidth = imgwidth/2;		// "	"
	quadheight = imgheight/2;	// "	"

	std::cout << "creating initial pixel map..." << std::flush;
	mandelmap = new pixel*[imgwidth];
	for(int i = 0; i < imgwidth; ++i) mandelmap[i] = new pixel[imgheight];
	for(int i = 0; i < imgheight; ++i) {
		for(int j = 0; j < imgwidth; ++j) {
			mandelmap[j][i].z = 0;
			mandelmap[j][i].divergent = false;
			mandelmap[j][i].howDivergent = 0;
			markconvergent(mandelmap[j][i]);
			mandelmap[j][i].c = std::complex<double> 
				(((-quadwidth+j)/(imgwidth*scale/4))+xshift, 
				((quadheight-i)/(imgheight*scale/4))+yshift);
		}
	}
	std::cout << "done." << std::endl;
	
}

void fractal::createbrot(int iter) {
	int w = 0;
	int h = 0;
	
	for(double j = quadheight; j > -quadheight; --j) {
		for(double i = -quadwidth; i < quadwidth; ++i) {
			mandelframe(mandelmap[w][h], iter);
			if(mandelmap[w][h].howDivergent) markdivergent(mandelmap[w][h]);
			++w;
		}
		w = 0;
		++h;
	}
}

void fractal::markconvergent(pixel& pix) {
	pix.red = 0;
	pix.green = 0;
	pix.blue = 0;
}

void fractal::markdivergent(pixel& pix) {
	pix.red = pix.howDivergent*1.5;
	pix.green = pix.howDivergent*0.3;
	pix.blue = pix.howDivergent*7.2;
	// maybe rename this function to reflect what it's
	// actually doing
}

fractal::~fractal() {
	for(int i = 0; i < imgwidth; ++i) delete[] mandelmap[i];
	delete[] mandelmap;
}
