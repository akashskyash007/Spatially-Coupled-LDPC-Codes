#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100000
#define WIDTH 100

int main(){
  long i;
  float progress = 0.0;
  int c  = 0, x=0, last_c=0;
  /**
   * Print a basic template of the progress line.
  **/
  fprintf(stderr, "%3d%% [", (int)progress);
  for (x = 0; x < c; x++){
    fprintf(stderr, "=");
  }
  for (x = c; x < WIDTH; x++){
    fprintf(stderr, " ");
  }
  fprintf(stderr, "]");
  for(i = 1; i < MAX+1; i++){
    progress = i*100.0/MAX;
    c = (int) progress;
    /**
     * Update the template on each increment in progress.
    **/
    fprintf(stderr, "\n\033[F");
    fprintf(stderr, "%3d%%", (int)progress);
    fprintf(stderr, "\033[1C");
    fprintf(stderr, "\033[%dC=", last_c);
    for (x = last_c; x < c; x++){
      fprintf(stderr, "=");
    }
    if(x<WIDTH){
      fprintf(stderr, ">");
    }
    last_c = c;
  }

  /**
   * Write a finish line.
  **/
  fprintf(stderr, "\033[EDone\n");
}
