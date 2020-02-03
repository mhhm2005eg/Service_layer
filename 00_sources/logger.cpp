/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "configurations.h"

/*void logger(char* file, const char* message) {
   FILE * fp; 
   time_t now;
   char* tag = "log";
   time(&now);
   fp = fopen (file, "w+");
   fprintf(fp, "%s [%s]: %s\n", ctime(&now), tag, message);
   fclose(fp);
}*/

#ifdef DEBUG
void logger(const char* tag, const char* message) {
   FILE * fp; 
   time_t now;
   time(&now);

   fp = fopen (log_file_name, "a");

    int            ms; // Milliseconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    
    
   char *loc_time = ctime(&now);
   loc_time[strlen(loc_time) - 1] = '\0';
   fprintf(fp, "%s %03d [%s]: %s\n", loc_time, ms, tag, message);
   fclose(fp);
}
#endif