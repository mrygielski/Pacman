float DiffTime,FPS;
bool  framerate_limit = true;
float framerate;
float Time2,Time1;

inline GLfloat ABS(GLfloat A)
{
  if (A < 0)
  A = -A; 
  return A;
}

struct
{
  __int64       frequency;          
  GLfloat            resolution;         
  unsigned long mm_timer_start;     
  
  unsigned long mm_timer_elapsed;    
  bool   performance_timer;    
  
  __int64       performance_timer_start;    
  __int64       performance_timer_elapsed;
} timer;

inline void TimerInit(void)
{
     memset(&timer, 0, sizeof(timer));   
     if (!QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency))
     {
          timer.performance_timer = FALSE;          
          timer.mm_timer_start = timeGetTime();     
          timer.resolution  = 1.0f/1000.0f;         
          timer.frequency   = 1000;                 
          timer.mm_timer_elapsed = timer.mm_timer_start;
     }
     else
     {
          QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
          timer.performance_timer   = TRUE;    
          timer.resolution    = (GLfloat) (((double)1.0f)/((double)timer.frequency));
          timer.performance_timer_elapsed = timer.performance_timer_start;
     }
}

inline GLfloat TimerGetTime()
{
     __int64 time;                                  
     if (timer.performance_timer)           
     {
          QueryPerformanceCounter((LARGE_INTEGER *) &time); 
          return ( (GLfloat) ( time - timer.performance_timer_start) * timer.resolution)*1000.0f;
     }
     else
     {
          return ( (GLfloat) ( timeGetTime() - timer.mm_timer_start) * timer.resolution)*1000.0f;
     }
}


void Draw_FPS()
{
	if (framerate_limit)
	{
	Time2 = TimerGetTime()/1000;
    DiffTime = ABS(Time2-Time1);
 	while (DiffTime < 0.02) 
    {
			Time2 = TimerGetTime()/1000;
			DiffTime = ABS(Time2-Time1);				
	}	
    Time1 = TimerGetTime()/1000;     
    FPS = 1/(DiffTime);
	}
}