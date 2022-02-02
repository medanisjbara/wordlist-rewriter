#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/* The smaller you make these files the less ram this program will need. */
/* The downside ofcourse is the restrictions. */
#define FNL 1000	//filename length
#define MRL 120		//Maximum length of any given line in a file

/* The more the better, but not too much. */
#define WBS 2000		//Writing buffer size

bool nllException(char * line);
bool minlenExeption(char * line);
bool maxlenExeption(char * line);
bool nonumsExeption(char * line);
bool exB, WBCF, exclude = false;

bool (*exceptions[4]) (char * line);

char infile[FNL], outfile[FNL], exfile[FNL], ess[MRL];
int minlen, maxlen, nonums, NLL[45], NLLJ=0, NE=0, SB, CT=0;

void parse(int argc,char const *argv[]);
void gen();

int main(int argc, char const *argv[]){
    if (argc<2){
        printf("rewrite: you must specify a worldlist file\n");
        printf("Try 'rewrite -h' for more information.\n");
        exit(1);
    }
    parse(argc,argv);
    gen();
    return 0;
}


bool isnumeric(char const * ch){
	for (int i=0; ch[i]!='\0'; i++){
		if(! isdigit(ch[i])){
			return false;
		}
	}
	return true;
}

void strip(char * input, char * output, bool (*exceptions[4]) (char * line)){
	if (! NE){
        printf("\n\n No option specified, exiting\n\n");
        exit(0);
    }
    char content[MRL*(WBS+1)];
	bool clear = true;
	
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *in_f, *out_f;
	
	if((in_f = fopen(input,"r")) == NULL){
		printf("Error reading the input file\n");
		exit(1);
	}

    if((out_f = fopen(output,"w")) == NULL){
        printf("Error creating the output file\n");
        exit(1);
    }

	while ((read = getline(&line, &len, in_f)) != -1) {

        for (int i=0; line[i]!='\n'; i++){
            ess[i]=line[i];
            SB=i;
        }
        ess[SB+1]='\0';
        exB = false;        //exception buffer
        for (int i=0; i<NE; i++){
            if ((*exceptions[i])(ess)){
                exB = true;
                break;
            }
        }
        if (exB){ continue; }
        
        for (int i=0; line[i]!='\0'; i++){
            content[CT+i]=line[i];
        }
        CT+=strlen(line);               //Content tracker
        WBCF = false;       //Write buffer clear flag
        if (CT>WBS*MRL){
            content[CT]='\0';
            fputs(content,out_f);
            CT=0;
            WBCF = true;
            printf(".");
        }
    }
    if (! WBCF){
        content[CT]='\0';
        fputs(content,out_f);
    }
    printf("done\n");

	fclose(in_f);
    fclose(out_f);
}

void help(){
    printf("USAGE: rewrite [-i] <input> [OPTIONS] \n\
\n\
 OPTIONS:\n\
\n\
  -o FILE       specify output file. generated wordlist will be saved to FILE\n\
                ex: -o wordlist.txt   will save words to the file wordlist.txt\n\
                if the output file is not specified, the output will be written\n\
                to input-rewritten\n\
\n\
  -e FILE       specify an exclude file. everything on the exclude file will not\n\
                be shown in the output file\n\
\n\
\n\
  -min MIN      set minimum word length to MIN (number)\n\
  -max MAX      set maximum word length to MAX (number)\n\
\n\
  -nn           numbers (?d)*\\n will not be allowed\n\
  -nnl LEN      numbers (?d)\\{L}\\n will be allowed\n\
                ex: -nnl 8    all numeric 8 digit numbers won't pass\n\
                ex: -nnl 8 9  all numeric 8 & 9 digit numbers won't pass\n\
\n\
                \n");
}

void parse(int argc, char const *argv[]){
    // infile,outfile,exclude,exfile,minlen,maxlen,nonums
    int i = 0;
    char buff[10];
    while (i<argc-1){
        i++;
        if (! strcmp(argv[i],"-h")){
            help();
            exit(0);
        }
        if (! strcmp(argv[i],"-i")){
            if (infile[0]!='\0'){
                printf("%s was given as input but %s was already specified\n",argv[i],infile);
            }
            else{
                i++;
                strcpy(infile,argv[i]);
                continue;
            }
        }
        if (! strcmp(argv[i],"-o")){
            i++;
            strcpy(outfile, argv[i]);
            continue;
        }
        if (! strcmp(argv[i],"-e")){
            i++;
            exclude = true;
            strcpy(exfile,argv[i]);
            continue;
        }
        if (! strcmp(argv[i],"-min")){
            i++;
            if (isnumeric(argv[i])){
                minlen = atoi(argv[i]);
            }
            else{
                help();
                exit(1);
                continue;
            }
        }
        if (! strcmp(argv[i],"-max")){
            i++;
            if (isnumeric(argv[i])){
                maxlen = atoi(argv[i]);
            }
            else{
                help();
                exit(1);
                continue;
            }
        }
        if (! strcmp(argv[i],"-nn")){
            nonums = true;
            continue;
        }
        if (! strcmp(argv[i],"-nnl")){
            while (1){
                i++;
                if (i==argc)
                    break;
                if (isnumeric(argv[i])){
                    NLL[NLLJ] = atoi(argv[i]);
                    NLLJ++;
                }
                else {
                    i--;
                    break;
                }
            }
            if (NLLJ==0){
                help();
                exit(1);
            }
            else
                continue;
        }
        if (infile[0]!='\0'){
            printf("Unknown Option %s\n",argv[i]);
            printf("if you mean %s as input, %s is already specified\n",argv[i],infile);
            help();
            exit(1);
        }
        else{
            strcpy(infile,argv[i]);
        }
    }
}

void gen(){
    if (NLL){
        exceptions[NE]=nllException;
        NE++;
    }
    if (minlen){
        exceptions[NE]=minlenExeption;
        NE++;
    }
    if (maxlen){
        exceptions[NE]=maxlenExeption;
        NE++;
    }
    if (nonums){
        exceptions[NE]=nonumsExeption;
        NE++;
    }
    if (exclude){
        printf("exclude function haven't been implemented yet\n");
    }

    strip(infile,outfile,exceptions);
}

bool nllException(char * line){
    if (! isnumeric(ess)){
        return false;
    }
    for (int i=0; i<NLLJ; i++){
        if (strlen(ess)==NLL[i]){
            return true;
        }
    }
    return false;
}

bool minlenExeption(char * line){
    if (strlen(line)<minlen){
        return true;
    }
    return false;
}

bool maxlenExeption(char * line){
    if (strlen(line)>maxlen){
        return true;
    }
    return false;
}

bool nonumsExeption(char * line){
    for (int i=0; line[i]!='\0'; i++){
        if(! isdigit(line[i])){
            return false;
        }
    }
    return true;
}