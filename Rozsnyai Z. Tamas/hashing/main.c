#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Hash tables
key->value
hash function: "home" h(string)->int ex: home=396  h(s)=sum(i=0;n){s[i]}
in hash table: "home" is at position 396
problem at collision: "meoh" is at position 396 too
to avoid collision: 1)Chaining: you may chain collisions in a list at that position
HINTS:array length: 101
*/
/* HOMEWORK: Se mareste lungimea hashtable-ului aproape de 1000(un nr prim). Apoi, printr-un random string
generator, umplem hashtable cu 10000 strings. Trebuie sa parcurgem hashtable si sa gasim lista cu cele mai
multe elemente si sa afisam cat elemente are aceasta. Trebuie sa schimbam apoi functia hashing, pentru a vedea
cum se schimba numarul maxim. Daca numarul e prea mic la hashing bun, marim hashtable la 10000.
*/
typedef struct hasht
{
    char key[3000];
    struct hasht *next;
}hashT;

hashT *h[3000];
int listnr[3000];
char key[]=" ";
int hashmethod_nr=0;


int hashing1(char str[])
{
    int nr=0, i,len=strlen(str);
    for(i=0;i<len;i++)
        nr=nr+str[i];
    return nr%3001;
}

int hashing2(char str[])
{
    int nr, i,len=strlen(str);
    nr=str[len/2];
    for(i=0;i<len;i++)
        nr=nr+str[i];
    return (nr/(len))%3001;
}

int hashing3(char str[])
{
    int nr=0, i,len=strlen(str),x=1000;

    for(i=0;i<len;i++)
        {
            nr=nr+(str[i]*x);
            if(x!=1) x=x/10;
        }
    return nr%3001;
}


void inserthash(char str[])
{
    hashT *p;
    int n;
    switch (hashmethod_nr)
    {
        case 1: n=hashing1(str); break;
        case 2: n=hashing2(str); break;
        case 3: n=hashing3(str); break;

    }
    listnr[n]++;
    if(h[n]==NULL)
    {
        h[n]=(hashT*)malloc(sizeof(hashT));
        strcpy(h[n]->key,str);
        h[n]->next=NULL;
    }
    else
    {
        p=h[n];
        while(p->next!=NULL)
        {
            p=p->next;
        }
        hashT *newe=(hashT*)malloc(sizeof(hashT));
        strcpy(newe->key,str);
        newe->next=NULL;
        p->next=newe;
    }

}
int limitedrandom(int a,int b)
{
    return ((rand())%(b-a))+a;
}

void rand_str_hased(int a, int b)
{
    int nr=limitedrandom(a,b);
    int i;
    char x[3000];
    for(i=0;i<nr;i++)
    {
        x[i]=limitedrandom('a','Z');
    }
    inserthash(x);
}

int main()
{
    char x[3000];
    int nr,i;
    printf("Hashin' method (1-3):\n#");
    scanf("%d",&hashmethod_nr);
    printf("Number of strings:");
    scanf("%d",&nr);
    srand(time(NULL));
    printf("Random strings limit [a,b]:\na=");
    int a,b;
    scanf("%d",&a);
    printf("b=");
    scanf("%d",&b);

    for(i=0;i<nr;i++)
    {
        rand_str_hased(a,b);
    }
    hashT *p;
   /* for(i=0;i<3001;i++)
    {
        if(h[i]!=NULL)
        {
            p=h[i];
            while(p!=NULL)
            {
                printf("%s ",p->key);
                p=p->next;
            }
            printf("\n");
        }
    }
    */
    int max=0;
    for(i=0;i<3000;i++)
    {
        if (listnr[i]>max) max=listnr[i];

    }
    printf("\nMax of chained elements: %d",max);

    //printf("%d",hashing(x));

    return 0;
}
