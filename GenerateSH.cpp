//To generate link.sh and codevillage.sh files

#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>

using namespace std;

int main ()
{
    ofstream file1;
    ofstream file2;
    string currentDir;
    char cwd[2048];
    if(getcwd(cwd, sizeof(cwd))!=NULL)
    {
        currentDir=cwd;
        //cout<<currentDir;
        file1.open ("CodeRunner.sh");
        file1 << "until "+currentDir+"/link.sh; do \n echo \" CodeRunner crashed with exit code $?.  Respawning.. \" >&2 \n sleep 1 \n done";
        file1.close();
        file2.open ("link.sh");
        file2 << currentDir+"/main -q";
        file2.close();
    }
    else
        perror("getcwd() Status");
  return 0;
}
