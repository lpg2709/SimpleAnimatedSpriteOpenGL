#include <stdio.h>
#include <string.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT);

	float quad_size = 0.5;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-quad_size, -quad_size);
		glTexCoord2f(quad_size, 0.0); glVertex2f( quad_size, -quad_size);
		glTexCoord2f(quad_size, quad_size); glVertex2f( quad_size,  quad_size);
		glTexCoord2f(0.0, quad_size); glVertex2f(-quad_size,  quad_size);
	glEnd();

	glutSwapBuffers();
}

void framebuffer_size_callback(int w, int h){
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);

}

void setup(){
	glClearColor(0.2, 0.2, 0.4, 1.0);
}

int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Animated Sprit");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(framebuffer_size_callback);

	setup();

	glutMainLoop();
	
	return 0;
}
