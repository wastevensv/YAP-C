#include "postdrop.h"

char hostname[] = "https://postdrop.labs.wasv.me";

int main(int argc, char *argv[]) {
  if(argc > 1) {
    PDget(hostname, argv[1]);
  }
  return 0;
}
