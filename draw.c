#include "main.h"

void	put_pixel(int x, int y, int color, unsigned *surface)
{
	int index;

	index = (y * WIN_WIDTH + x);
	if (0 <= index && index < WIN_WIDTH * WIN_HEIGHT)
		surface[index] = color;
}

uint32_t	get_pixel(int x, int y, SDL_Surface *tex)
{
	uint32_t	*sprite;
	uint32_t	pixel;
	uint32_t	size;

	sprite = (uint32_t*)tex->pixels;
	pixel = tex->w * y + x;
	size = tex->w * tex->h;
	if ((pixel < size))
		return(sprite[pixel]);
	else
		return (0);
}
