MSG		msg;
BOOL	done=FALSE;
BOOL	done2=FALSE;

GLuint texture[16];

int i, j;

GLuint		fonttext;	



int menu_texture;


int mapa[15][19] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,9,200,200,1,0,0,0,0,9,0,0,0,0,1,200,200,9,1}, 
					{1,200,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,200,1}, 
					{1,200,200,200,200,0,200,0,200,0,200,0,200,0,200,200,200,200,1}, 
					{1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1}, 
					{1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1}, 
					{1,1,1,0,1,0,0,0,1,1,1,0,0,0,1,0,1,1,1}, 
					{3,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,4}, 
					{1,1,1,0,1,0,0,0,1,200,1,0,0,0,1,0,1,1,1}, 
					{1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1}, 
					{1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1}, 
					{1,200,200,200,200,0,200,0,200,0,200,0,200,0,0,200,200,200,1}, 
					{1,200,1,200,1,0,1,1,1,1,1,1,1,0,1,0,1,200,1}, 
					{1,9,200,200,1,200,200,0,0,9,0,0,200,200,1,200,200,9,1}, 
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};



float steps = 0.1f;

float xx, tmX = 0, yy, tmY = 0;
float PlayerX, PlayerY;
bool moveUP = 0, moveDOWN = 0, moveRIGHT = 0, moveLEFT = 0;
bool mR=0, mL=0, mU=0, mD=0;


bool BadajTablice(int xx, int yy, int nr)
// funkcja badajaca co w danym miejscu znajduje sie na mapie
// gdy  funkcja  rowna   sie  podawanemu  elementowi  zwraca 
// TRUE a jak nie FALSE
{
	if (mapa[xx][yy]==nr) return FALSE; else return TRUE;
}

int ilosc_star=0;
int czas=0, czas_on;
int text_p=2, ilosc_zyc=3, player_die=0;