/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

//custom global variables
SDL_FRect rect;
const float gravity = 0.5;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    rect.x = 50;
    rect.y = 550;
    rect.w = rect.h = 50;

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer("project", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.key == SDLK_ESCAPE){
            SDL_Log("ESCAPE KEY PRESSED");
            return SDL_APP_SUCCESS;
        }

        if(event->key.key == SDLK_SPACE){
            SDL_Log("SPACE BAR PRESSED");
            rect.y = rect.y - 50;
        }

        if(event->key.key == SDLK_D){
            SDL_Log("D KEY PRESSED");
            rect.x = rect.x + 10;
        }

        if(event->key.key == SDLK_A){
            SDL_Log("A KEY PRESSED");
            rect.x = rect.x - 10;
        }
    }

    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}
