#include <SDL2/SDL_video.h>
#include <complex>
#include <cstdlib>
#include<fstream>
#pragma once


struct pixel {
	char red;
	char green;
	char blue;
	bool divergent;		//sets to true if the pixel has been deemed div.
	int howDivergent;
	std::complex<double> z;
	std::complex<double> c;
};

class fractal {
	public:
		fractal();
		~fractal();
		
		void mandel_init(int, int, double); //passes in the size of the canvas
		void createbrot(int);
		
		void fileopen(int = 0);
		void fileclose(int = 0);
		void output();
		void exportAnim(int, int, int, double);

		int imgwidth, imgheight, quadwidth, quadheight, firstDivergent;
		pixel **mandelmap;
		std::ofstream fileout;
	private:
		double xshift, yshift;

		int mandelbrot(std::complex<double>&, std::complex<double>, int);
		void mandelframe(pixel&, int);
		void markconvergent(pixel&);
		void markdivergent(pixel&);
};
