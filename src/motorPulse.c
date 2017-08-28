#include <rc_usefulincludes.h>
#include <roboticscape.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

  //time in milliseconds
  double upTime = 4;
  double holdTime = 8;
  double downTime = 9;


  int m2u = 1000;
  double overhead = 0.4;
  double upMilli = (int)((upTime - overhead) * m2u);
  double holdMilli = (int)((holdTime - overhead) * m2u);
  double downMilli = (int)((downTime - overhead) * m2u);
    
  if(rc_initialize())
    {
      fprintf(stderr, "Could not run rc_init");
    }

  fprintf(stdout, "Test\n");

  if(rc_enable_motors())
    {
      fprintf(stdout, "RC_Enable");
    }

  if(rc_set_motor(1, 1.0))
    {
      fprintf(stdout, "Set Motor");
    }

  usleep(upMilli);

  rc_set_motor(1,0);

  usleep(holdMilli);
  
  rc_set_motor(1,-1.0);

  usleep(downMilli);

  rc_disable_motors();
  
  return 0;
}
