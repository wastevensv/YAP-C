#include "postdrop.h"
#include "trim.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  FILE *fh = fopen("hostname.key", "r");
  char hostname[129];
  fread(hostname, 1, 128 , fh);
  hostname[128]='\0';
  trimend(hostname);
  fclose(fh);

  FILE *fp = fopen("primary.key", "r");
  char primary[17];
  fread(primary, 1, 16 , fp);
  primary[16]='\0';
  trimend(primary);
  fclose(fp);
  
  FILE *fo = fopen("otpsecret.key", "r");
  char otpsecret[17];
  fread(otpsecret, 1, 16 , fo);
  otpsecret[16]='\0';
  trimend(otpsecret);
  fclose(fo);
  
  FILE *fu = fopen("username.key", "r");
  char username[17];
  fread(username, 1, 16 , fu);
  username[16]='\0';
  trimend(username);
  fclose(fu);

  PDinit(hostname, username, primary, otpsecret);
  if(argc > 1) {
    PDget(argv[1]);
  } else {
    PDlist();
  }
  return 0;
}
