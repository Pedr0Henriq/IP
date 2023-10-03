#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
    {
        int linha,coluna,maior,**matriz;
    }imagemPGM;

void clarear_imagem(imagemPGM  img,FILE *arq){
   int i,j;
   arq=fopen("TESTE1.pgm","a");
   for(i=0;i<img.linha;i++){
    for(j=0;j<img.coluna;j++){
     if(img.matriz[i][j]+30>255){
            fprintf(arq,"%d ",img.maior);
        }
    else{
        fprintf(arq,"%d ",img.matriz[i][j]+30);}
           
    }
    fprintf(arq,"\n");
   }
   fclose(arq);
 
}

void binarizar_imagem(imagemPGM img, FILE *arq2){
    int i,j;
    arq2=fopen("TESTE2.pgm","a");
    for(i=0;i<img.linha;i++){
        for(j=0;j<img.coluna;j++){
            if(img.matriz[i][j]>=128){
                fprintf(arq2,"%d ",255);
            }
            else
                fprintf(arq2,"%d ", 0);
        }
        fprintf(arq2,"\n");
    }
    fclose(arq2);
}

void rotacionar_imagem(imagemPGM img, FILE *arq3){
    int i,j,**matriz_t;
    arq3=fopen("TESTE3.pgm","a");
    matriz_t=malloc(img.coluna*sizeof(int *));
for(i=0;i<img.coluna;i++)
    matriz_t[i]=malloc(img.linha*sizeof(int));

    for(i=0;i<img.linha;i++){
        for(j=0;j<img.coluna;j++){
            matriz_t[j][i]=img.matriz[i][j];
        }
    }

    for(i=0;i<img.linha;i++){
        for(j=0;j<img.coluna;j++){
            fprintf(arq3,"%d ",matriz_t[i][j]);
        }
        fprintf(arq3,"\n");
    }
fclose(arq3);

}



int main(int argc,char **argv){
    FILE *file,*arq,*arq2,*arq3, *arq4;
     char ler_linha[1024],nomearquivo[300];
     int i,j;
    imagemPGM img;


file=fopen(argv[1],"r");
if(file==NULL){
    printf("Erro ao abrir o arquivo.");
}

arq=fopen("TESTE1.pgm","w");
if(arq==NULL){
    printf("Erro ao abrir o arquivo.");
}
arq2=fopen("TESTE2.pgm","w");
if (arq2==NULL)
{
    printf("Erro ao abrir o arquivo.");
}
arq3=fopen("TESTE3.pgm","w");
if (arq3==NULL)
{
    printf("Erro ao abrir o arquivo.");
}


fscanf(file,"%s",ler_linha);
fprintf(arq,"%s\n",ler_linha);
fprintf(arq2,"%s\n",ler_linha);
fprintf(arq3,"%s\n",ler_linha);
fscanf(file,"%d %d",&img.coluna,&img.linha);
fprintf(arq,"%d %d\n",img.coluna,img.linha);
fprintf(arq2,"%d %d\n",img.coluna,img.linha);
fprintf(arq3,"%d %d\n",img.coluna,img.linha);
fscanf(file,"%d",&img.maior);
fprintf(arq,"%d\n",img.maior); 
fprintf(arq2,"%d\n",img.maior);
fprintf(arq3,"%d\n",img.maior);


img.matriz=malloc(img.linha*sizeof(int *));
for(i=0;i<img.linha;i++)
    img.matriz[i]=malloc(img.coluna*sizeof(int));

for(i=0;i<img.linha;i++){
    for(j=0;j<img.coluna;j++){
        fscanf(file,"%d ",&img.matriz[i][j]);
    }
}

fclose(file);
fclose(arq);
fclose(arq2);
fclose(arq3);

clarear_imagem(img,arq);
binarizar_imagem(img,arq2);
rotacionar_imagem(img,arq3);
for(i=0;i<img.linha;i++)
    free(img.matriz[i]);
free(img.matriz);

return 0;
}