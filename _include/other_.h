int Random(int min,int max)
{
	int i;
	i=rand()%(max-min+1)+min;
	return i;
}

void randomize()
{
	tm timer;
	int i=0,a=0,b;
	_getsystime(&timer);
	i=timer.tm_sec+100;
	while (a!=i)
	{
		b=rand()%100;
		a++;
	}
}