#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int value=0, find=0, *table=NULL;

//DEFINITION DE LA STRUCTURE
typedef struct part{
    int begin;
    int end;
    int number;
}Part;

void *findNumber(void* arg);
void readInFile(FILE* f, int t[], int n);

int main(int argc, char* argv[]){
    int i=0, cores=0, size=0, threadNbr=0;

    //Test du Nombre de Parametres
    if(argc != 4){
        printf("\nError !!! Many/Few arguments\n\n");
        return EXIT_FAILURE;
    }
    srand(time(NULL));
    
    //RECUPERATION DU NBRE DE COEURS
    char tmp[2];
    FILE *f = popen("cat /proc/cpuinfo | grep processor | wc -l", "r");
    FILE *fileToRead = fopen("Random_numbers.txt", "r");
    fgets(tmp, 2, f);
    pclose(f);
    cores = atoi(tmp);
    threadNbr = atoi(argv[1]);

    //TEST DU NBRE DE THREADS
    if(threadNbr > cores || threadNbr < 1 ){
        printf("\nError in The Thread's Number !!!\n\n");
        return EXIT_FAILURE;
    }
    //CREATION DES VARIABLES ET THREADS
    pthread_t threads[threadNbr];
    size = atoi(argv[2]);
    value = atoi(argv[3]);
    Part part;

    //Allocation Memoire
    table = malloc(size*sizeof(int));

    //REMPLISSAGE TABLEAU
    printf("\nTotal cores = %d   | Thread's Number = %d \nTable's_size = %d | search_value = %d\n\n", cores, threadNbr, size, value);
    readInFile(fileToRead, table, size);
    printf("Table contents: \n");
    for(i=0; i<size; i++) printf("%d ",table[i]);
    puts("");

    //EXECUTION DES THREADS
    for(i=0; i<threadNbr; i++){
        //Calcul des partitions
        part.begin = (i*size)/threadNbr; 
        part.end = ((i+1)*size/threadNbr)-1;
        part.number = i;
        //Lancement des Threads
        pthread_create(&threads[i], NULL, findNumber,(void*)&part);
        pthread_join(threads[i],NULL);    
    }
    
    //Liberation Memoire
    fclose(fileToRead);
    free(table);
    puts("");
    return 0;
}

void *findNumber(void* arg){
    
    if(find) return EXIT_SUCCESS;
    int j=0;
    Part* part = (Part*) arg;

    printf("\nThread %d search in: ", part->number);
    for(j = part->begin ; j <= part->end; j++){
        printf("%d ",table[j]);
        if(table[j] == value){
            printf("\nThread %d find %d !!\n\n", part->number ,value);
            find = 1;
            return EXIT_SUCCESS;
        }
    }
    printf("\n");
}

void readInFile(FILE* f, int t[], int n){
    int i=0, sizeFile;
    fscanf(f,"%d",&sizeFile);

    if(sizeFile < n){
        printf("\n\nError!! Table's size is Greater than Numbers in File\n\n");
        exit(EXIT_FAILURE);
    }
    else if(n <= 0){
    	printf("\n\nError!! Table's must be Greater than 0\n\n");
        exit(EXIT_FAILURE);
    }

    for(i=0; i<n; i++){
        fscanf(f, "%d", &t[i]);
    }
}
