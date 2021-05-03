/*
* Esse arquivo serve SOMENTE como apoio pro main.c
*/
#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H



/*Variáveis inicializadas no draw_objects.c*/
extern int ROT_WINDOW;
extern float ROT_W_ANGLE;//angulo de rotação da janela em graus
extern int ROT_W_DIR;//Direção de rotação da janela:horário, antihorário

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


#endif