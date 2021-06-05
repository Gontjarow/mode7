#include "main.h"

SDL_Window *g_window;
SDL_Surface *g_surface;
SDL_Surface *g_texture;

signed	main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL: %s\n", SDL_GetError());
		return 1;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		printf("IMG: %s\n", IMG_GetError());
		return 1;
	}

	g_window = new_window("Render Test", WIN_WIDTH, WIN_HEIGHT);
	g_surface = SDL_GetWindowSurface(g_window);
	g_texture = IMG_Load("border.png");

	int running = 1;
	while (running)
	{
		handle_events(&running);

		clear_surface(g_surface);
		render_frame();

		SDL_UpdateWindowSurface(g_window);
		SDL_Delay(1000 / 60); // 60 FPS, but not dynamic.
	}

	printf("return (0)\n");
	return (0);
}

// ===================
// Program closes with the window or by ESC
// ===================

void	render_frame()
{
	double	Tx = 0;
	double	Ty = 0;
	double	z = 0;

	for (int y = MID_HEIGHT; y < WIN_HEIGHT; y++, z++)
	{
		Ty = y / z;
		if (Ty < 0) Ty *= -1;
		Ty *= 32;
		Ty = fmod(Ty, g_texture->h);

		for (int x = 0; x < WIN_WIDTH; x++)
		{
			Tx = (MID_WIDTH - x) / z;
			if (Tx < 0) Tx *= -1;
			Tx *= 32;
			Tx = fmod(Tx, g_texture->w);

			put_pixel(x, y, get_pixel(Tx, Ty, g_texture), g_surface->pixels);
		}
	}
}

void	handle_events(int *running)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			SDL_Scancode key = event.key.keysym.scancode;
			if (key == SDL_SCANCODE_ESCAPE)
			{
				printf("ESCAPE\n");
				*running = 0;
			}
		}
		else if ((event.type == SDL_QUIT) || (event.type == SDL_WINDOWEVENT_CLOSE))
		{
			printf("SDL_QUIT\n");
			*running = 0;
		}
	}
}

SDL_Window	*new_window(const char *title, int width, int height)
{
	return (SDL_CreateWindow(title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0));
}

void	clear_surface(SDL_Surface *surface)
{
	// https://wiki.libsdl.org/SDL_Surface
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, 0, surface->h * surface->pitch);
	SDL_UnlockSurface(surface);
}
