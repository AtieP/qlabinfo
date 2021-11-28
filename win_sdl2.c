#include "qlabinfo.h"

#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static SDL_Window *current_window = NULL;
static SDL_Renderer *current_renderer = NULL;
static SDL_TimerID current_timer_id = 0;

static int event_handler(void *userdata, SDL_Event *event)
{
	(void) userdata;
	if (event->type == SDL_QUIT)
		exit(0);

	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_C)
			win_key_event(KEY_C);
		else if (event->key.keysym.scancode == SDL_SCANCODE_D)
			win_key_event(KEY_D);
		else if (event->key.keysym.scancode == SDL_SCANCODE_H)
			win_key_event(KEY_H);
		else if (event->key.keysym.scancode == SDL_SCANCODE_L)
			win_key_event(KEY_L);
		else if (event->key.keysym.scancode == SDL_SCANCODE_U)
			win_key_event(KEY_U);
		else if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
			win_key_event(KEY_ARROW_LEFT);
		else if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
			win_key_event(KEY_ARROW_RIGHT);
		else if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			win_key_event(KEY_ESC);
	}

	return 0; /* ignored */
}

int win_init(int width, int height, int fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		qprint(LOG_ERROR, "sdl2: Could not initialize");
		return -1;
	}

	current_window = SDL_CreateWindow("QLabInfo",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
	if (current_window == NULL)
	{
		qprint(LOG_ERROR, "sdl2: Could not create window");
		return -1;
	}

	/* request rendering driver information */
	SDL_RendererInfo renderer_info;
	if (SDL_GetRenderDriverInfo(0, &renderer_info) != 0)
	{
		qprint(LOG_ERROR, "sdl2: Could not query video driver "
					"information");
		return -1;
	}

	int flags;
	if (renderer_info.flags & SDL_RENDERER_ACCELERATED)
		flags |= SDL_RENDERER_ACCELERATED;
	else if (renderer_info.flags & SDL_RENDERER_SOFTWARE)
		flags |= SDL_RENDERER_SOFTWARE;
	else
	{
		qprint(LOG_ERROR, "sdl2: Video driver does not support "
					"any rendering?");
		return -1;
	}

	if (!(renderer_info.flags & SDL_RENDERER_TARGETTEXTURE))
	{
		qprint(LOG_ERROR, "sdl2: Video driver does not support "
					"rendering to textures");
		return -1;
	}
	flags |= SDL_RENDERER_TARGETTEXTURE;

	if (renderer_info.flags & SDL_RENDERER_PRESENTVSYNC)
		flags |= SDL_RENDERER_PRESENTVSYNC;

	current_renderer = SDL_CreateRenderer(current_window, 0, flags);
	if (current_renderer == NULL)
	{
		qprint(LOG_ERROR, "sdl2: Could not create renderer");
		return -1;
	}

	/* events */
	SDL_EventState(SDL_QUIT, SDL_ENABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_AddEventWatch(event_handler, NULL);

	return 0;
}

int win_msgbox(enum LogLevels level, const char *title, const char *str)
{
	int sdl_level;
	switch (level)
	{
		case LOG_WARN:
			sdl_level = SDL_MESSAGEBOX_WARNING; break;
		case LOG_ERROR:
			sdl_level = SDL_MESSAGEBOX_ERROR; break;
		default:
			sdl_level = SDL_MESSAGEBOX_INFORMATION; break;
	}

	if (SDL_ShowSimpleMessageBox(sdl_level, title, str,
			NULL) != 0)
		return -1;
	else
		return 0;
}

int win_image_flush(void *buf, size_t len)
{
	int ret = 0;
	SDL_RWops *image_ops = NULL; SDL_Texture *image_texture = NULL;

	image_ops = SDL_RWFromConstMem(buf, len);
	if (image_ops == NULL)
	{
		ret = -1; goto cleanup;
	}

	image_texture = IMG_LoadTexture_RW(current_renderer, image_ops, 0);
	if (image_texture == NULL)
	{
		ret = -1; goto cleanup;
	}

	if (SDL_RenderClear(current_renderer) != 0)
		goto cleanup;

	if (SDL_RenderCopy(current_renderer, image_texture, NULL, NULL) != 0)
		goto cleanup;

	SDL_RenderPresent(current_renderer);

cleanup:
	if (image_texture != NULL)
		SDL_DestroyTexture(image_texture);
	if (image_ops != NULL)
		SDL_RWclose(image_ops);

	return ret;
}

int win_deinit()
{
	if (current_renderer != NULL)
		SDL_DestroyRenderer(current_renderer);

	if (current_window != NULL)
		SDL_DestroyWindow(current_window);

	SDL_Quit();
	return 0;
}

void win_detach_main_flow()
{
	for (;;) SDL_WaitEvent(NULL);
}

