#include "postdrop.h"
char hostname[] = "https://postdrop.labs.wasv.me";
int main(int agrc, char *argv[]) {
  PDget(hostname, "b");
  return 0;
}
