#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define C_X 0
#define C_Y 1
#define C_Z 2
#define SENSIBILITY 100.0f


//gcc test.c camera.c -o test.out -IGL -IGLU -IGLUT -lglut -lGL -lGLU -lm

typedef struct Vertex
{
    float x , y , z ;//corrdenadas do vertice
    float r , g , b ;//cor
} Vertex;



Vertex vertices [] = { 
        { -0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 0.0f } ,
        {0.0f , 0.5f , 0.0f , 0.0f , 1.0f , 0.0f } ,
        {0.5f , -0.5f , 0.0f , 0.0f , 0.0f , 1.0f }
    };

float fov_y ;

float* cam_pos;
float* cam_center;
float* cam_nv;

int old_x, old_y;

// Variaveis para posicionar a parede
float parede_x , parede_y , parede_z ; // posicao da parede
float parede_rotacao ; // rotacao da parede
float parede_largura , parede_altura , parede_espessura ; 

Camera* cam;

void display();
void moveCam(unsigned char key, int x, int y);
void moveCamSpec(int key, int x, int y);
void draw_axis();
void draw_cube();
void mouse_func(int button, int state, int x, int y);

void draw_line(float x0, float y0, float z0, float x1, float y1, float z1);

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Open GL");

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    cam = init_camera();

    parede_altura = 3.0f ; // 3m
    parede_espessura = 0.3f ; // 30 cm
    parede_largura = 4.0f ; // 4m
    parede_rotacao = 45.0f ;
    parede_x = 0.0f ;
    parede_y = 1.5f ; // metade da altura
    parede_z = 1.0f ;
    /*
    * center representa o ponto que estamos olhando ,
    * nesse caso sera o centro da parede
    */
   


    glutDisplayFunc(display);
    glutKeyboardFunc(moveCam);
    glutSpecialFunc(moveCamSpec);
    glutMouseFunc(mouse_func);
    glutMainLoop();
    return 0;
}


void moveCam(unsigned char key, int x, int y) {

    switch(key) {
        case 'w':
            moveCamFoward(cam);
            break;
        case 's':
            moveCamBackwards(cam);
            break;
        case 'a':
            moveCamLeft(cam);
            break;     
        case 'd':
            moveCamRight(cam);
            break;
        case 'z':
            turnCamBack(cam);
            break;
        case 'f':
            moveCamDown(cam);
            break;
        case 'r':
            moveCamUp(cam);
            break;        
    }
    display();
    //printf("(%.2f, %.2f, %.2f)\n", cam_pos[0], cam_pos[1], cam_pos[2]);
    

}

void moveCamSpec(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
           rotateCamUp(cam);
           break;
        case GLUT_KEY_DOWN:
            rotateCamDown(cam);
            break;

        case GLUT_KEY_LEFT:
            rotateCamLeft(cam);
            break;
        case GLUT_KEY_RIGHT:
            rotateCamRight(cam);
            break;
    }
    display();
    
    
}


void draw_axis(){
	float width = 1.5f;
	glLineWidth(width);
	glColor3f(1.0f, 0.0f, 0.0f);
	draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);	
	glColor3f(0.0f, 1.0f, 0.0f);
	draw_line(0.0f, 0.0f, 0.0f, 0.0f, 100, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	draw_line(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100);
}

void draw_line(float x0, float y0, float z0, float x1, float y1, float z1){
	glBegin(GL_LINES);
		glVertex3f(x0, y0, z0);
		glVertex3f(x1, y1, z1);
	glEnd();
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

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    

    int i ;
    Vertex v ;

    /*glBegin ( GL_TRIANGLES ) ;
    for( i = 0; i < sizeof ( vertices ) ; i ++)
    {
        v = vertices [ i ];
        glColor3f ( v .r , v .g , v . b ) ;
        glVertex3f ( v .x , v .y , v . z ) ;
    }
    glEnd () ;*/


    fov_y = 75.0f ; // 75 graus
    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity () ;
    gluPerspective ( fov_y , 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT ,
    0.001f , 1000.0f ) ;


    cam_pos = getCamPos(cam);
    cam_center = getCamCenter(cam);
    cam_nv = getCamNV(cam);

    gluLookAt( cam_pos[C_X] , cam_pos[C_Y] , cam_pos[C_Z] , cam_center[C_X] , cam_center[C_Y] ,
    cam_center[C_Z] , cam_nv[C_X] , cam_nv[C_Y] , cam_nv[C_Z] ) ;
    
    glMatrixMode ( GL_MODELVIEW ) ;
    glLoadIdentity () ;

    glPushMatrix();
    draw_axis();
    glPopMatrix();
    draw_cube();


    /*glPushMatrix();
    glLoadIdentity () ;
    glTranslatef ( parede_x , parede_y , parede_z+10.0 ) ;
    
    glScalef ( parede_largura , parede_altura , parede_espessura );
    glColor3f ( 1.0f , 0.0f , 0.0f ) ;
    glutSolidCube (1 ) ;
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity () ;
    glTranslatef ( parede_x , parede_y , parede_z ) ;
    //glRotatef ( parede_rotacao , 0.0f , 1.0f , 0.0f ) ;
    glScalef ( parede_largura , parede_altura , parede_espessura );
    glColor3f ( 1.0f , 1.0f , 0.0f ) ;
    glutSolidCube (1 ) ;
    glPopMatrix();*/

    
    
    glFlush();
    glutSwapBuffers () ;
}


void mouse_func(int button, int state, int x, int y) {
    if(state == GLUT_DOWN) {
        old_x = x;
        old_y = y;
    }
    else if(state == GLUT_UP) {
        int diff_x = old_x - x;
        int diff_y = old_y - y;
        old_x = x;
        old_y = y;
        int i;
        int quant_x = abs(diff_x/SENSIBILITY);
        int quant_y = abs(diff_y/SENSIBILITY);

        printf("%d %d\n", quant_x, quant_y);

        if(diff_x > 0) {
            for(i = 0; i < quant_x; i++) {
                rotateCamRight(cam);
            }
        }
        if(diff_x < 0) {
            for(i = 0; i < quant_x; i++) {
                rotateCamLeft(cam);
            }
        }

        if(diff_y > 0) {
            for(i = 0; i < quant_y; i++) {
                rotateCamUp(cam);
            }
        }
        if(diff_y < 0) {
            for(i = 0; i < quant_y; i++) {
                rotateCamDown(cam);
            }
        }
        display();
    }

}