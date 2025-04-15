#include "mandelbrot.hpp"
#include <iostream>

void fractal::exportAnim(int frameAmt, int width, int height, double scale) {
	system("mkdir mandelbrot_anim");

	mandel_init(width, height, scale);

	for(int i = 1; i <= frameAmt; ++i) {
		fileopen(i);
		createbrot(i);
		output();
		fileclose(i);
		std::cout << "\r";
		printf("%.2f", 100*(float)i/frameAmt);
		std::cout << "\% done." << std::flush;
	}
	std::cout << '\r' << std::flush;
	std::cout << "\r100\% done.    " << std::flush;
	std::cout << '\n';
}

void fractal::fileopen(int framenum) {
	std::stringstream framename;
	if(framenum) framename << "./mandelbrot_anim/mandelbrot_" << framenum << ".ppm";
	else framename << "./mandelbrot.ppm";
	fileout.open(framename.str());
	if(!framenum && fileout) std::cout << "file created." << std::endl;
}

void fractal::fileclose(int framenum) {
	fileout.close();
	if(!framenum) {
		std::cout << "converting to .png..." << std::flush;
		system("magick mandelbrot.ppm mandelbrot.png");
		std::cout << "done." << std::endl;
		return;
	}
	std::stringstream filename;
	std::stringstream syscall;
	syscall << "magick ./mandelbrot_anim/mandelbrot_" <<\
		   framenum << ".ppm mandelbrot_anim/mandelbrot_" <<\
		   framenum << ".png";
	system(syscall.str().c_str());
	syscall.str("");
	syscall << "rm ./mandelbrot_anim/mandelbrot_" <<\
		   framenum << ".ppm";
	system(syscall.str().c_str());
}
		   
void fractal::output() {
	fileout << "P6" << std::endl;
	fileout << imgwidth << " " << imgheight << std::endl;
	fileout << "255" << std::endl;
	//std::cout << "writing to file..." << std::flush;
	for(int i = 0; i < imgheight; ++i) {
		for(int j = 0; j < imgwidth; ++j) {
			fileout << mandelmap[j][i].red;
			fileout << mandelmap[j][i].green;
			fileout << mandelmap[j][i].blue;
		}
	}
}
