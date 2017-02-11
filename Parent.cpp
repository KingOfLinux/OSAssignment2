

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

  cout << "Parent Executing" << endl;
  pid_t parentPID = getpid();
  cout << "Parent PID: " << parentPID << endl;

  pid_t childPID = fork();
  if (childPID < 0)
  {
    perror("fork() error");
  }
  else if(childPID == 0)
  {
    if (execl("Child", "Child", "LISTALL", NULL) == -1){
      perror("child exec() error");
  }
    sleep(2);
  }


  return 0;
}
