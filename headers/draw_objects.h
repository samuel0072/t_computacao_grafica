/*
* Esse arquivo serve SOMENTE como apoio pro main.c
*/
#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

typedef struct TextureInfo TextureInfo;

/*Desenha marcações nos eixos*/
void draw_axis_ticks();

/*Desenha uma janela*/
void draw_window();

/*Desenha um objeto qualquer*/
void draw_objects(int index, float r, float g, float b);

/*Desenha uma linha*/
void draw_line(float x0, float y0, float z0, float x1, float y1, float z1);

/*Desenha os eixos x, y, z*/
void draw_axis();

/*Desenha um cubo*/
void draw_cube();

/*Desenha o ventilador girando*/
void draw_helix();

void draw_door();

void change_door_state();

void change_window_state();
#endif