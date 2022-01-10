#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
//include the header file for OMP
#include <omp.h>
#define MAX_N 16
//function to check for correct queen position
int check_acceptable(int queen_rows[MAX_N], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = i+1; j < n; j++)
        {
// two queens in the same row => not a solution!
            if (queen_rows[i] == queen_rows[j]) return 0;
// two queens in the same diagonal => not a solution!
            if (queen_rows[i] - queen_rows[j] == i - j ||
                    queen_rows[i] - queen_rows[j] == j - i)
                return 0;
        }
    }
    return 1;
}
int main(int argc, char* argv[])
{
//initialize the variables for threads
    float nThreads,thread_limit,thread_used;
    int n,temp=0;
    int max_iter = 1;
//determining the number of queens to be solved
    printf("enter the number of queens");
    scanf("%d",&n);
    double start_time, end_time;
    int number_solutions = 0;
    int get_level;
    int get_level2;
    double time;
//determine the maximum number of OpenMP threads available to the program
    thread_limit=omp_get_thread_limit();
//determine the nesting level for the parallel blocks
    get_level=omp_get_level();
    {
        int num_workers;
        int i;
        n = (argc > 1) ? atoi(argv[1]) : n;
        num_workers = (argc > 2) ? atoi(argv[2]) : 30;
        for (i = 0; i < n; i++)
        {
            max_iter *= n;
        }
    }
    /*
    get the double precision value equal to the number of seconds
    since the initial value of the operating system real-time clock
    */
    start_time = omp_get_wtime();
    int iter;
//spawns a group of threads and for divides loop iterations between the spawned threads.
    #pragma omp in parallel for
    #pragma omp master
//Threads other than the master thread will not execute the statement block associated with this construct
    {
//number of threads available in subsequent parallel region that can be adjusted by the runtime library
        omp_set_dynamic(9);
//Specifies the number of threads used by default in subsequent parallel sections
        omp_set_num_threads(4);
        printf_s("output from omp_get_dynamic %d\n",omp_get_dynamic( ));
        for (iter = 0; iter < max_iter; iter++)
        {
            int code = iter;
            int i;
            int queen_rows[MAX_N];
// the index correspond to the queen's number and the queen's column
// we only generate configurations where there's only one queen per column
            for (i = 0; i < n; i++)
            {
                queen_rows[i] = code % n;
                code /= n;
            }
            if (n<=16)
            {
                if (check_acceptable(queen_rows, n))
                {
//allows access of a specific memory location atomically to avoid race conditions
                    #pragma omp atomic
                    number_solutions++;
//identifies a section of code that must be executed by a single thread at a time
                    #pragma omp critical
                    if (number_solutions<0)
                    {
                        /*identifies a point at which the compiler ensures that all threads in a parallel region have
                        the same view of specified objects in memory*/
                        #pragma omp flush
                        get_level2=omp_get_level();//return the number of active and inactive nested parallel regions
                    }
                    else
                    {
                        printf("\n");
                        for (i = 0; i < n; i++)
                        {
                            int j;
                            for (j = 0; j < n; j++)
                            {
                                if (queen_rows[i] == j) printf("|Q");
                                else printf("| ");
                            }
                            printf("|\n");
                        }
                        printf("\n");
                    }
                }
            }
        }
    }
    /*identifies a synchronization point at which threads in a parallel region will not execute
    beyond
    the omp barrier until all other threads in the team complete all explicit tasks in the region.
    */
    #pragma omp barrier
    if (n>0 && n<16)
    {
// get end time
        end_time = omp_get_wtime();
// print results
        printf("The starting time is %d\n",&start_time);
        printf("The ending time is %d\n",&end_time);
        printf("The execution time is %g sec\n", end_time - start_time);
        printf("Number of found solutions is %d\n", number_solutions);
//number of threads in the team currently executing
        thread_used=omp_get_num_threads();
        printf("the number of thread in total = %d \n",&thread_limit);
        printf("the number of thread is used = %d \n",&thread_used);
        printf("the number of parallel region initially is %d\n", get_level);
        printf("the number of parallel region is %d", get_level2);
        time=omp_get_wtick();//returns the number of seconds between clock ticks
        printf("\ntotal time between successful clock ticks = %f ",&time);
    }
//check for invalid input
    else if (n>16)
    {
        printf("the number of queens input is not proper");
    }
    return 0;
}
