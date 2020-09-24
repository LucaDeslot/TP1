#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "fonctions_SDL.h"

int main()
{

    SDL_Window* fenetre; //Declaration de la fenetre
    SDL_Event evenement; //evenements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO < 0)) {
    printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;


    }

    // Création de la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,600,SDL_WINDOW_RESIZABLE);
    if (fenetre == NULL){
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    //Charger l'image
    SDL_Texture* fond = charger_image( "fond.bmp", ecran );

    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* obj = charger_image_transparente("obj.bmp", ecran,r,g,b);
    SDL_Rect SrcR;

    int w;
    int h;
    SDL_QueryTexture(obj, NULL, NULL, &w, &h);

    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = w; // Largeur de l’objet en pixels (à récupérer)
    SrcR.h = h; // Hauteur de l’objet en pixels (à récupérer)

    SDL_Rect DestR;
    DestR.x = 350;
    DestR.y = 350;
    DestR.w = w/3;
    DestR.h = h/3;

    SDL_Texture* sprites = charger_image_transparente("sprites.bmp",ecran,0,255,255);
    SDL_Rect SrcR_sprite[6];
    int sw;
    int sh;
    int x = 0;
    int y = 0;
    SDL_QueryTexture(sprites, NULL, NULL, &sw, &sh);
    sw = sw/3;
    sh = sh/2;
    for (int i = 0; i < 6; i++) {
        if (i == 3) {
            y = sh;
            x = 0;
        }
        SrcR_sprite[i].x = x;
        SrcR_sprite[i].y = y;
        x += sw;
        SrcR_sprite[i].w = sw;
        SrcR_sprite[i].h = sh;
    }
    
    SDL_Rect DestR_sprite[6];
    for(int i=0; i<6; i++)
    {
        DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
        DestR_sprite[i].y = i > 2 ? 60 : 120;
        DestR_sprite[i].w = sw; //Largeur du sprite
        DestR_sprite[i].h = sh; // Hauteur du sprite
    }

    TTF_Init();
    int texteW;
    int texteH;
    TTF_Font *font = TTF_OpenFont("./arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char msg[] = "TP sur Makefile et SDL";
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    SDL_QueryTexture(texte, NULL, NULL, &texteW, &texteH);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = texteW;
    text_pos.h = texteH;

    //boucle principale
    while(!terminer) {

            SDL_RenderClear(ecran);
            SDL_RenderCopy(ecran,fond,NULL,NULL);
            SDL_RenderCopy(ecran, obj, &SrcR, &DestR);
            SDL_RenderCopy(ecran,texte,NULL,&text_pos);
            for (int i = 0; i < 6 ; i++) {
                SDL_RenderCopy(ecran, sprites, &SrcR_sprite[i], &DestR_sprite[i]);
            }

        while(SDL_PollEvent(&evenement)){


            switch(evenement.type) {

            case SDL_QUIT:
                terminer =true;
                break;

            case SDL_KEYDOWN:
                switch(evenement.key.keysym.sym){
                case SDLK_ESCAPE:
                case SDLK_q:
                    terminer = true;
                    break;

                }

            }


        }

        SDL_RenderPresent(ecran);
    }

    // Libération de l’écran (renderer)
    TTF_CloseFont( font );
    TTF_Quit();
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;
}

