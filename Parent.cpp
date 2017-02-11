

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
#include <cstring>
#include <memory>
#include <sstream>





using namespace std;

int main(int argc, char **argv){

  cout << "Parent Executing" << endl;
  pid_t parentPID = getpid();
  cout << "Parent PID: " << parentPID << endl;

  //Making a pipe
  int fd[2];
  int READ = 0;
  int WRITE = 1;
  pipe(fd);
  char command[] = "LISTALL";
  char readbuf[sizeof(command)];

  write(fd[WRITE], command, sizeof(command));


  //forking child process
  pid_t childPID = fork();
  if (childPID < 0)
  {
    perror("fork() error");
  }
  else if(childPID == 0)
  {
    cout << "Child Executing" << endl;
    read(fd[READ], readbuf, sizeof(readbuf));
    cout << "Child recieved: " << readbuf << " from pipe"<< endl;

    pid_t parentPID = getppid();
    cout << "Parent PID from child: " << parentPID << endl;
    pid_t childPID = getpid();
    cout << "Child PID from child: " << childPID << endl;

    string PID_String = to_string(childPID) + " " + to_string(parentPID);
    cout << PID_String << endl;

    char PID_char[20];
    strcpy(PID_char, PID_String.c_str());

    write(fd[WRITE],PID_char , sizeof(PID_char));


  }
    sleep(1);

    read(fd[READ], readbuf, sizeof(readbuf)+20);
    cout << "Parent recieved: " << readbuf << " from pipe"<< endl;

    cout << "Parent Killing ChildPID" << endl;
    string PID_String(readbuf);
    stringstream  stream;
    stream << PID_String;
    string firstWord;
    stream >> firstWord;
    stringstream convert(firstWord);
    int firstPID;
    convert >> firstPID;

    if (kill(firstPID, SIGKILL) == -1){
      perror("Kill failed");
    }


  return 0;
}
