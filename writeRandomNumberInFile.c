#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[] ){

    int n=0, i=0;
    FILE *file=NULL;
    file = fopen("Random_numbers.txt", "w");
    srand(time(NULL));

    printf("\nPlease How many numbers to generate in File \"Random_numbers.txt\" ?: ");
    scanf("%d",&n);
	
    //check if n > 1
    if(n<1){
    	printf("\n\nError!! Enter a positive number (>0)\n\n");
	return EXIT_FAILURE;
    }
    
    //Write in File
    fprintf(file, "%d\n", n);
    for(i=0; i<n; i++){
	fprintf(file, "%d\n", rand()%1000);
    }
    
    //Status
    printf("\nOk ! %d number(s) generated successfully in File \"Random_numbers.txt\" \n\n",n);
    fclose(file);
    return EXIT_SUCCESS;
}
