#include "SDL_video.h"
#include "SDL_render.h"
#include "mandelbrot.hpp"

class gfx {
	public:
		gfx(fractal*);
		~gfx();
		int init(int winWidth, int winHeight);
		bool running();
		void update();
		void render();
		void renderDouble();
		void handleEvents();
		static SDL_Renderer *renderer;

	private:
		SDL_Window *window;
		fractal *fractals;
		bool isRunning;
		int width, height;
		unsigned long int cnt;
};
