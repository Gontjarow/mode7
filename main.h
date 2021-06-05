#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define MID_WIDTH (WIN_WIDTH / 2)
#define MID_HEIGHT (WIN_HEIGHT / 2)

SDL_Window	*new_window(const char *title, int width, int height);
void	clear_surface(SDL_Surface *surface);

void	handle_events(int *running);
void	render_frame();

uint32_t	get_pixel(int x, int y, SDL_Surface *tex);
void		put_pixel(int x, int y, int color, unsigned *surface);

#endif