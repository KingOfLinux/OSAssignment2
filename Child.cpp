#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <string>

#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char **argv){



  if(argc != 2)
  {
    cout << "Missing argument"<< endl;
    exit(-1);
  }else

  cout << "Child Executing" << endl;
  pid_t childPID = getpid();
  cout << "Parent PID: " << childPID << endl;
  string command = argv[1];

  if (command.compare("LISTALL") == 0){
    pid_t commandPID = fork();
    if (execl("/bin/ps", "ps", "-aux", NULL) ==-1)
    {
      perror("Child exec() error");
    }
    cout << "ps PID: " << commandPID << endl;

  }else
    cout << "no command call " << command << endl;


  return 0;
}
