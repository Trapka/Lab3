#include <iostream>
#include <ctime>

int main()
{

    srand(time(0));
    int n ,m;
    n   =rand()%5+3;
    m   =rand()%5+3;
     long long arrayA[m][n];
     long long arrayB[n];
    for (size_t i = 0; i < m ;i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            arrayA[i][j]=rand()%9+3;
            
        }

        //arrayB[i][0]=rand()%9+3;
    }
    for (size_t i = 0; i < n; i++)
    {
        arrayB[i]=rand()%9+3;
    }
    
    std::cout<<"----------------------"<<std::endl;
    for (size_t i = 0; i < m ;i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout<<arrayA[i][j]<<"\t";
        }
        std::cout<<'\n';
    }
    std::cout<<"----------------------"<<std::endl;
    for (size_t i = 0; i < n; i++)
    {
        std::cout<<arrayB[i]<<std::endl;
        //std::cout<<arrayB[0][i]<<std::endl;
    }
    int a=0;
    printf("____________________\n");
    long long arrayC[m]={};
    long long *A_array_start=&arrayA[0][0];
    long long *A_array_end=&arrayA[m-1][n-1];
    long long *B_array_start=&arrayB[0];
    long long *B_array_end=&arrayB[n-1];
    std::cout<<sizeof(arrayA)<<"\t"<<sizeof(arrayA[0][0])<<std::endl;
   // long long *C_array_start=&arrayC[0];
    //long long *C_array_end=&arrayC[m-1];
        asm (  
        "movq $0,%%rax\n\t"
         //"movq %[A_array_start],%%rbx\n\t"
         "movq %[A_array_start],%%rbx\n\t"
        // "movq %[B_array_start],%%rdx\n\t"
        "subq $8, %%rbx \n\t"
        "movq $0,%%rcx\n\t"
        "movq $0,%%r9\n\t"
        "movq $0,%%r10\n\t"
        "leaq %[arrayC], %%r10 \n\t"
        //"pushq %%r10 \n\t"
        "start1: \n\t"

        "movq %[B_array_start],%%rdx\n\t"
        "subq $8, %%rdx \n\t"

         "start: \n\t"
        "addq $8, %%rdx \n\t"
        "addq $8, %%rbx \n\t"
        "movq (%%rdx),%%rcx\n\t"
        "movq (%%rbx),%%rax\n\t"
        //"mulq %%rcx\n\t"
        "movq $0,%%rax\n\t"
        "s: \n\t"
        "addq (%%rbx), %%rax\n\t"
        "loop s \n\t"
    

        "addq %%rax,%%r9\n\t"
        "cmpq %%rdx, %[B_array_end]\n\t"
         "jne start\n\t"

        "movq %%r9,%%rax\n\t"
        //"popq %%r10\n\t"
        "movq %%rax,(%%r10)\n\t"
        "addq $8, %%r10 \n\t"
        //"pushq %%r10 \n\t"
        "movq $0,%%r9\n\t"
        "cmpq %%rbx, %[A_array_end]\n\t"
        "jne start1\n\t"

            ://"=a"(a)
            :[A_array_end]"m"(A_array_end),
            [arrayB]"m"(arrayB), [arrayC]"m"(arrayC),
            [B_array_end]"m"(B_array_end),[A_array_start]"m"(A_array_start),[B_array_start]"m"(B_array_start)
            :"%rbx", "%rcx","%rdx","cc","memory","%r9","%r10","%r11"
        );
    std::cout<<"__________ass____________________"<<std::endl;
    for (size_t i = 0; i < m; i++)
    {
        // for (size_t j = 0; j < n; j++)
        // {
        //     arrayC[i]+=arrayA[i][j]*arrayB[j];
        // }
        std::cout<<arrayC[i]<<std::endl;
    }
    std::cout<<"____________c++____________________"<<std::endl;

        long long arrayC1[m]={};
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            arrayC1[i]+=arrayA[i][j]*arrayB[j];
        }
         std::cout<<arrayC1[i]<<std::endl;

    }
    
    return 0 ;
    }