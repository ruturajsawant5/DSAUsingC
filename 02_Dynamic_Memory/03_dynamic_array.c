#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct array
{
    int* a;
    int N;
};

struct array get_dyn_array(void);
struct array* get_dyn_array2(void);
void get_dyn_array3(struct array** pparr);
void fill_array(struct array* parray);
void show_array(struct array* parray);

int main()
{
    struct array arr1;
    struct array* parr2;
    struct array* parr3;
    
    srand((unsigned int)time(NULL)); //seed

    arr1 = get_dyn_array(); //memberwise copy will happen
    fill_array(&arr1);
    show_array(&arr1);

    parr2 = get_dyn_array2();
    fill_array(parr2);
    show_array(parr2);

    get_dyn_array3(&parr3);
    fill_array(parr3);
    show_array(parr3);

    free(arr1.a);

    free(parr2->a);
    free(parr2);

    free(parr3->a);
    free(parr3);

}

struct array get_dyn_array(void)
{
    struct array arr;
    int N = 50;
    
    arr.a = (int*)malloc(sizeof(int) * N);
    if(arr.a == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    arr.N = N;

    return arr;
    
}

struct array* get_dyn_array2(void)
{
    struct array* parr;
    int N = 150;
    
    parr = (struct array*)malloc(sizeof(struct array));
    if(parr == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    parr->a = (int*)malloc(sizeof(int) * N);
    if(parr->a == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }
    parr->N = N;

    return parr;
}

void get_dyn_array3(struct array** pparr)
{
    struct array* parr;
    int N = 200;
    
    parr = (struct array*)malloc(sizeof(struct array));
    if(parr == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    parr->a = (int*)malloc(sizeof(int) * N);
    if(parr->a == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }
    parr->N = N;

    *pparr = parr;
}

void fill_array(struct array* parray)
{
    int i;
    
    for(i = 0; i < parray->N; i++)
        parray->a[i] = rand();

}

void show_array(struct array* parray)
{
    int i;
    
    printf("\nARRAY CONTENT\n");
    for(i = 0; i < parray->N; i++)
        printf("%d=%d\n", i+1, parray->a[i]);

}