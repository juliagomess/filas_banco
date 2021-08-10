#ifndef PILHA_FILA_H_INCLUDED
#define PILHA_FILA_H_INCLUDED

/* Funcoes Pilha


Pilha * CriaPilha (void)

No* ins_inicio (No* t int a)

void push (Pilha* p, int v)

No* ret_inicio (No* l)

int pop (Pilha* p)

Pilha * libera (Pilha * p)

void imprimePilha(Pilha* p)

int vazia(Pilha *p)



Funcoes Fila

Fila* CriaFila()

void InsereFila (Fila* f, int v)

int RetiraFila (Fila* f)

Fila *liberaFila(Fila *f)

void imprimeFila(Fila *f)

*/

typedef struct nos
{
    int info;
    struct nos *prox;
} No;

typedef struct no
{
    int info;
    struct no *prox;
}Lista;

typedef struct fila
{
    No * inicio;
    No * fim;
} Fila;

typedef struct pilha
{
    No *primeiro;
} Pilha;

Lista* CriaLista (void)
{
    return NULL;
}


Lista* insereLista_pos(Lista* recebida, int valor, int pos)
{
    Lista *novo, *aux, *aux1;
    int cont;
    novo = (Lista*) malloc (sizeof(Lista));
    novo ->info = valor;
    novo->prox = NULL;

    if(pos == 1)
    {
        novo->prox = recebida;
        return novo;

    }
    aux1 = recebida;
    cont = 1;

    while ((aux1 != NULL) && (cont<pos))
    {
        aux =aux1;
        aux1 = aux1 ->prox;
        cont++;
    }
    novo ->prox = aux1;
    aux -> prox = novo;
    return recebida;
}

Lista* buscaLista (Lista* recebida, int v)
{
    Lista* p;
    for (p= recebida; p!=NULL; p=p->prox)
    {
        if (p->info == v)
            return p;
    }
    return NULL;
}

Lista* insereLista (Lista* recebida, int valor)
{
    Lista  *novo ;
    novo= (Lista*) malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = recebida;
    return novo;
}

Lista* insereLista_palavra (Lista* recebida, char valor[50])
{
    Lista  *novo ;
    novo= (Lista*) malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = recebida;
    return novo;
}



void imprimeLista(Lista *p)
{
    printf("\nLista");
    while(p!=NULL)
    {
        printf(" - %d",p->info);
        p=p->prox;
    }
}

Pilha * CriaPilha (void)
{
    Pilha *p;
    p = (Pilha*)malloc(sizeof(Pilha));
    p->primeiro = NULL;
    return p;

};

No* ins_inicio (No* t, int a)
{
    No* aux = (No*)malloc(sizeof(No));
    aux -> info = a;
    aux -> prox =t;
    return aux;
};


void push (Pilha* p, int v)
{
    p ->primeiro = ins_inicio(p ->primeiro,v);
};


void InsereFila_seg (Fila* f, int v)
{
    if(f->inicio==NULL)
    {
        f->inicio = ins_inicio(f->inicio,v);
        f->fim = f->inicio;
    }
    else
    {
        No * segundo = (No*)malloc(sizeof(No));
        No *aux=f->inicio;
        No *t=aux->prox;

        segundo->info=v;
        segundo->prox=t;
        aux->prox=segundo;

        if (f->inicio==f->fim)
            f->fim = segundo;
    }
}

No* ret_inicio (No* l)
{
    No * p = l ->prox;
    free(l);
    return p;
};



int pop (Pilha* p)
{
    int v;
    if(p==NULL)
    {
        printf("Pilha vazia.\n");
        exit(1);
    }
    v= p->primeiro->info;
    p->primeiro=ret_inicio(p->primeiro);
    return v;
};


Pilha * libera (Pilha * p)
{
    No* q = p->primeiro;
    while (q!= NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return (NULL);
};

void imprimePilha(Pilha* p)
{
    No* q;
    if(!p)
    {
        printf("\n\n\tPILHA VAZIA!!!!");
    }
    else
    {
        printf("\n\n\tPILHA: ");
        for(q=p->primeiro; q!=NULL; q=q->prox)
        {
            printf(" - %d", q->info);
        }
    }
}


int vazia(Pilha *p)
{
    if(!p->primeiro)
    {
        return 1; //pilha vazia
    }
    return 0;
}

int VaziaFila(Fila *f)
{
    if (f->inicio==NULL) return 1;
    return 0;
}



Fila* CriaFila()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f ->inicio = f->fim = NULL;
    return f;
}

No* ins_fim (No* fim, int A)
{
    No* p = (No*)malloc(sizeof(No));
    p->info = A;
    p->prox = NULL;
    if(fim != NULL)
        fim->prox = p;
    return p;
};


void InsereFila (Fila* f, int v)
{
    f->fim = ins_fim(f->fim,v);
    if(f->inicio==NULL)
        f->inicio = f->fim;
}


No* retira_inicio (No* inicio)
{
    No* p = inicio->prox;
    free(inicio);
    return p;
}

int RetiraFila (Fila* f)
{
    int v;
    if(VaziaFila(f))
    {
        printf("Fila Vazia.\n");
        exit(0);
    }
    v=f->inicio->info;
    f->inicio = retira_inicio(f->inicio );
    if(f->inicio == NULL )
        f->fim = NULL;
    return v;
}

int RetiraFila_seg (Fila* f)
{
    int v;
    if(VaziaFila(f))
    {
        printf("Fila Vazia.\n");
        exit(0);
    }
    v=f->inicio->prox->info ;
    f->inicio->prox = retira_inicio(f->inicio->prox );

    return v;
}

int Retorna_inicio (Fila* f)
{
    int v;
    if(VaziaFila(f))
    {
        printf("Fila Vazia.\n");

    }
    v=f->inicio->info;
    return v;
}

void InsereFila_ini (Fila* f, int v)
{
    f->inicio = ins_inicio(f->inicio,v);
    if(f->fim==NULL)
        f->fim = f->inicio;
}

void imprimeFila(Fila *f)
{
    No *q;
    printf("\n");

    for(q=f->inicio; q!=NULL; q=q->prox)
	    if(q==f->inicio)
            {printf("%2d\t - ", q-> info);}	
        else
            {printf("%2d - ", q-> info);}
}

Fila *liberaFila(Fila *f)
{
    No* q = f->inicio;
    while(q!= NULL)
    {
        No *t = q->prox;
        free(q);
        q=t;
    }
}
#endif // PILHA_FILA_H_INCLUDED
