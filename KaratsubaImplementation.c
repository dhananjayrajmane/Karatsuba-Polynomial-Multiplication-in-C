#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void storeEquations(long long *A,int m,long long *B,int n)
{
    int counter=0;
    for(;counter<m;counter++)
        scanf("%lld",&A[counter]);
    for(counter=0;counter<n;counter++)
        scanf("%lld",&B[counter]);
}

void printArray(char *a,long long *A,int length)
{
    //printf("%s",a);
    for(int counter=0;counter<length;counter++)
    {
        printf("%lld ",A[counter]);
    }
    //printf("\n");
}

long long* multiplication(long long *A,long long *B,int length)
{
    long long *productArray = (long long *)calloc(sizeof(long long),2 * length);
    
    if(length==1)
    {
        productArray[0] = A[0] * B[0];
        return productArray;
    }

    int middle = length/2;
   
    long long lowerArrayA[middle];
    long long uppperArrayA[middle];
    long long lowerArrayB[middle];
    long long uppperArrayB[middle];
    long long lowHighArrayA[middle];
    long long lowHighArrayB[middle];
    //printf("\nLength : %d",length);
    //fill the low and high arrays
    for(int i=0;i<middle;i++)
    {
        lowerArrayA[i] = A[i];
        uppperArrayA[i] = A[i + middle];
        lowHighArrayA[i] = lowerArrayA[i] + uppperArrayA[i];
        
        lowerArrayB[i] = B[i];
        uppperArrayB[i] = B[i + middle];
        lowHighArrayB[i] = lowerArrayB[i] + uppperArrayB[i];
    }
    //printArray("lowerArrayA",lowerArrayA,middle);
    //printArray("uppperArrayA",uppperArrayA,middle);
    //printArray("lowHighArrayA",lowHighArrayA,middle);
    //printArray("lowerArrayB",lowerArrayB,middle);
    //printArray("uppperArrayB",uppperArrayB,middle);
    //printArray("lowHighArrayB",lowHighArrayB,middle);    
    
    long long *productLow = (long long *)calloc(sizeof(long long),middle);
    long long *productHigh = (long long *)calloc(sizeof(long long),middle);
    long long *productLowHigh = (long long *)calloc(sizeof(long long),middle);
 
    productLow = multiplication(lowerArrayA,lowerArrayB,middle);
    productHigh = multiplication(uppperArrayA,uppperArrayB,middle);
    productLowHigh = multiplication(lowHighArrayA,lowHighArrayB,middle);
    
    long long intermediateProduct[length];
    int counter=0;
     //printf("\nintermediateProduct : ");
    for(counter=0;counter<length;counter++)
    {
      intermediateProduct[counter] = productLowHigh[counter] -  productHigh[counter] -  productLow[counter];
      //printf("%4lld",intermediateProduct[counter]);
    }
    
    int temp = length/2;

    //printf("\nproductArray : ");
    for(counter=0;counter<length;counter++)
    {
        productArray[counter] += productLow[counter];
    //printf("  %d : %4lld",counter,productArray[counter]);
        productArray[counter + length] += productHigh[counter];
    //printf("  %d : %4lld",counter + length,productArray[counter]);
        productArray[temp + counter] += intermediateProduct[counter];
    //printf("  %d : %4lld",temp + counter,productArray[counter]);
    }
    return productArray;
        
}

int getNumberOfZeroes(long long *array,int length)
{
    int counter = length - 1;
    long long zero = 0;
    while(counter>=0)
    {
        if(array[counter]!=zero)
            break;
        counter--;
    }
    return (length - counter-1);
}

int isPowerOfTwo(int n)
{
    if(ceil(log2(n))==floor(log2(n)))
        return 1;
    return 0;
}

int getPowerTwoN(int N)
{
    return pow(2,ceil(log2(N)));
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    int m,n,nearestPowerTwo,counter=0;
    scanf("%d",&m);
    scanf("%d",&n);
    if(m==0 || n==0)
    {
        printf("%d",counter);
        return 0;
    }
    if((m>=n))
    {
        if(!isPowerOfTwo(m))
        {
           // printf("m is not power of two and greate");
            //printf("\nNearer %d\n",getPowerTwoN(m));
            nearestPowerTwo = getPowerTwoN(m);
        }
        else
            nearestPowerTwo = m;
    }
    else if(!isPowerOfTwo(n))
    {
        //printf("n is not power of two and greate");
        //printf("\nNearer %d\n",getPowerTwoN(n));
        nearestPowerTwo = getPowerTwoN(n);
    }
    else
        nearestPowerTwo = n;
   // printf("\nNearest power of 2 is : %d \n",nearestPowerTwo);
    
    long long *productArray = (long long *)calloc(sizeof(long long),2 * nearestPowerTwo);
    long long *A = (long long *)calloc(sizeof(long long),nearestPowerTwo);
    long long *B = (long long *)calloc(sizeof(long long),nearestPowerTwo);
    
    storeEquations(A,m,B,n);
    
    //makeEquationPowerOfTwo(A,m,B,n,nearestPowerTwo);
    
    for(counter=m;counter<nearestPowerTwo;counter++)
        A[counter]=0;
    for(counter=n;counter<nearestPowerTwo;counter++)
        B[counter]=0;
    
    //printArray("ArrayA",A,nearestPowerTwo);
    //printf("\n");
    //printArray("ArrayB",B,nearestPowerTwo);
  
    long long *output = multiplication(A,B,nearestPowerTwo);
    int zeros = getNumberOfZeroes(output,(2*nearestPowerTwo - 1));
  
    //printArray("",output,2*nearestPowerTwo-1-zeros);
    printArray("",output,m+n-1);
    counter=0;
    if(2*nearestPowerTwo-1-zeros == 0)
        printf("%d",counter);
    free(productArray);
    free(A);
    free(B);
    return 0;
}
