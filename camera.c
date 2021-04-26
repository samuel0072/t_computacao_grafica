#include "camera.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct Camera {
    float p_x, p_y, p_z;//posicao da camera
    float n_x, n_y, n_z;//Normal ao vetor de view da camera, vetor v
    float v_x, v_y, v_z;//Vetor que define a direção e sentido de visualização, vetor n
    float s_x, s_y, s_z;//vetor resultado do produto vetorial entre o normal e o view, vetor s
};

void updateSvec(Camera* c);

void cross_v_u(float v[], float u[], float output[]);



Camera* init_camera() {
    Camera* c = (Camera*)malloc(sizeof(Camera));
    c->p_x = 0;
    c->p_y = 1;
    c->p_z = 1;

    c->n_x = 0;
    c->n_y = 1;
    c->n_z = 0;

    c->v_x = 0;
    c->v_y = 0;
    c->v_z = 1;

    updateSvec(c);

    return c;
}

void descruct_camera(Camera* c) {
    free(c);
}

float* getCamCenter(Camera* c) {
    float* pos = (float*)malloc(3*sizeof(float));
    pos[0] = c->p_x + (CAM_MV_SPEED * c->v_x);
    pos[1] = c->p_y + (CAM_MV_SPEED * c->v_y);
    pos[2] = c->p_z + (CAM_MV_SPEED * c->v_z);

    return pos;
}

float* getCamPos(Camera* c) {
    float* pos = (float*)malloc(3*sizeof(float));
    pos[0] = c->p_x;
    pos[1] = c->p_y;
    pos[2] = c->p_z;

    return pos;
}

float* getCamNV(Camera* c) {
    float* pos = (float*)malloc(3*sizeof(float));
    pos[0] = c->n_x;
    pos[1] = c->n_y;
    pos[2] = c->n_z;

    return pos;
}


void moveCamFoward(Camera* c) {
    c->p_x += CAM_MV_SPEED * c->v_x;
    c->p_y += CAM_MV_SPEED * c->v_y;
    c->p_z += CAM_MV_SPEED * c->v_z;
}

void moveCamBackwards(Camera* c) {
    c->p_x += - CAM_MV_SPEED * c->v_x;
    c->p_y += - CAM_MV_SPEED * c->v_y;
    c->p_z += - CAM_MV_SPEED * c->v_z;
}

void moveCamRight(Camera* c) {
    c->p_x +=  CAM_MV_SPEED * c->s_x;
    c->p_y +=  CAM_MV_SPEED * c->s_y;
    c->p_z +=  CAM_MV_SPEED * c->s_z;
}

void moveCamLeft(Camera* c) {
    c->p_x +=  - CAM_MV_SPEED * c->s_x;
    c->p_y +=  - CAM_MV_SPEED * c->s_y;
    c->p_z +=  - CAM_MV_SPEED * c->s_z;
}

void moveCamUp(Camera* c) {
    //Se move no eixo Y
    c->p_x +=  CAM_MV_SPEED * 0;
    c->p_y +=  CAM_MV_SPEED * 1;
    c->p_z +=  CAM_MV_SPEED * 0;
}

void moveCamDown(Camera* c) {
    //Se move no eixo Y
    c->p_x +=  - CAM_MV_SPEED * 0;
    c->p_y +=  - CAM_MV_SPEED * 1;
    c->p_z +=  - CAM_MV_SPEED * 0;
}

void turnCamBack(Camera* c) {
    c->v_x = -  c->v_x;
    c->v_y = -  c->v_y;
    c->v_z = -  c->v_z;

}


void rotateCamRight(Camera* c) {

    /*
    //Esse código rotaciona ao redor do eixo Y
    float const3 = (1 - cos(CAM_ROT_SPEED))*(c->v_y); 
    //como ta girando ao redor do eixo Y
    // o produto interno resulta somente em c-v_y
    float v_scaled[3] = {c->v_x*cos(CAM_ROT_SPEED), 
                            c->v_y*cos(CAM_ROT_SPEED), 
                            c->v_z*cos(CAM_ROT_SPEED)}; 
    
    float yxv[3];
    float y[] = {0, 1, 0};
    float v[] = {c->v_x, c->v_y, c->v_z};

    cross_v_u(y, v, yxv);
    yxv[X] *= sin(CAM_ROT_SPEED);
    yxv[Y] *= sin(CAM_ROT_SPEED);
    yxv[Z] *= sin(CAM_ROT_SPEED);

    c->v_x = v_scaled[X] + yxv[X] + 0*const3;//o vetor Y é 0 na cord x
    c->v_y = v_scaled[Y] + yxv[Y] + 1*const3;//o vetor Y é 1 na cord y
    c->v_z = v_scaled[Z] + yxv[Z] + 0*const3;//o vetor Y é 0 na cord z*/


    c->v_x = cos(CAM_ROT_SPEED)*c->v_x + sin(CAM_ROT_SPEED)* c->s_x;
    c->v_y = cos(CAM_ROT_SPEED)*c->v_y + sin(CAM_ROT_SPEED)* c->s_y;
    c->v_z = cos(CAM_ROT_SPEED)*c->v_z + sin(CAM_ROT_SPEED)* c->s_z;
    
    
    updateSvec(c);
} 

