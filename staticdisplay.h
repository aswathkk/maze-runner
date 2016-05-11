#ifndef STATIC_DISPLAY_H
#define SATIC_DISPLAY_H

struct StaticDisplay {

		int win_width;
		int win_height;
		float t = 150;

		void glPrint(float x, float y, char a[]){
			int i;
			glRasterPos3f(x, y, 0);
			for(i=0;i<strlen(a);i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,a[i]);
		}

		void drawRect(int x1, int y1, int x2, int y2) {
			glBegin(GL_POLYGON);
			glVertex2f(x1,y1);
			glVertex2f(x2,y1);
			glVertex2f(x2,y2);
			glVertex2f(x1,y2);
			glEnd();
		}

		void drawTime() {
			char s[20];
			t-=.015;
			sprintf(s,"time : %.0f",t);
			glColor3f(1,0,0);
			glPrint(200,475,s);
			if(t < 0)
				flag = 0;
		}

		void gameOver() {
			glColor3f(1,.2,0);
			glPrint(170,300,"GAME OVER!");
			glColor3f(0,0,0);
			glPrint(150,250,"Press ESC to QUIT");
			glColor3f(1,1,1);
			drawRect(0,0,500,500);
		}

		int flag = 1; // Detects Win or Loose

		StaticDisplay(int w, int h) {
			win_width = w;
			win_height = h;
		}

		void reshape(int w, int h) {
			win_width = w;
			win_height = h;
		}

		void draw() {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0,500,0,500);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);

			if(flag == 1) {
				drawTime();
				glColor3f(1,1,1);
				drawRect(0,450,500,500);
			} else if(flag == 0) {
				gameOver();
			}

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45,(float)win_width/(float)win_height,.1,100);
			glMatrixMode(GL_MODELVIEW);
		}

};

#endif