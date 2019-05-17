#include "connection.hpp"
#include <unistd.h>
#include <iostream>

#include <robotcontrol.h>

int status;

//conversion from second to useconds
int sec2usec = 1000000;

//the approximate overhead in useconds it takes between writing a motor command and usleeping
double overhead = 400;

//the time in useconds to hold the solenoid with a positive voltage
double upU;

//the time in useconds to hold teh solenoid at neutral voltage
double holdU;

//the time in useconds to hold the solenoid at negative voltage to close it
double downU;

//the time in useconds between blasts
double intervalU;


void startBlast(double interval, int numShots, double upTime, double holdTime, double downTime)
{

  fprintf(stderr, "In startBlast\n");
  if(!status){
    fprintf(stderr, "Turning on Red LED\n");
    rc_led_set(RC_LED_RED,1);
  }

  upU = (int)(upTime * sec2usec - overhead);
  holdU = (int)(holdTime * sec2usec - overhead);
  downU = (int)(downTime * sec2usec - overhead);
  intervalU = (int)(interval * sec2usec - overhead);



  for(int i = 0; i < numShots; i++)
    {
      rc_led_set(RC_LED_USR3, 1);
      fprintf(stderr, "Motor Set HIGH Status: %d\n", rc_motor_set(0, 0.8));
      
      usleep(upU);

      fprintf(stderr, "Motor Set NEUTRAL Status: %d\n",rc_motor_set(0, 0));
      
      usleep(holdU);
      
      fprintf(stderr, "Motor Set LOW Status: %d\n",rc_motor_set(0, -0.8));
      
      usleep(downU);
      
      fprintf(stderr, "Motor Set NEUTRAL Status: %d\n",rc_motor_set(0, 0));

      rc_led_set(RC_LED_USR3, 0);
      
      usleep(intervalU);
      
    }

  fprintf(stderr,"Exiting startBlast\n");
  rc_led_set(RC_LED_RED,0);

}


int main(int argc, char * argv[])
{
  //  rc_enable_signal_handler();
  fprintf(stderr, "Preparing to Initialize Motors.\n");
  status = rc_motor_init();
  fprintf(stderr, "Motor Init Status: %d\n", status);


  int port = 5555;
  std::string IP = "0.0.0.0";

  IPV4_Connection conn;

  conn.serverPort = port;
  conn.serverIP = IP;

  fprintf(stderr, "UDP Connection Status %d\n",conn.Initialize(true));

  char buff[100];

  
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

	  if((interval >= 0)
	     && (numShots >= 0)
	     && (upTime >= 0)
	     && (holdTime >=0)
	     && (downTime >=0))
	    {
	      fprintf(stderr, "%f, %f, %f, %f, %f\n", interval, numShots, upTime, holdTime, downTime);
	      startBlast(interval, numShots, upTime, holdTime, downTime);
	    }
	  else
	    {
	      fprintf(stderr, "Read Error");
	    }
	  	    
	}
      
    }

  status = rc_motor_cleanup();
  fprintf(stderr, "Motor Status on Exit: %d\n", status);

  return 0;
}
