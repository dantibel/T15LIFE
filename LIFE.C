#include <stdlib.h>
#include <windows.h>

#include "life.h"

#define LIFE_W 100
#define LIFE_H 100

int GetCell( byte *Field, int X, int Y )
{
  X = (X + LIFE_W) % LIFE_W;
	Y = (Y + LIFE_H) % LIFE_H;

	return Field[Y * LIFE_W + X];
	/* value = -1 – dark dead cell, value = 0 – light dead cell,
	   value = 1 – the elder cell, value = 2 – old cell, value = 3 - middle cell, value = 4 - young cell, value = 5 - the youngest cell */
}

void SetCell( byte *Field, int X, int Y, int Value )
{
	X = (X + LIFE_W) % LIFE_W;
	Y = (Y + LIFE_H) % LIFE_H;

	Field[Y * LIFE_W + X] = Value;
	/* value = 0 – dark dead cell, value = 1 – light dead cell,
		 value = 2 – the elder cell, value = 3 – old cell, value = 4 - middle cell, value = 5 - young cell, value = 6 - the youngest cell */
}

static int GetNeighbours( byte *Field, int X, int Y )
{
	int count = 0;

	count += GetCell(Field, X - 1, Y + 1) > 1;
	count += GetCell(Field, X, Y + 1) > 1;
	count += GetCell(Field, X + 1, Y + 1) > 1;

	count += GetCell(Field, X - 1, Y) > 1;
	count += GetCell(Field, X + 1, Y) > 1;

	count += GetCell(Field, X - 1, Y - 1) > 1;
	count += GetCell(Field, X, Y - 1) > 1;
	count += GetCell(Field, X + 1, Y - 1) > 1;

	return count;
	/* count of alive nieghbour cells */
}

static void FieldDraw( byte *F )
{
	int X, Y;

	for (Y = 0; Y < LIFE_H; Y++)
		for (X = 0; X < LIFE_W; X++)
		{	
			switch (GetCell(F, X, Y))
			{
			case 0:
				PutPixel(X, Y, 60, 60, 60);
				break;
			case 1:
				PutPixel(X, Y, 70, 70, 70);
				break;
			case 2:
				PutPixel(X, Y, 0, 80, 0);
				break;
			case 3:
				PutPixel(X, Y, 0, 110, 0);
				break;
			case 4:
				PutPixel(X, Y, 0, 140, 0);
				break;
			case 5:
				PutPixel(X, Y, 0, 170, 0);
				break;
			case 6:
				PutPixel(X, Y, 0, 200, 0);
				break;
			}
		}
}

static void NewGeneration( byte *F1, byte *F2, byte *F3 )
{
	int X, Y, n, value = 0;

	for (Y = 0; Y < LIFE_H; Y++)
		for (X = 0; X < LIFE_W; X++)
		{
			n = GetNeighbours(F1, X, Y);
			
			if (GetCell(F1, X, Y) > 1)
				if (n == 2 || n == 3)
					value = GetCell(F1, X, Y) - 1 > 2 ? GetCell(F1, X, Y) - 1 : 2;
				else
					value = GetCell(F3, X, Y);
			else
				if (n == 3)
					value = 6;
				else
				  value = GetCell(F3, X, Y);

			SetCell(F2, X, Y, value);
		}
}

void GameStep( void )
{
	byte * tmp;

	tmp = Field2;
	FieldDraw(Field1);
	NewGeneration(Field1, Field2, Field3);
	Field2 = Field1;
	Field1 = tmp;

	SleepEx(step, FALSE);
}

void ClearField( byte *Field )
{
	int X, Y, state = 1;

	for (Y = 0; Y < LIFE_H; Y++)
	{
		for (X = 0; X < LIFE_W; X++)
		{
			if (state % 2 == 1)
				SetCell(Field, X, Y, 0);
			else
				SetCell(Field, X, Y, 1);
			state++;
		}
		state++;
	}
}

void CreateFigure( byte *Field, char *Figure, int X0, int Y0 )
{
	int i = 0, c, X = X0, Y = Y0;

	while ((c = Figure[i++]) != 0)
	{
		if (c == '*')
		{
			PutPixel(X, Y, 0, 0, 155);
			SetCell(Field, X, Y, 6);
		}
		X++;
		if (c == '\n')
		{
			X = X0;
			Y++;
		}
	}
}

void GameInit( void )
{
	Field1 = malloc(LIFE_H * LIFE_W);
	Field2 = malloc(LIFE_H * LIFE_W);
	Field3 = malloc(LIFE_H * LIFE_W);

	ClearField(Field1);
	ClearField(Field2);
	ClearField(Field3);
	FieldDraw(Field1);
}