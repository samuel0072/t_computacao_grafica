#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "headers/camera.h"
#include "headers/obj_import.h"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

#define MODEL_QUANT 10

#define PI 3.14
#define RAD_TO_GRAD(c) c*180/PI

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

typedef struct Vecs Vecs;

struct Vecs {
    Vec3 *VERTICES;
    Vec3 *NORMALS;
    Vec2 *TEX_COORDS;
    int VERTEX_COUNT;
};

float* cam_pos;
float* cam_center;
float* cam_nv;

int old_x = 0, old_y = 0;


Camera* cam;
Vecs** vecs;

int ROT_WINDOW = 0;//flag para girar a janela
float ROT_W_ANGLE = 0;//angulo de rotação da janela em graus
int ROT_W_DIR = 1;//Direção de rotação da janela:horário, antihorário


void display();

void moveCam(unsigned char key, int x, int y);
void moveCamSpec(int key, int x, int y);
void mouse_func( int x, int y);
void pass_mouse_func(int x, int y);

void load_obj_display(const char* path, int index);
void init_obj_vecs();

void draw_axis_ticks();
void draw_window();
void draw_objects(int index, float r, float g, float b);
void draw_line(float x0, float y0, float z0, float x1, float y1, float z1);
void draw_axis();
void draw_cube();

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
    /*
    * center representa o ponto que estamos olhando ,
    * nesse caso sera o centro da parede
    */

    /*init_vecs();

    load_obj("./models/casa.obj");*/

    init_obj_vecs();
    /*load_obj_display("./models/casa.obj", 0);
    load_obj_display("./models/cama.obj", 1);
    load_obj_display("./models/caneca.obj", 2);*/
    load_obj_display("./models/janela.obj", 3);
    //load_obj_display("./models/mesa.obj", 4);


    glutDisplayFunc(display);
    glutKeyboardFunc(moveCam);
    glutSpecialFunc(moveCamSpec);
    glutMotionFunc(mouse_func);
    glutPassiveMotionFunc(pass_mouse_func); 
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
        case '/':
            resetOrgDir(cam);
            break;  
        case 'g':
            ROT_WINDOW = 1;
            break;
    }
    glutPostRedisplay();
    

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
    glutPostRedisplay();
    
    
}

void mouse_func( int x, int y) {
    int diff_x = old_x - x;
    int diff_y = old_y - y;
    old_x = x;
    old_y = y;
    int i;

    if(diff_x > 0) {
        rotateCamRight(cam);
    }
    if(diff_x < 0) {
        rotateCamLeft(cam);
    }

    if(diff_y > 0) {
        rotateCamUp(cam);
    }
    if(diff_y < 0) {
        rotateCamDown(cam);
    }
    glutPostRedisplay();
}

void pass_mouse_func(int x, int y) {
    old_x = x;
    old_y = y;
}
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

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    

    int i ;


    glMatrixMode ( GL_PROJECTION ) ;
    glLoadIdentity () ;
    gluPerspective ( FOV , 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT ,
    0.001f , 1000.0f ) ;


    cam_pos = getCamPos(cam);
    cam_center = getCamCenter(cam);
    cam_nv = getCamNV(cam);

    gluLookAt( cam_pos[X] , cam_pos[Y] , cam_pos[Z] , cam_center[X] , cam_center[Y] ,
    cam_center[Z] , cam_nv[X] , cam_nv[Y] , cam_nv[Z] ) ;
    
    glMatrixMode ( GL_MODELVIEW ) ;
    glLoadIdentity () ;

    
    D(
        glPushMatrix();
        draw_axis();
        glPopMatrix();

        glPushMatrix();
        draw_axis_ticks();
        glPopMatrix();)
    //glPushMatrix();
    //draw_cube();
    //glPopMatrix();
    //glColor3f (0.5 , 0.5 , 0.5 ) ;
    //glTranslatef ( 0 , 0 , 0 ) ;


    glPushMatrix();

    
    
    //glRotatef ( 180 , 1.0f , 0.0f , 0.0f ) ;
    /*glTranslatef ( 0 , -10 , 0 ) ;
    draw_objects(0, 0.5, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glScalef(5.0,5.0,5.0);
    draw_objects(1, 1, 0, 0);
    glPopMatrix();

    glPushMatrix();
    draw_objects(2, 0, 1, 0);
    glPopMatrix();*/

    glPushMatrix();
    draw_window();
    glPopMatrix();

    /*glPushMatrix();
    //glRotatef ( 180 , 1.0f , 0.0f , 0.0f ) ;
    draw_objects(3, 0.5, 0.5, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef ( 0 , 10 , 0 ) ;
    //glRotatef ( 180 , 1.0f , 0.0f , 0.0f ) ;
    draw_objects(4, 0.5, 0.5, 0.5);
    glPopMatrix();*/

    




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
    
    glScalef ( parede_largura , parede_altura , parede_espessura );
    glColor3f ( 1.0f , 1.0f , 0.0f ) ;
    glutSolidCube (1 ) ;
    glPopMatrix();*/

    
    
    glFlush();
    glutSwapBuffers () ;
    glutPostRedisplay();
}

void load_obj_display(const char* path, int index) {
    int i;

    if(0 <= index < MODEL_QUANT) {
        init_vecs();
        load_obj(path);
        vecs[index]->VERTICES = VERTICES;
        vecs[index]->NORMALS = NORMALS;
        vecs[index]->TEX_COORDS = TEX_COORDS;
        vecs[index]->VERTEX_COUNT = VERTEX_COUNT;
        
    }
    else {
        printf("Indice fora do range permitido: (0, %d)", MODEL_QUANT);
        exit(1);
    }

    
    
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

void init_obj_vecs() {
    int i;
    vecs = (Vecs**)malloc(MODEL_QUANT*sizeof(Vecs*));
    for(i = 0; i < MODEL_QUANT; i++) {
        vecs[i] = (Vecs*)malloc(sizeof(Vecs));
    }
}