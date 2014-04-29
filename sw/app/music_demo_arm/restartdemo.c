#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char **argv)
{
  pid_t child_id;
  
  while(1)
  {
    child_id = vfork();
    if(child_id<0)
    {
      printf("Create child process wrong!\n");
      exit(0);
    }else if(child_id==0)
    {
      execl("/music/music_demo","music_demo","-qws",NULL);
    }else if(child_id>0)
	{
	 wait();
	}
       
  }
  exit(0);
}

