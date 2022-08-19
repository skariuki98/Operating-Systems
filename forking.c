/*STELLA M KARIUKI
Using child processes to increment a value stored in the shared memory
The parent process should wait for all processes to terminate
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

/* change the key number */
#define SHMKEY ((key_t) 7890)


typedef struct
{
  int value;
} shared_mem;

shared_mem *total;




/*----------------------------------------------------------------------*
 * This function increases the value of shared variable "total"
 *  by one all the way to 100000
 *----------------------------------------------------------------------*/

void process1 ()
{
  int k = 0;

  while (k < 100000)
    {
      k++;
      total->value = total->value + 1;
    }
  printf ("From process1 total = %d\n", total->value);
}


/*----------------------------------------------------------------------*
 * This function increases the value of shared memory variable "total"
 *  by one all the way to 200000
 *----------------------------------------------------------------------*/

void process2 ()
{
  int k = 0;

  while (k < 100000)
    {
      k++;
      total->value = total->value + 1;
    }

  printf ("From process2 total = %d\n", total->value);

}
/*----------------------------------------------------------------------*
 * This function increases the value of shared memory variable "total"
 *  by one all the way to 300000
 *----------------------------------------------------------------------*/
void process3(){

   int k =0;

   while (k<100000){
      k++;
      total->value = total->value + 1;
   }
   printf ("From process3 total = %d\n", total->value);

}
/*----------------------------------------------------------------------*
 * This function increases the value of shared memory variable "total"
 *  by one all the way to 500000
 *----------------------------------------------------------------------*/
void process4(){
   int k=0;

   while (k<200000){
      k++;
      total->value = total->value + 1;
   }
   printf ("From process4 total = %d\n", total->value);

}

/*----------------------------------------------------------------------*
 * MAIN()
 *----------------------------------------------------------------------*/

main()
{
  int   shmid;
  int   pid1;
  int   pid2;
  int   pid3;
  int   pid4;
  int   ID;
  int	status=0;
  

  char *shmadd;
  shmadd = (char *) 0;

/* Create and connect to a shared memory segment*/

  if ((shmid = shmget (SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
      perror ("shmget");
      exit (1);
    }


 if ((total = (shared_mem *) shmat (shmid, shmadd, 0)) == (shared_mem *) -1)
    {
      perror ("shmat");
      exit (0);
    }

  /* Initialize shared memory to 0 */
  total->value = 0;

/* Create 4 child processes. Each of them run its own program*/

  if ((pid1 = fork()) == 0)
    process1(); //child process 1
  if ((pid1 != 0) && (pid2 = fork()) == 0){
    
    process2(); //child process 2
  }
 /*create two more children*/
  if ((pid1 != 0) && (pid2 != 0) && (pid3 = fork())==0)
  {
      
      process3(); //child process 3
  }

  if ((pid1 != 0) && (pid2 != 0) && (pid3 != 0) && (pid4 = fork())==0)
  {
      
      process4(); //child process 4
  }

  if(pid1==-1 || pid2==-1 || pid3==-1 ||pid4==-1){
   printf("Forking Failed"); //failed process creation
  }

  if((pid1!=0)&&(pid2!=0)&&(pid3!=0)&&(pid4!=0)){ //defines what parent process should do
        //wait for all process individually
         waitpid(pid1, NULL, 0);
         waitpid(pid2, NULL, 0);
         waitpid(pid3, NULL, 0);
         waitpid(pid4, NULL, 0);
         //print when exited
	       ID = pid1;
         printf("Process with ID %d has exited.\n", ID); //if terminated successfully
	       ID = pid2;
          printf("Process with ID %d has exited.\n", ID); //if terminated successfully
          ID = pid3;
         printf("Process with ID %d has exited.\n", ID); //if terminated successfully
         ID = pid4;
         printf("Process with ID %d has exited.\n", ID); //if terminated successfully
         
         

   /* The parent process releases the shared memory */
   if ((shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0)) == -1)
	{
	  perror ("shmctl");
	  exit (-1);
	}
   printf ("\t\t  End of Program.\n");

   }
}

/***** Note:  loop for parent to wait for child processes to finish and print ID of each child*****/


