#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "stb_image.h"

unsigned int texturesData[10];
float sprite_width = 32.0f, sprite_height = 32.0f;
int width, height, nrChanels;
unsigned int oneSpriteSize = 32;
unsigned int total_image_row;
unsigned int total_image_col;
float x = 0.0f, y = 0.0f;
float c_time = 0;

void print_current_sprite_animation(){
	printf("\rCurrent index: %d", (int) y);
	fflush(stdout);
}

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT);
	c_time++;
	if(c_time > 5){
		c_time = 0;
		x++;
		if(x == total_image_col - 1){
			x = 0;
		}
	}

	print_current_sprite_animation();

	float quad_size = 1.0;
	glBindTexture(GL_TEXTURE_2D, texturesData[0]);
	glBegin(GL_QUADS);
		glTexCoord2f((x*sprite_width)/width, (y*sprite_height)/height);
		glVertex2f(-quad_size, -quad_size);

		glTexCoord2f(((x + 1.0f)*sprite_width)/width, (y*sprite_height)/height);
		glVertex2f( quad_size, -quad_size);

		glTexCoord2f(((x + 1.0f)*sprite_width)/width, ((y+1.0f)*sprite_height)/height);
		glVertex2f( quad_size,  quad_size);

		glTexCoord2f((x*sprite_width)/width, ((y+1.0f)*sprite_height)/height);
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

	stbi_set_flip_vertically_on_load(1);
	unsigned char *sprite = stbi_load("./rogue_srpite.png", &width, &height, &nrChanels, 0);
	if(!sprite){
		printf("Fail to open ./rogue_srpite.png");
		exit(1);
	}

	total_image_col = (unsigned int) width/ (unsigned int) oneSpriteSize;
	total_image_row = (unsigned int) height/ (unsigned int) oneSpriteSize;

	printf("Sprite width: %d\n", width);
	printf("Sprite height: %d\n", height);
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
	glutTimerFunc(33, timerFunction, 1); // ~= 60 fps
}

void updateY(int add){
	y += add;
	x = 0; // First frame
	if( y < 0) y = 0;
	if( y > total_image_row - 1) y = total_image_row - 1;
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 'k':
			updateY(1);
			break;
		case 'j':
			updateY(-1);
			break;
	}
}

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Animated Sprit");
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(framebuffer_size_callback);
	glutTimerFunc(10, timerFunction, 1);

	setup();

	glutMainLoop();

	return 0;
}
