#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>


#include "headers/camera.h"
#include "headers/obj_import.h"
#include "headers/cam_movement.h"
#include "headers/draw_objects.h"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif



float* cam_pos;
float* cam_center;
float* cam_nv;

void* cam = NULL;




void display();


int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Open GL");

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    
    /*
    * center representa o ponto que estamos olhando ,
    * nesse caso sera o centro da parede
    */

    /*init_vecs();

    load_obj("./models/casa.obj");*/
    cam = (Camera*)init_camera();
    init_obj_vecs();
    load_obj_display("./models/cadeira.obj", 0);
    load_obj_display("./models/cama.obj", 1);
    load_obj_display("./models/caneca.obj", 2);
    load_obj_display("./models/janela.obj", 3);
    load_obj_display("./models/basquete.obj", 4);
    load_obj_display("./models/estanteDeLivros.obj", 5);
    load_obj_display("./models/sofa.obj", 6);
    load_obj_display("./models/ventilador/helice.obj", 7);
    load_obj_display("./models/ventilador/base_sem_helice3.obj", 8);


    glutDisplayFunc(display);
    glutKeyboardFunc(moveCam);
    glutSpecialFunc(moveCamSpec);
    glutMotionFunc(mouse_func);
    glutPassiveMotionFunc(pass_mouse_func); 
    glutMainLoop();
    return 0;
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

        //glTranslatef ( -10 , 0 , -10 ) ;
        glPushMatrix();
        draw_helix();
        glPopMatrix();

        /*glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(0, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(1, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(2, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(3, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(4, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(5, 0.5, 0, 0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef ( -10 , 0 , -10 ) ;
        glScalef(5.0,5.0,5.0);
        draw_objects(6, 0.5, 0, 0);
        glPopMatrix();*/
    
    glFlush();
    glutSwapBuffers () ;
    glutPostRedisplay();
}

