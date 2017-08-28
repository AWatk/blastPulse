#include "connection.hpp"
#include <unistd.h>
#include <iostream>
extern "C"
{
#include <rc_usefulincludes.h>
#include <roboticscape.h>
}


void startBlast(double interval, int numShots, double upTime, double holdTime, double downTime)
{
  int sec2usec = 1000000;
  double overhead = 400;
  double upU = (int)(upTime * sec2usec - overhead);
  double holdU = (int)(holdTime * sec2usec - overhead);
  double downU = (int)(downTime * sec2usec - overhead);
  double intervalU = (int)(interval * sec2usec - overhead);
  

  if(rc_enable_motors())
    {
      fprintf(stdout, "RC_Enable");
    }


  for(int i = 0; i < numShots; i++)
    {
      rc_set_motor(1, 1.0);
      
      usleep(upU);
      
      rc_set_motor(1,0);
      
      usleep(holdU);
      
      rc_set_motor(1,-1.0);
      
      usleep(downU);
      
      rc_set_motor(1,0);
      
      usleep(intervalU);
    }

  rc_disable_motors();

}


int main(int argc, char * argv[])
{

  int port = 5555;
  std::string IP = "0.0.0.0";

  IPV4_Connection conn;

  conn.serverPort = port;
  conn.serverIP = IP;

  fprintf(stdout, "%d\n",conn.Initialize(true));

  char buff[100];

  if(rc_initialize())
    {
      fprintf(stderr, "Could not run rc_init");
    }

  
  while(rc_get_state() != EXITING)
    {
      double interval = 0;
      double numShots = 0;
      double upTime = 0;
      double holdTime = 0;
      double downTime = 0;

      
      if(conn.Receive(buff,100) > 0)
	{

	  char * pch;

	  pch = strtok(buff, ",");
	  if(pch != NULL)
	    {
	      interval = atof(pch);
	    }

	  pch = strtok(NULL, ",");

	  if(pch != NULL)
	    {
	      numShots = atoi(pch);
	    }

	  pch = strtok(NULL, ",");

	  if(pch != NULL)
	    {
	      upTime = atof(pch);
	    }

	  pch = strtok(NULL, ",");

	  if(pch != NULL)
	    {
	      holdTime = atof(pch);
	    }

	  pch = strtok(NULL, ",");

	  if(pch != NULL)
	    {
	      downTime = atof(pch);
	    }

	  if(interval && numShots && upTime && holdTime && downTime)
	    {
	      fprintf(stdout, "%f, %f, %f, %f, %f\n", interval, numShots, upTime, holdTime, downTime);
	      startBlast(interval, numShots, upTime, holdTime, downTime);
	    }
	  else
	    {
	      fprintf(stdout, "Read Error");
	    }
	  	    
	}

      
    }

  rc_cleanup();
  

  return 0;
}
