//#include <windows.h>
#include <cstdio>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

// Function prototypes
void generateColors();
double myrandom(bool reset = false);
void drawTriangle(GLfloat *a, GLfloat *b, GLfloat *c);
void divideTriangle(GLfloat *a, GLfloat *b, GLfloat *c, int iterations);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void display();
void doZoom();
void init();


//coordenadas del triángulo que se dividirá
GLfloat triangle[3][2] = {{-1.0, -1.0}, 
                          { 0.0,  1.0}, 
                          { 1.0, -1.0}};

int num_iterations;
double zoom = 0;
int shading = GL_SMOOTH;

typedef struct {
	double r; 
	double g;
	double b;
} color;

color colors[1000];

void generateColors() {

	FILE * fp;
	fp = fopen("color.txt", "r");

	int ir, ig, ib;


	for (int i = 0; i < num_iterations+1; i++) {
		fscanf(fp, "%d", &ir);
		fscanf(fp, "%d", &ig);
		fscanf(fp, "%d", &ib);
		// colors[i].r = rand() / (double) RAND_MAX;
		// colors[i].g = rand() / (double) RAND_MAX;
		// colors[i].b = rand() / (double) RAND_MAX;
		colors[i].r = (1.0f/255) * ir;
		colors[i].g = (1.0f/255) * ig;
		colors[i].b = (1.0f/255) * ib;
	}

	fclose(fp);
}

void drawTriangle(GLfloat *a, GLfloat *b, GLfloat *c) {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
	glShadeModel(shading);
	glBegin(GL_TRIANGLES);
		glColor3f(colors[num_iterations].r, colors[num_iterations].g, colors[num_iterations].b);
		glVertex2fv(a);
		glColor3f(colors[num_iterations].r, colors[num_iterations].g, colors[num_iterations].b);
		glVertex2fv(b);
		glColor3f(colors[num_iterations].r, colors[num_iterations].g, colors[num_iterations].b);
		glVertex2fv(c);
	glEnd();
}

void divideTriangle(GLfloat *a, GLfloat *b, GLfloat *c, int iterations) {
     GLfloat v[3][2];
     int j;
     if (iterations > 0) {
        for (j = 0; j < 2; j++) {
            v[0][j] = (a[j] + b[j]) / 2;
		}
        for (j = 0; j < 2; j++) {
			v[1][j] = (a[j] + c[j]) / 2;
		}
        for (j = 0; j < 2; j++) {
            v[2][j] = (b[j] + c[j]) / 2;
		}

        divideTriangle( a  , v[0], v[1], iterations-1);
        divideTriangle(v[0],  b  , v[2], iterations-1);
        divideTriangle(v[1], v[2],  c  , iterations-1);

        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	
		glShadeModel(shading);
		glBegin(GL_TRIANGLES);
			glColor3f(colors[num_iterations - iterations].r, colors[num_iterations - iterations].g, colors[num_iterations - iterations].b);
			glVertex2fv(v[0]);
			glColor3f(colors[num_iterations - iterations].r, colors[num_iterations - iterations].g, colors[num_iterations - iterations].b);
			glVertex2fv(v[1]);
			glColor3f(colors[num_iterations - iterations].r, colors[num_iterations - iterations].g, colors[num_iterations - iterations].b);
			glVertex2fv(v[2]);
		glEnd();

     } else {
        drawTriangle(a,b,c);
     }
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':
			exit(0);
			break;
	}
}

void special(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			if (zoom - 0.1 > -1) zoom -= 0.05;
			doZoom();
			break;
		case GLUT_KEY_DOWN:
			zoom += 0.05;
			doZoom();
			break;
	}
}

void doZoom() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 - zoom, 1.0 + zoom, -1.0 - zoom, 1.0 + zoom);
	glMatrixMode(GL_MODELVIEW);
	display();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	divideTriangle(triangle[0], triangle[1], triangle[2], num_iterations);
	glFlush();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {\
	printf("Masukkan jumlah level : ");
	scanf("%d", &num_iterations);

	generateColors();

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Sierpinski Triangle");
	glutPositionWindow(100, 100);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
