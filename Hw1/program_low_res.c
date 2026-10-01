#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    unsigned sizeX; //image width
    unsigned sizeY; //image height
    unsigned char *image; //image array
    unsigned char *imageTemp; //temporary image array
    unsigned int k; //iterator for storing image data from a matrix
    unsigned levels;

    FILE *file = fopen("Porche.pgm","r");
    if(file==0){
        printf("no open");
        return 1;
    }
    if(3!=fscanf(file, "P5 %d %d %d ", &sizeX, &sizeY, &levels)) return 1;
    image=(unsigned char *) malloc(sizeX*sizeY);
    fread(image, sizeof(unsigned char), sizeX*sizeY, file);
    fclose(file); 

    imageTemp = (unsigned char *) malloc((sizeX/2)*(sizeY/2));
    unsigned char processedImage [sizeY][sizeX];
    memcpy(processedImage, image, sizeX*sizeY*sizeof(unsigned char));
    
    k=0;
    
    for(unsigned int i = 0; i<sizeY; i++){
        for(unsigned int j = 0; j<sizeX; j++){
            if((i%2==0) && (j%2==0)){
                imageTemp[k] = processedImage[i][j];
                k++;
            }   
        }
    }
    
    file = fopen("new_Porche.pgm","w");
    if(file==0){
        printf("failed to create file");
        return 1;
    }
    fprintf(file,"P5 %d %d %d ",sizeX/2,sizeY/2, levels);
    fwrite(imageTemp, sizeof(unsigned char), (sizeY/2)*(sizeX/2), file);
    fclose(file);
    return 0;
}
