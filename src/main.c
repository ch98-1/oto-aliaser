/* c standard libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//max length of character readable per line
#define MAX_CHAR 4096


//dictionary
typedef struct dictionary_entry
{
  char* in; //input of dictionary
  char* out; //output of dictionary
}dict_e;

typedef struct dictionary
{
  dict_e* d; //dictionary list
  unsigned long int l; //length of dictionary
}dict;


dict add_entry(dict d, const char* in, const char* out); //add entry in to dictionary

dict read_dict(const char* file); //build dictionary

const char* find(dict d, const char* in); //find item in dictionary. returns null if not found

int free_dict(dict); //clean up dictionary



//oto reading and writing

typedef struct oto_entry
{
  char* a; //filename without .wav
  char* b; //aliase
  char* c; //rest of the mess
}oto_e;

typedef struct oto
{
  oto_e* o; //oto list
  char platform;
  char mac_header[MAX_CHAR];
  unsigned long int l; //length of oto
}oto;


oto add_oto(oto o, const char* a, const char* b, const char* c); //add entry in to oto. a is filename without .wav, b is aliase, c is the rest

oto read_oto(const char* file, char platform); //read oto file

int write_oto(const char* file, oto o); //write oto file

int free_oto(oto o); //clean up oto




//other
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
  dict d = read_dict(argv[2]);

  //read input file
  oto o = read_oto(argv[3], platform);


  //replace aliase
  if (mode == 'a'){
    unsigned long int i;
    for(i = 0; i < o.l; i++){ //add based on file name for each entry
      const char* tmp = find(d, o.o[i].a);
      if(tmp != NULL){
        strcpy(o.o[i].b, tmp);
      }
    }
  }
  else{
    unsigned long int i;
    for(i = 0; i < o.l; i++){ //replace based on existing aliase for each entry
      const char* tmp = find(d, o.o[i].b);
      if(tmp != NULL){
        strcpy(o.o[i].b, tmp);
      }
    }
  }

  //write output file
  write_oto(argv[4], o);

  //free all
  free_dict(d);
  free_oto(o);

  //exit
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

//add entry in to dictionary
dict add_entry(dict d, const char* in, const char* out){
  d.l++;
  if (d.l == 1){ //allocate new memory for new entry in dictionary
    d.d = malloc(sizeof(dict_e));
  }
  else{
    d.d = realloc(d.d, sizeof(dict_e)*d.l);
  }

  d.d[d.l-1].in = malloc(sizeof(char)*(strlen(in)+1)); //create in
  strcpy(d.d[d.l-1].in, in);//copy in

  d.d[d.l-1].out = malloc(sizeof(char)*(strlen(out)+1)); //create out
  strcpy(d.d[d.l-1].out, out);//copy out

  return d;
}

//build dictionary
dict read_dict(const char* file){
  dict d;
  d.l = 0;
  FILE* f_csv = fopen(file, "r");

  char line[MAX_CHAR];//each line of the file
  char in[MAX_CHAR];//in
  char out[MAX_CHAR];//out
  while(fgets(line, MAX_CHAR, f_csv) != NULL){
    strcpy(in, strtok (line,","));
    strcpy(out, strtok (NULL,",\r\n"));
    d = add_entry(d, in, out);
  }
  fclose(f_csv);
  return d;
}

//find item in dictionary. returns null if not found
const char* find(dict d, const char* in){
  unsigned long int i;
  for(i = 0; i < d.l; i++){ //search though each text entry
    if (!strcmp(d.d[i].in, in)){
      return d.d[i].out;
    }
  }
  return NULL;
}

//clean up dictionary
int free_dict(dict d){
  unsigned long int i;
  for(i = 0; i < d.l; i++){ //free each text entry
    free(d.d[i].in);
    free(d.d[i].out);
  }
  free(d.d);
  return 0;
}


//add entry in to oto. a is filename without .wav, b is aliase, c is the rest
oto add_oto(oto o, const char* a, const char* b, const char* c){
  o.l++;
  if (o.l == 1){ //allocate new memory for new entry in dictionary
    o.o = malloc(sizeof(oto_e));
  }
  else{
    o.o = realloc(o.o, sizeof(oto_e)*o.l);
  }

  o.o[o.l-1].a = malloc(sizeof(char)*(strlen(a)+1)); //create a
  strcpy(o.o[o.l-1].a, a);//copy a

  o.o[o.l-1].b = malloc(sizeof(char)*(strlen(b)+1)); //create b
  strcpy(o.o[o.l-1].b, b);//copy b

  o.o[o.l-1].c = malloc(sizeof(char)*(strlen(c)+1)); //create c
  strcpy(o.o[o.l-1].c, c);//copy c

  return o;
}

//read oto file
oto read_oto(const char* file, char platform){
  oto o;
  o.l = 0;
  o.platform = platform;
  FILE* f_oto = fopen(file, "r");
  if (platform == 'm'){
    fgets(o.mac_header, MAX_CHAR, f_oto);
  }
  char line[MAX_CHAR];//each line of the file
  char a[MAX_CHAR];//a
  char b[MAX_CHAR];//b
  char c[MAX_CHAR];//c
  while(fgets(line, MAX_CHAR, f_oto) != NULL){
    strcpy(a, strtok (line,"."));
    strtok (NULL,"=");
    strcpy(b, strtok (NULL,","));
    strcpy(c, strtok (NULL,"\r\n"));

    o = add_oto(o, a, b, c);
  }
  fclose(f_oto);
  return o;
}

//write oto file
int write_oto(const char* file, oto o){
  FILE* f_oto = fopen(file, "w");
  if (o.platform == 'm'){
    fprintf(f_oto, "%s", o.mac_header);
  }
  unsigned long int i;
  for(i = 0; i < o.l; i++){ //print each text entry
    fprintf(f_oto, "%s.wav=%s,%s\n", o.o[i].a, o.o[i].b, o.o[i].c);
  }
  return 0;
}

//clean up oto
int free_oto(oto o){
  unsigned long int i;
  for(i = 0; i < o.l; i++){ //free each text entry
    free(o.o[i].a);
    free(o.o[i].b);
    free(o.o[i].c);
  }
  free(o.o);
  return 0;
}
