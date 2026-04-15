#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "font_ttf.h"

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096);
	TTF_Init();

	SDL_Window *window = SDL_CreateWindow("Wiidia Player",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_RWops *font_rw = SDL_RWFromMem((void *)font_ttf, font_ttf_size);
	TTF_Font *font = TTF_OpenFontRW(font_rw, 1, 32);

	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface *text_surface = TTF_RenderText_Blended(font, "Hello world", white);
	SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	SDL_Rect text_rect;
	text_rect.w = text_surface->w;
	text_rect.h = text_surface->h;
	text_rect.x = (640 - text_rect.w) / 2;
	text_rect.y = (480 - text_rect.h) / 2;
	SDL_FreeSurface(text_surface);

	int running = 1;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = 0;
			if (event.type == SDL_JOYDEVICEADDED)
				SDL_JoystickOpen(event.jdevice.which);
			if (event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == 6)
				running = 0;
		}

		SDL_SetRenderDrawColor(renderer, 0, 60, 120, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(text_texture);
	TTF_CloseFont(font);
	TTF_Quit();
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
