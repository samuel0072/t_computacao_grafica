#include "../headers/draw_objects.h"
#include "../headers/obj_import.h"
#include "../headers/stb_image.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

struct TextureInfo {
    int width, height, nrChannels;
    unsigned char* data;
};


int WINDOW_OPEN = 0;//flag para abrir a janela
int HEX_ANGLE = 0;

int DOOR_OPEN = 0;

float OFF_SET_COL = 0.1;

TextureInfo** textures = NULL;

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
     if(WINDOW_OPEN) {
         //janela aberta
        glTranslatef ( 28 , 30 , 65 ) ;
        glScalef(0.5, 0.7, 0.5);
        draw_objects(10, 0.8, 0.2, 0.2);
     }
     else {
         //janela fechada
        glTranslatef ( 28 , 30 , 65 ) ;
        glScalef(0.5, 0.7, 0.5);
        draw_objects(14, 0.8, 0.2, 0.2);
     }
    
    
}

void draw_cube() {
    glBegin(GL_QUADS);
        //glColor3f (0.5 , 0.5 , 0.5 ) ;

        
        glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
        

        glTexCoord2f(1, 0);
		glVertex3f(1.5, 0, 0);
        

        
        glTexCoord2f(1, 1);
        glVertex3f(1.5, 1, 0);
        

        glTexCoord2f(0, 1);
        glVertex3f(0, 1, 0);
        

    glEnd();
    
}

void draw_helix() {
    //glScalef(5.0,5.0,5.0);
    draw_objects(8, 0.8, 0.8, 0);
    glTranslatef(0, 1.7, 0);
    glScalef(0.75,0.75,0.75);
    glRotatef(90, 1, 0, 0);

    HEX_ANGLE -= 1;
    HEX_ANGLE %= 360;
    glRotatef(HEX_ANGLE, 0, 1, 0);//Gira no Y pq  ventilador original ta no plano XZ e não no XY

    draw_objects(7, 0.5, 0.2, 0.2);
    
    
}

void draw_door() {
    if(DOOR_OPEN) {
        //aberta
        glTranslatef ( -43 , 0.6 , -59.4 ) ;
        glScalef(1, 0.8, 0.75);
        draw_objects(12, 0.7, 0.1, 0.9);
    }
    else {
        //porta fechada
        glTranslatef ( -43 , 0.6 , -70.4 ) ;
        glScalef(0.75, 0.8, 1);
        draw_objects(13, 0.7, 0.1, 0.9);

    }
    
}

void change_door_state() {
    DOOR_OPEN = !DOOR_OPEN;
}

void change_window_state() {
    WINDOW_OPEN = !WINDOW_OPEN;
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
            glColor3f (r + OFF_SET_COL , g + OFF_SET_COL , b + OFF_SET_COL) ;
            glNormal3f(NORMALS[i].x, NORMALS[i].y, NORMALS[i].z);
            glTexCoord2f(TEX_COORDS[i].x, TEX_COORDS[i].y);
            glVertex3f(VERTICES[i].x, VERTICES[i].y, VERTICES[i].z);
            OFF_SET_COL = - OFF_SET_COL;
	    }
	    glEnd();
        
    }
    else {
        printf("Indice fora do range permitido: [0, %d)", MODEL_QUANT);
        exit(1);
    }
}

void load_texture(const char* path, int index) {

    if(0 <= index <= MODEL_QUANT) {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        textures[index] = (TextureInfo*)malloc(sizeof(TextureInfo));
        textures[index]->data = data;
        textures[index]->height = height;
        textures[index]->width = width;
        textures[index]->nrChannels = nrChannels;
    }
    else {
        printf("Indice de textura inválido.");
        exit(1);
    }
    
}

void init_textures_vec() {
    textures = (TextureInfo**)malloc(MODEL_QUANT*sizeof(TextureInfo*));
}

void aply_texture(int index) {
    if(0 <= index <= MODEL_QUANT) {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        unsigned char* data = textures[index]->data;

        int width = textures[index]->width,
            height= textures[index]->height,
            nrChannels = textures[index]->nrChannels;

        if (data)
        {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            //stbi_image_free(data);
            //não to liberando pq o código só carrega os arquivo de textura uma única vez
        }
        else
        {
            perror("Texture failed to load");
            //stbi_image_free(data);
        }
    }
    else {
         printf("Indice de textura inválido.");
        exit(1);
    }
}
