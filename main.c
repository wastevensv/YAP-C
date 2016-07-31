#include "postdrop.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char hostname[] = "https://postdrop.labs.wasv.me";

  FILE *fp = fopen("primary.key", "r");
  char primary[17];
  fread(primary , 1, 16 , fp);
  primary[16]='\0';
  fclose(fp);
  
  FILE *fo = fopen("otpsecret.key", "r");
  char otpsecret[17];
  fread(otpsecret, 1, 16 , fo);
  primary[16]='\0';
  fclose(fo);
  

  PDinit(hostname, "wasv", primary, otpsecret);
  if(argc > 1) {
    PDget(argv[1]);
  } else {
    PDlist();
  }
  return 0;
}
