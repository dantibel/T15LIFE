/* Belov Danil, 10-6, 01.10.2021 */

#include <stdlib.h>

#include "glut.h"
#pragma comment( lib, "glut32.lib" )

#include "life.h"

#define FRAME_H 100
#define FRAME_W 100
#define FRAME_ZOOM 10

byte Frame[FRAME_H][FRAME_W][3], *Field1, *Field2, *Field3;

static int GameStart = 0;

int step = 110;

char Smpr1[] = { "***\n" };
char Smpr2[] =
{ 
  "*\n"
  "*\n"
  "*\n" 
};

char Gldr1[] = 
{
  "***\n"
  "  *\n"
  " * \n"
};

char Gldr3[] =
{
  "***\n"
  "*  \n"
  " * \n"
};

char Blst1[] =
{
  "****\n"
  "****\n"
  "****\n"
  "****\n"
};

char Blst2[] =
{
  "******\n"
  "*    *\n"
  "*    *\n"
  "*    *\n"
  "*    *\n"
  "******\n"
};

char Lss1[] =
{
  "*  * \n"
  "    *\n"
  "*   *\n"
  " ****\n"
};

char Lss2[] =
{
  " *  *\n"
  "*    \n"
  "*   *\n"
  "**** \n"
};

char Mss1[] =
{
  "  *   \n"
  "*   * \n"
  "     *\n"
  "*    *\n"
  " *****\n"
};

char Mss2[] =
{
  "   *  \n"
  " *   *\n"
  "*     \n"
  "*    *\n"
  "***** \n"
};

char Hss1[] =
{
  "  **   \n"
  "*    * \n"
  "      *\n"
  "*     *\n"
  " ******\n"
};

char Hss2[] =
{
  "   **  \n"
  " *    *\n"
  "*      \n"
  "*     *\n"
  "****** \n"
};

char Dfns[] =
{
	"      *      \n"
	"     * *     \n"
	"     * *     \n"
	"      *      \n"
	"    *   *    \n"
	" **  * *  ** \n"
	"*  *  *  *  *\n"
	" **  * *  ** \n"
	"    *   *    \n"
	"      *      \n"
	"     * *     \n"
	"     * *     \n"
	"      *      \n"
};

void PutPixel( int X, int Y, int Red, int Green, int Blue )
{
    if (X > 0 || Y > 0 || X < FRAME_W || Y < FRAME_H)
	{
		Frame[Y][X][0] = Blue;
		Frame[Y][X][1] = Green;
		Frame[Y][X][2] = Red;
	}
}

void Display( void )
{
    glClear(GL_COLOR_BUFFER_BIT);
  
    glPixelZoom(FRAME_ZOOM, -FRAME_ZOOM);
    glRasterPos2d(-1, 1);
    glDrawPixels(FRAME_H, FRAME_W, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

    if (GameStart)
	    GameStep();

    glFinish();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Keyboard( unsigned char Key, int X, int Y )
{
	int i, j;

	switch (Key)
	{
	case 27:
		exit(30);
		break;
	case 13:
		GameStart = !GameStart;
		break;
	case 8:
		for (j = 0; j < FRAME_H; j++)
			for (i = 0; i < FRAME_W; i++)
				if (GetCell(Field1, i, j) > 1)
					PutPixel(i, j, 155, 0, 0);
		ClearField(Field1);
		break;
	case '-':
		if (step < 310)
		step += 50;
		break;
	case '+':
		if (step > 10)
		step -= 50;
		break;
	case 's':
		CreateFigure(Field1, Smpr1, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case 'S':
		CreateFigure(Field1, Smpr2, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case 'g':
		CreateFigure(Field1, Gldr1, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case 'G':
		CreateFigure(Field1, Gldr3, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case 'b':
		CreateFigure(Field1, Blst1, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case 'B':
		CreateFigure(Field1, Blst2, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case '1':
		CreateFigure(Field1, Lss1, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case '!':
		CreateFigure(Field1, Lss2, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case '2':
		CreateFigure(Field1, Mss1, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case '@':
		CreateFigure(Field1, Mss2, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case '3':
		CreateFigure(Field1, Hss1, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case '#':
		CreateFigure(Field1, Hss2, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	case 'd':
		CreateFigure(Field1, Dfns, X / FRAME_ZOOM, Y / FRAME_ZOOM);
		break;
	}    
}

void Mouse(int Button, int State, int X, int Y)
{
	int i, j;

	switch (Button)
	{
	case GLUT_LEFT_BUTTON:
		if (State == GLUT_DOWN)
		{
			PutPixel(X / FRAME_ZOOM, Y / FRAME_ZOOM, 0, 0, 155);
			SetCell(Field1, X / FRAME_ZOOM, Y / FRAME_ZOOM, 6);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (State == GLUT_DOWN)
		{
			for (j = Y - FRAME_ZOOM; j < Y + FRAME_ZOOM; j++)
				for (i = X - FRAME_ZOOM; i < X + FRAME_ZOOM; i++)
				{
					PutPixel(i / FRAME_ZOOM, j / FRAME_ZOOM, 155, 0, 0);
					SetCell(Field1, i / FRAME_ZOOM, j / FRAME_ZOOM, GetCell(Field3, i / FRAME_ZOOM, j / FRAME_ZOOM));
				}
		}
		break;
	}
}

void main( int argc, char*argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("DB6'20211001");

  GameInit();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  glClearColor(0.30, 0.47, 0.8, 1);

  glutMainLoop();
}