#ifndef CAMERA_H
#define CAMERA_H

#define CAM_MV_SPEED  1.0f//velocidade de movimento em unidades do mundo
#define CAM_ROT_SPEED 0.0174533//angulo de rotação em radianos
#define FOV 75.0f
#define X 0
#define Y 1
#define Z 2


/*A struct camera é composta de 4 vetores: v, n, s e p
o vetor v indica a direção e o sentido que a camera olha
o vetor n é perpendicular ao vetor v e indica a direção do topo da camera
o vetor s é o produto vetorial entre o vetor v e n: vXn
o vetor p indica a posição da camera 
*/
typedef struct Camera Camera;

//inicializa a camera na posição (0, 1, 1)
//olha na direção (0, 0, 1)
//o topo é na direção (0, 1, 0)
//inicializa o vetor s segundo sua definição
Camera* init_camera();

//desaloca a area de memoria da camera
void descruct_camera(Camera* c);

//obtém o ponto do centro da camera pela formula:
//v + CAM_MV_SPEED*p, onde v e p são os vetores da camera
float* getCamCenter(Camera* c);

//retorna o vetor p
float* getCamPos(Camera* c);

//retorna o vetor n
float* getCamNV(Camera* c);

/*Para se mover para frente apenas somamos o vetor p + o vetor v*/
void moveCamFoward(Camera* c);

/*Para se mover para trás apenas somamos o vetor p + o vetor v no sentido contrario(-view)*/
void moveCamBackwards(Camera* c);

/*Para se mover para direita apenas somamos o vetor p + o vetor s*/
void moveCamRight(Camera* c);

/*Para se mover para esquerda apenas somamos o vetor p + o vetor -s*/
void moveCamLeft(Camera* c);

/*A camera se move ao longo do eixo Y para cima*/
void moveCamUp(Camera* c);

/*A camera se move ao longo do eixo Y para baixo*/
void moveCamDown(Camera* c);

/*Vira a camera para trás, O vetor view muda de sentido: -v*/
void turnCamBack(Camera* c);


/*As funções de rotação usam a Rodrigues' rotation formula
disponivel em: https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula

consiste em rotacionar um vetor ao redor do outro

Rotacionamos o vetor view ao redor do vetor normal para girar a camera para esquerda/direita
rotacionamos o vetor view e normal para girar a camera para cima/baixo
*/

//Rotaciona o vetor v ao redor do eixo y no sentido antihorário
void rotateCamLeft(Camera* c);

//Rotaciona o vetor v ao redor do eixo yno sentido horário
void rotateCamRight(Camera* c);

//Rotaciona o vetor v e o vetor n ao redor do vetor s no sentido horário
void rotateCamUp(Camera* c);

//Rotaciona o vetor v e o vetor n ao redor do vetor s no sentido antihorário
void rotateCamDown(Camera* c);

//Rotaciona o vetor n ao redor do vetor v no sentido horário
void rotateNAboutVCW(Camera* c);

//Rotaciona o vetor n ao redor do vetor v no sentido horário
void rotateNAboutVACW(Camera* c );

void resetOrgDir(Camera* c);
#endif