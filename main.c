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

  printf("\n[ PassmarkSearcher by Eleanor (decentcarp) ]\n\n");
  FILE *file;

  file = fopen("passmark.txt", "r");

  if (file == NULL) {
    printf("I couldn't find the specified database file :C");
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
      printf("The database file is not formatted correctly :C\n"); 
      return 1;
 }
  
  fclose(file);
    

    char query[100];
    printf("Enter CPU Name (approximate or exact): ");
    scanf("%[^\n]", query);

    int i;
    int i2 = 0; 
    int i3;
  
    #define MAX_RESULTS 10
    int i4[MAX_RESULTS];
    char results[MAX_RESULTS][256];

    for (int i5 = 0; i5 < MAX_RESULTS; i5++) i4[i5] = -1;

    for (i = 0; i < numberofcpus; i++) {
      if (strcasestr(cpuspecs[i].cpuname, query) != NULL) {
        if (i2 < MAX_RESULTS) {
          strcpy(results[i2], cpuspecs[i].cpuname);
          printf("%d: %s\n", i2 + 1, cpuspecs[i].cpuname);
          i4[i2] = i;
          i2++;
        }
        continue;
      } 
      if (i2 == 0 && i == numberofcpus - 1) {
          printf("No CPU matches '%s' :C\n", query);
          return 1;
      }
    }

  printf("\nPlease select a CPU: ");
  scanf("%d", &i3);

  int i6 = i4[i3 - 1];
  printf("\nCPU Name: %s\n", cpuspecs[i6].cpuname);
  printf("Cores: %d\n", cpuspecs[i6].cores);
  printf("Single Thread Performance: %dpts\n", cpuspecs[i6].single);
  printf("Multi Thread Performance: %dpts\n", cpuspecs[i6].multi);
  printf("TDP: %.1fW\n", cpuspecs[i6].tdp);
  printf("Socket: %s\n", cpuspecs[i6].socket);
  printf("Type: %s\n", cpuspecs[i6].type);

  return 0;
}
