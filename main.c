#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "stb_image.h"

unsigned int texturesData[10];
unsigned int oneSpriteSize = 32;
unsigned int total_image_row;
unsigned int total_image_col;

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT);

	float quad_size = 1.0;
	glBindTexture(GL_TEXTURE_2D, texturesData[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(-quad_size, -quad_size);

		glTexCoord2f(1.0, 0.0); 
		glVertex2f( quad_size, -quad_size);

		glTexCoord2f(1.0, 1.0); 
		glVertex2f( quad_size,  quad_size);

		glTexCoord2f(0.0, 1.0); 
		glVertex2f(-quad_size,  quad_size);
	glEnd();


	glutSwapBuffers();
}

void framebuffer_size_callback(int w, int h){
	float aspectRatio;
	float size = 1;

	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (float) w / (float) h;

	if(w <= h){
		glOrtho(-size, size, -size/aspectRatio, size/aspectRatio, -size, size);
	}else{
		glOrtho(-size * aspectRatio, size * aspectRatio, -size, size, -size, size);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setup(){
	glClearColor(0.2, 0.2, 0.4, 1.0);



	int width, height, nrChanels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char *sprite = stbi_load("./rogue_srpite.png", &width, &height, &nrChanels, 0);
	if(!sprite){
		printf("Erro ao abrir ./rogue_srpite.png");
		exit(1);
	}

	total_image_row = (unsigned int) width/ (unsigned int) oneSpriteSize;
	total_image_col = (unsigned int) height/ (unsigned int) oneSpriteSize;

	printf("Total row: %d\n", total_image_row);
	printf("Total col: %d\n", total_image_col);

	glGenTextures(10, texturesData);
	glBindTexture(GL_TEXTURE_2D, texturesData[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite);
	stbi_image_free(sprite);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glEnable(GL_TEXTURE_2D);
	// Enable transparence
	glEnable(GL_BLEND); // Enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Change blend function
}

void timerFunction(int val){
	glutPostRedisplay();
	glutTimerFunc(33, timerFunction, 1);
}

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Animated Sprit");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(framebuffer_size_callback);
	glutTimerFunc(10, timerFunction, 1);

	setup();

	glutMainLoop();
	
	return 0;
}
