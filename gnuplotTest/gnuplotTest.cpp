#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Note that gnuplot binary must be on the path
// and on Windows we need to use the piped version of gnuplot
// http://stackoverflow.com/questions/9349538/gnuplot-c-from-windows-command-window-opens-and-closes
// http://stackoverflow.com/questions/8521824/how-to-draw-objects-rect-from-a-file
#ifdef WIN32
    #define GNUPLOT_NAME "pgnuplot -persist"
#else 
    #define GNUPLOT_NAME "gnuplot"
#endif

int main() 
{
    #ifdef WIN32
        FILE *pipe = _popen(GNUPLOT_NAME, "w");
    #else
        FILE *pipe = popen(GNUPLOT_NAME, "w");
    #endif

    if (pipe != NULL)
    {

        fprintf(pipe, "unset key; unset tics; unset border\n");         // set the terminal
        fprintf(pipe, "set term wx\n");         // set the terminal
		 fprintf(pipe, "set object 1 rect from 0,0 to 1,1 fc lt 2\n");
         fprintf(pipe, "set object 2 rect from 0,1 to 1,2 fc lt 2\n");  
         fprintf(pipe, "set object 3 rect from 1,1 to 2,2 fc lt 2\n");  
         fprintf(pipe, "set object 4 rect from 1,0 to 2,1 fc lt 2\n");  
        fprintf(pipe, "plot [0:5] x lw 0\n");       
        //fprintf(pipe, "plot sin(x)\n"); // plot type
        //fprintf(pipe, "pause 2\n"); // plot type
        //fprintf(pipe, "plot x\n"); // plot type
        //fprintf(pipe, "plot '-' with lines\n"); // plot type
        //for(int i = 0; i < 10; i++)             // loop over the data [0,...,9]
        //    fprintf(pipe, "%d\n", i);           // data terminated with \n
        //fprintf(pipe, "%s\n", "e");             // termination character
        fflush(pipe);                           // flush the pipe

        // wait for key press
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();


        fflush(pipe);                           // flush the pipe

        // wait for key press
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        #ifdef WIN32
                _pclose(pipe);
        #else
                pclose(pipe);
        #endif
    }
    else
        std::cout << "Could not open pipe" << std::endl; 
return 0;
}