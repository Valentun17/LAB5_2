#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

int WriteTxt(FILE *fP,int x1,int x2,int N,float delta);
void ReadTxt(FILE *fP,unsigned int n,int x1,int x2);
int WriteBin(FILE *fP,int x1,int x2,int N,float delta);
void ReadBin(FILE *fP,unsigned int n,int x1,int x2);
void SaveResult(FILE *fP,int n);

int main()
{
    unsigned int N,n;
    float delta;
    int x1,x2;
    char gr[10];
    FILE *fInput, *fWriteTxt, *fWriteBin, *fReadTxt, *fReadBin;

    fInput = fopen("input.dat","r");
    fscanf(fInput,"%s%d%d%u%f",&gr,&x1,&x2,&N,&delta);
    fclose(fInput);

    printf("Group : %s\nx1 = %d\nx2 = %d\nN = %u\ndelta = %f\n\n",gr,x1,x2,N,delta);
    fWriteTxt = fopen("result.txt","w");
    n = WriteTxt(fWriteTxt,x1,x2,N,delta);
    fclose(fWriteTxt);

    printf("-------------------------------------------------\n");

    fReadTxt = fopen("result.txt","r");
    ReadTxt(fReadTxt,n,x1,x2);
    fclose(fReadTxt);

    fWriteBin = fopen("result.bin","wb");
    n = WriteBin(fWriteTxt,x1,x2,N,delta);
    fclose(fWriteBin);

    printf("-------------------------------------------------\n");

    fReadBin = fopen("result.bin","rb");
    ReadBin(fReadTxt,n,x1,x2);
    fclose(fReadBin);

    printf("-------------------------------------------------\n");

    fReadTxt = fopen("result.txt","r");
    SaveResult(fReadTxt,n);
    fclose(fReadTxt);
    return 0;
}

int WriteTxt(FILE *fP,int x1,int x2,int N,float delta)
{
    int y,n=0;
    for(int i=0;i<=N;i++)
    {
        n++;
        y=pow(x1,2)+10;
        fprintf(fP,"%d %d\n",x1,y);
        if(x1>=x2)
        {
            return n;
        }
        x1+=delta;
    }
    fclose(fP);
    return n;
}

void ReadTxt(FILE *fP,unsigned int n,int x1,int x2)
{
    int x,y;
    printf("TXT FILE (result.txt) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("*\tN\t*\tX\t*\tF(X)\t*\t\n");
    printf("*************************************************\n");
    for(int i = 0; i < n;i++)
    {
        fscanf(fP,"%d",&x);
        fscanf(fP,"%d",&y);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    printf("\n\n");
    fclose(fP);
}

int WriteBin(FILE *fP,int x1,int x2,int N,float delta)
{
    int y,n=0;
    for(int i=0;i<=N;i++)
    {
        n++;
        y=pow(x1,2)+10;
        fwrite(&x1,sizeof(int),1,fP);
        fwrite(&y,sizeof(int),1,fP);
        if(x1>=x2)
        {
            return n;
        }
        x1+=delta;
    }
    fclose(fP);
    return n;
}

void ReadBin(FILE *fP,unsigned int n,int x1,int x2)
{
    int x,y;
    printf("BIN FILE (result.bin) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("*\tN\t*\tX\t*\tF(X)\t*\t\n");
    printf("*************************************************\n");
    for(int i = 0; i < n;i++)
    {
        fread(&x,sizeof(int),1,fP);
        fread(&y,sizeof(int),1,fP);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    printf("\n\n");
    fclose(fP);
}

void SaveResult(FILE *fP,int n)
{
   int k;
   int **array = (int **)malloc(n*sizeof(int*));
   for(int i = 0; i < n; i++)
   {
      array[i] = (int *)malloc(2*sizeof(int));
   }
   printf("Array :\n");
   for(int i = 0;i<n;i++)
   {
       for(int j = 0;j<=1;j++)
       {
           fscanf(fP,"%d",&k);
           array[i][j] = k;
       }
   }
   for(int i = 0;i<n;i++)
   {
       for(int j = 0;j<1;j++)
       {
            printf("x: %d \ty: %d\n",array[i][j],array[i][j+1]);
       }
   }
   for(int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
}
