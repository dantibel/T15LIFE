typedef unsigned char byte;	

extern byte *Field1, *Field2, *Field3;

extern int step;

void PutPixel( int X, int Y, int Red, int Green, int Blue );
void SetCell( byte *Field, int X, int Y, int v );
int GetCell( byte *Field, int X, int Y );
void ClearField( byte *Field );
void CreateFigure( byte *Field, char *Figure, int X0, int Y0 );
void GameInit( void );
void GameStep( void );