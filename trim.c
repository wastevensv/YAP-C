#include <string.h>

void trimbegin(char *src) {
  int offset = 0;
  for(int i=0; i < strlen(src)-1; i++) {
    if(src[i] < 127 && src[i] > 32) {
      break;
    } else {
      offset++;
    }
  }
  int i=0;
  for(; i < (strlen(src)-1)-offset; i++) {
    src[i] = src[i+offset];
  }
  src[i] = '\0';
}

void trimend(char *src) {
  for(int i=strlen(src)-1; i >= 0; i--) {
    if(src[i] < 127 && src[i] > 32) {
      return;
    } else {
      src[i] = 0;
    }
  }
}