void rotateCamLeft(Camera* c) {

    /*
    //Esse código rotaciona ao redor do eixo Y
    float const3 = (1 - cos(-CAM_ROT_SPEED))*(c->v_y); 
    //como ta girando ao redor do eixo Y
    // o produto interno resulta somente em c-v_y
    float v_scaled[3] = {c->v_x*cos(-CAM_ROT_SPEED), 
                            c->v_y*cos(-CAM_ROT_SPEED), 
                            c->v_z*cos(-CAM_ROT_SPEED)}; 
    
    float yxv[3];
    float y[] = {0, 1, 0};
    float v[] = {c->v_x, c->v_y, c->v_z};

    cross_v_u(y, v, yxv);
    yxv[X] *= sin(-CAM_ROT_SPEED);
    yxv[Y] *= sin(-CAM_ROT_SPEED);
    yxv[Z] *= sin(-CAM_ROT_SPEED);

    c->v_x = v_scaled[X] + yxv[X] + 0*const3;//o vetor Y é 0 na cord x
    c->v_y = v_scaled[Y] + yxv[Y] + 1*const3;//o vetor Y é 1 na cord y
    c->v_z = v_scaled[Z] + yxv[Z] + 0*const3;//o vetor Y é 0 na cord z*/

    c->v_x = cos(-CAM_ROT_SPEED)*c->v_x + sin(-CAM_ROT_SPEED)* c->s_x;
    c->v_y = cos(-CAM_ROT_SPEED)*c->v_y + sin(-CAM_ROT_SPEED)* c->s_y;
    c->v_z = cos(-CAM_ROT_SPEED)*c->v_z + sin(-CAM_ROT_SPEED)* c->s_z;
    
    
    updateSvec(c);
} 

void rotateCamUp(Camera* c) {

    float vx, vy, vz;
    vx = -c->v_x;
    vy = -c->v_y;
    vz = -c->v_z;

    //O vetor v está rotacionando se aproximando de n
    c->v_x = cos(CAM_ROT_SPEED)*c->v_x + sin(CAM_ROT_SPEED)* c->n_x;
    c->v_y = cos(CAM_ROT_SPEED)*c->v_y + sin(CAM_ROT_SPEED)* c->n_y;
    c->v_z = cos(CAM_ROT_SPEED)*c->v_z + sin(CAM_ROT_SPEED)* c->n_z;

    //O vetor n está rotacionando se aproximando de -v
    c->n_x = cos(CAM_ROT_SPEED)*c->n_x + sin(CAM_ROT_SPEED)* (vx);
    c->n_y = cos(CAM_ROT_SPEED)*c->n_y + sin(CAM_ROT_SPEED)* (vy);
    c->n_z = cos(CAM_ROT_SPEED)*c->n_z + sin(CAM_ROT_SPEED)* (vz);

}

void rotateCamDown(Camera* c) {
    float vx, vy, vz;
    vx = -c->v_x;
    vy = -c->v_y;
    vz = -c->v_z;

    //O vetor v está rotacionando se aproximando de n
    c->v_x = cos(-CAM_ROT_SPEED)*c->v_x + sin(-CAM_ROT_SPEED)* c->n_x;
    c->v_y = cos(-CAM_ROT_SPEED)*c->v_y + sin(-CAM_ROT_SPEED)* c->n_y;
    c->v_z = cos(-CAM_ROT_SPEED)*c->v_z + sin(-CAM_ROT_SPEED)* c->n_z;

    //O vetor n está rotacionando se aproximando de -v
    c->n_x = cos(-CAM_ROT_SPEED)*c->n_x + sin(-CAM_ROT_SPEED)* (vx);
    c->n_y = cos(-CAM_ROT_SPEED)*c->n_y + sin(-CAM_ROT_SPEED)* (vy);
    c->n_z = cos(-CAM_ROT_SPEED)*c->n_z + sin(-CAM_ROT_SPEED)* (vz);
}

void updateSvec(Camera* c) {
    //atualiza o vetor s da camera
    float* cords = (float*)malloc(3*sizeof(float));

    //calculo do produto vetorial
    c->s_x = (c->v_y*c->n_z) - (c->n_y*c->v_z);
    c->s_y = (c->n_x*c->v_z) - (c->v_x*c->n_z);
    c->s_z = (c->v_x*c->n_y) - (c->n_x*c->v_y);

}

void cross_v_u(float v[], float u[], float output[]) {
    //Faz o produto vetorial VxU e escreve o resultado no vetor output
    output[X] = (v[Y]*u[Z]) - (u[Y]*v[Z]);
    output[Y] = (u[X]*v[Z]) - (v[X]*u[Z]);
    output[Z] = (v[X]*u[Y]) - (u[X]*v[Y]);

}