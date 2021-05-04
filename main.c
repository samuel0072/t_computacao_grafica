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

//#define DEBUG
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
    load_obj_display("./models/basquete.obj", 4);
    load_obj_display("./models/estanteDeLivros.obj", 5);
    load_obj_display("./models/sofa.obj", 6);
    load_obj_display("./models/ventilador/helice.obj", 7);
    load_obj_display("./models/ventilador/base_sem_helice3.obj", 8);
    load_obj_display("./models/casa.obj", 9);
    load_obj_display("./models/janelaAberta.obj", 10);
    load_obj_display("./models/lixeira.obj", 11);
    load_obj_display("./models/portaAberta.obj", 12);
    load_obj_display("./models/portaFechada.obj", 13);
    load_obj_display("./models/janelaFechada.obj", 14);
    load_obj_display("./models/mesa.obj", 15);
    load_obj_display("./models/quadroFaceTriangular.obj", 3);

    


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
    //ventilador
    glPushMatrix();
    glTranslatef ( 70 ,48.5 , -30 ) ;
    glScalef(4.0, 4.0, 4.0);
    glRotatef(90, 0, 0.9, 0);
    draw_helix();
    glPopMatrix();

    //casa
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    draw_objects(9, 0.9, 0, 0);
    glPopMatrix();

    //cadeira
    glPushMatrix();
    glTranslatef ( -10 , 0.7 , -50 ) ;
    glScalef(4.0, 4.0, 4.0);
    glRotatef(90, 0, 1, 0);
    draw_objects(0, 0.9, 0.9, 0);
    glPopMatrix();

    //cama
    glPushMatrix();
    glTranslatef ( -80 ,4, 64 ) ;
    glScalef(7.0, 7.0, 7.0);
    draw_objects(1, 0.9, 0.9, 0);
    glPopMatrix();

    //copo
    glPushMatrix();
    glTranslatef ( -13 , 15.8 , -65 ) ;
    glScalef(4.0, 4.0, 4.0);
    glRotatef(90, 0, 1, 0);
    draw_objects(2, 0.9, 0.9, 0);
    glPopMatrix();

    //basquete
    glPushMatrix();
    glTranslatef ( -78.2 ,30 , 1 ) ;
    glScalef(7.0,7.0, 7.0);
    glRotatef(90, 0, 1, 0);
    draw_objects(4, 0.9, 0.9, 0);
    glPopMatrix();

    //estante
    glPushMatrix();
    
    glTranslatef ( 90 ,30 , -60 ) ;
    glRotatef(180, 0, 1, 0);
    glScalef(3.0, 3.0, 3.0);
    draw_objects(5, 0.9, 0.9, 0);
    glPopMatrix();

    //sofa
    glPushMatrix();
    glTranslatef ( 15 , 0.7 , 70 ) ;
    glScalef(2.0, 2.0, 2.0);
    glRotatef(180, 0, 1, 0);
    draw_objects(6, 0.9, 0, 0.9);
    glPopMatrix();

    //janela
    glPushMatrix();
    draw_window();
    glPopMatrix();

    //lixeira
    glPushMatrix();
    glTranslatef ( 21 , 0 , -66 ) ;
    glScalef(2.0, 2.0, 2.0);
    draw_objects(11, 0.9, 0, 0.9);
    glPopMatrix();

    //porta 
    glPushMatrix();
    draw_door();
    glPopMatrix();

    //mesa
    glPushMatrix();
    glTranslatef ( -15 , 0 , -73.5 ) ;
    glScalef(2.0, 2.0, 2.0);
    glRotatef(90, 0, 1, 0);
    draw_objects(15, 0.9, 0, 0.9);
    glPopMatrix();

    //quadro
    glPushMatrix();
    glTranslatef ( 0 ,30 , -74.5 ) ;
    glScalef(1.5, 1.5, 1.5);
    //glRotatef(270, 0, 1, 0);
    draw_objects(3, 0.1, 0.5, 0.8);
    glPopMatrix();

        

      
    
    glFlush();
    glutSwapBuffers () ;
    glutPostRedisplay();
}

