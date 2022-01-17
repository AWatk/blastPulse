#include "connection.hpp"
#include <unistd.h>

int main(int argc, char * argv[])
{

  int port = 5555;
  std::string IP = "127.0.0.1"; //send to self via loopback address
  //std::string IP = "255.255.255.255";

  IPV4_Connection conn;

  conn.serverPort = port;
  conn.serverIP = IP;

  fprintf(stdout, "Initializing udp connection (0 is success): %d\n",conn.Initialize(false));

  std::string buff = "1, 5, 0.004, 0.008, 0.009";

  fprintf(stdout, "String to send (interval,numshots,upTime,holdTime,downTime): %s\n", buff.c_str());

  int sentBytes = conn.Send(buff.c_str(), buff.length());

  if(errno == 0)
      {
           fprintf(stdout, "Successfully sent the string!\nTotal bytes sent: %d\n", sentBytes);
       }
  else
       {
           fprintf(stdout, "Send error!\nErrno value: %d\n\nErrno is a standard value that can be googled.\n", errno);
       }

  return 0;
}
