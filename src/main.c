/* c standard libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int usage(char* program); //print usage

int main(int argc, char* argv[]) {
  if (argc != 5 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "-hw") || !strcmp(argv[1], "-hm")) { //basic argument number check
    usage(argv[0]);
    exit(EXIT_SUCCESS);
  }

  char mode, platform; //mode and platform

  int sl = strlen(argv[1]); //parse options
  if (sl == 2){
    mode = argv[1][1];
    platform = 'w';
  }
  else if (sl == 3){
    mode = argv[1][1];
    platform = argv[1][2];
  }
  else{
    usage(argv[0]);
    exit(EXIT_SUCCESS);
  }

  if( mode == 'a'){ //check mode
    printf("Working in add mode ");
  }
  else if (mode == 'r'){
    printf("Working in replacement mode ");
  }
  else {
      usage(argv[0]);
      exit(EXIT_SUCCESS);
  }

  if( platform == 'w'){ //check platform
    printf("for Windows\n");
  }
  else if (platform == 'm'){
    printf("for Mac\n");
  }
  else {
      usage(argv[0]);
      exit(EXIT_SUCCESS);
  }


  //read dictionary

  //read input file

  //replace aliase

  //write output file




  exit(EXIT_SUCCESS);
}

//print out the usage
int usage(char* program) {
  printf("Usage:\n"
  "%s [options][platform] <dictionary file> <input oto file> <output oto file>\n\n"
  "options:\n"
  "-a       Add aliase from filename\n"
  "-r       Replace aliase using existing aliase\n"
  "-h       Print this help message\n\n"
  "platforms:\n"
  "m        Mac\n"
  "w        Windows\n"
  "If no platform is given, windows is assumed\n\n"
  "example:\n"
  "%s -aw hira2roma.csv oto.ini edited-oto.ini\n", program, program);
  return 0;
}
