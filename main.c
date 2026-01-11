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
    printf("I couldn't find that file :C");
    return 1;
  }

  CPUSpecs cpuspecs[6224];

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
  if (numberofcpus >= 6224) break;
  numberofcpus++;
}
  
  if (readvalues != EOF) { 
      printf("The database is not formatted correctly :C\n"); 
      return 1;
 }
  
  fclose(file);
    

    char query[100];
    printf("Enter CPU Name: ");
    scanf("%[^\n]", query);
    printf("Querying passmark.txt..\n", query);

    int i;

    for (i = 0; i < numberofcpus; i++) {
        if (strstr(cpuspecs[i].cpuname, query) != NULL) {
            printf("CPU Name: %s\n", cpuspecs[i].cpuname);
            printf("Cores: %d\n", cpuspecs[i].cores);
            printf("Single Thread Performance: %dpts\n", cpuspecs[i].single);
            printf("Multi Thread Performance: %dpts\n", cpuspecs[i].multi);
            printf("TDP: %.1fW\n", cpuspecs[i].tdp);
            printf("Socket: %s\n", cpuspecs[i].socket);
            printf("Type: %s\n", cpuspecs[i].type);
            break;
      }
    }       
    
    return 0;
     
  }

