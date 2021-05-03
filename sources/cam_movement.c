#include "../headers/cam_movement.h"
#include "../headers/draw_objects.h"
#include <GL/gl.h>
#include <GL/glut.h>

int old_x = 0;
int old_y = 0;

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
