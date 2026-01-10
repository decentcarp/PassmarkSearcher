#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char cpuname[256];
    int cores;
    int single;
    int multi;
    float tdp;
    char socket[256];
    char type[256];
} CPUSpecs;

int main(void) {

  FILE *file;

  file = fopen("passmark.txt", "r");

  if (file == NULL) {
    printf("broken :C");
    return 1;
  }

  CPUSpecs cpuspecs[7000];

  int readvalues = 0;
  int numberofcpus = 0;

  while ((readvalues = fscanf(file,
         "%255[^,],%d,%d,%d,%f,%255[^,],%255[^\r\n]%*[\r\n]",
         cpuspecs[numberofcpus].cpuname,
         &cpuspecs[numberofcpus].cores,
         &cpuspecs[numberofcpus].multi,
         &cpuspecs[numberofcpus].single,
         &cpuspecs[numberofcpus].tdp,
         cpuspecs[numberofcpus].socket,
         cpuspecs[numberofcpus].type)) == 7) {
  if (numberofcpus >= 7000) break;
  numberofcpus++;
}
  
  if (readvalues != EOF) { 
      printf("meow"); 
      return 1;
 }
  
  fclose(file);
    
    char query[100];
    scanf("%[^\n]", query);
    printf("Looking for %s\n", query);

    int i;

    for (i = 0; i < 6222; i++) {
        if (strcmp(cpuspecs[i].cpuname, query) == 0) {
            printf("CPU Name: %s\n", cpuspecs[i].cpuname);
            printf("Cores: %d\n", cpuspecs[i].cores);
            printf("Single Thread Performance: %d\n", cpuspecs[i].single);
            printf("Multi Thread Performance: %d\n", cpuspecs[i].multi);
            printf("TDP: %.2fW\n", cpuspecs[i].tdp);
            printf("Socket: %s\n", cpuspecs[i].socket);
            printf("Desktop/Mobile: %s\n", cpuspecs[i].type);
            break;
        }
    }

  return 0;
}