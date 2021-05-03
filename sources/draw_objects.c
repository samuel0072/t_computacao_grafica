#include "../headers/draw_objects.h"
#include "../headers/obj_import.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

int ROT_WINDOW = 0;//flag para girar a janela
float ROT_W_ANGLE = 0;//angulo de rotação da janela em graus
int ROT_W_DIR = 1;//Direção de rotação da janela:horário, antihorário
int HEX_ANGLE = 0;

void draw_axis(){
	float width = 1.5f;
	glLineWidth(width);
	glColor3f(1.0f, 0.0f, 0.0f);
	draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);	
    glColor3f(1.0f, 0.0f, 0.0f);
	draw_line(0.0f, 0.0f, 0.0f, -100, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	draw_line(0.0f, 0.0f, 0.0f, 0.0f, 100, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
	draw_line(0.0f, 0.0f, 0.0f, 0.0f, -100, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	draw_line(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100);
    glColor3f(0.0f, 0.0f, 1.0f);
	draw_line(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100);
}

void draw_line(float x0, float y0, float z0, float x1, float y1, float z1){
	glBegin(GL_LINES);
		glVertex3f(x0, y0, z0);
		glVertex3f(x1, y1, z1);
	glEnd();
}

void draw_axis_ticks() {
    
    int colors[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    
    float i;
    glColor3f(0.0f, 0.0f, 1.0f);
    for(i = -99; i < 100; i++) {
        glBegin(GL_LINES);
            glVertex3f(i, 0.0f,100.0f);
            glVertex3f(i,0.0f,-100.0f);
	    glEnd();
    }
    glColor3f(0.0f, 1.0f, 0.0f);
    for(i = -99; i < 100; i++) {
        glBegin(GL_LINES);
            glVertex3f(-100.0f, i,0.0f);
            glVertex3f(100.0f,i,0.0f);
	    glEnd();
    }
    glColor3f(0.0f, 0.0f, 1.0f);
    for(i = -99; i < 100; i++) {
        glBegin(GL_LINES);
            glVertex3f(-100.0f, 0.0f,i);
            glVertex3f(100.0f,0.0f,i);
	    glEnd();
    }
}


void draw_window() {
    
    //glTranslatef ( -46.5 , 41.2 , -75 ) ;
    if(ROT_WINDOW) {
        ROT_W_ANGLE += ROT_W_DIR;
        
        
        if(ROT_W_ANGLE == 90 || ROT_W_ANGLE == 0) {
            //para de girar a janela
            ROT_WINDOW = 0;
            ROT_W_DIR *= (-1);
        }
        glTranslatef ( -1.5, 1.5 , 0) ;
        
    }
    glRotatef(ROT_W_ANGLE, 0, 1, 0);
    
    //glScalef(15.0,12.0,5.0);
    draw_objects(3, 1, 1, 0);
}

void draw_cube() {
    glBegin(GL_QUADS);
        glColor3f (0.5 , 0.5 , 0.5 ) ;
		glVertex3f(0, 1, 1);
        glVertex3f(2, 1, 1);
        glVertex3f(2, 1, 2);
		glVertex3f(0, 1, 2);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f (0 , 1 , 0.5 ) ;
		glVertex3f(0, 3, 2);
        glVertex3f(0, 3, 1);
        glVertex3f(2, 3, 1);
		glVertex3f(2, 3, 2);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f (0 , 0.4 , 0 ) ;
		glVertex3f(0, 1, 1);
        glVertex3f(0, 1, 2);
        glVertex3f(0, 3, 2);
		glVertex3f(0, 3, 1);
    glEnd();


    glBegin(GL_QUADS);
        glColor3f (0 , 0.4 , 0 ) ;
		glVertex3f(0, 3, 2);
        glVertex3f(2, 3, 2);
        glVertex3f(2, 1, 2);
		glVertex3f(0, 1, 2);
    glEnd();



//outro
    glBegin(GL_QUADS);
        glColor3f (1 , 1 , 1 ) ;
		glVertex3f(0, 1, 4);
        glVertex3f(2, 1, 4);
        glVertex3f(2, 1, 6);
		glVertex3f(0, 1, 6);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f (1 , 1 , 1 ) ;
		glVertex3f(0, 3, 6);
        glVertex3f(0, 3, 4);
        glVertex3f(2, 3, 4);
		glVertex3f(2, 3, 6);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f (1 , 1 , 1 ) ;
		glVertex3f(0, 1, 4);
        glVertex3f(0, 1, 6);
        glVertex3f(0, 3, 6);
		glVertex3f(0, 3, 4);
    glEnd();


    glBegin(GL_QUADS);
        glColor3f (1 , 1 , 1 ) ;
		glVertex3f(0, 3, 6);
        glVertex3f(2, 3, 6);
        glVertex3f(2, 1, 6);
		glVertex3f(0, 1, 6);
    glEnd();
}

void draw_helix() {
    //glScalef(5.0,5.0,5.0);
    draw_objects(8, 0.8, 0.8, 0);
    glTranslatef(0, 1.7, 0);
    glScalef(0.75,0.75,0.75);
    glRotatef(90, 1, 0, 0);

    HEX_ANGLE += 1;
    HEX_ANGLE %= 360;
    glRotatef(HEX_ANGLE, 0, 1, 0);//Gira no Y pq  ventilador original ta no plano XZ e não no XY

    draw_objects(7, 0.5, 0, 0);
    
    
}

void draw_objects(int index, float r, float g, float b) {
    if(0 <= index < MODEL_QUANT) {
        int i;
       
        VERTICES = vecs[index]->VERTICES;
        NORMALS = vecs[index]->NORMALS ;
        TEX_COORDS = vecs[index]->TEX_COORDS;
        VERTEX_COUNT = vecs[index]->VERTEX_COUNT;

        glBegin(GL_TRIANGLES);
	    for(i = 0;i < VERTEX_COUNT;i++){
            glColor3f (r , g , b ) ;
            glNormal3f(NORMALS[i].x, NORMALS[i].y, NORMALS[i].z);
            glTexCoord2f(TEX_COORDS[i].x, TEX_COORDS[i].y);
            glVertex3f(VERTICES[i].x, VERTICES[i].y, VERTICES[i].z);
	    }
	    glEnd();
        
    }
    else {
        printf("Indice fora do range permitido: [0, %d)", MODEL_QUANT);
        exit(1);
    }
}


