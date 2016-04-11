class BLOCK
{

public:

float xx, tmX, yy, tmY;
float PlayerX, PlayerY;
bool moveUP, moveDOWN, moveRIGHT, moveLEFT;
bool mR, mL, mU, mD;
int los, t;	
bool stoi;

int Ghost(float x, float y, int t);

};

BLOCK enemy[4];