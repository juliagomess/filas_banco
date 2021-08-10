#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pilha_fila_lista.h"
#include <time.h>

typedef struct
{
    int senha;
    int gestante;
    int crianca;
    int idade;
    float tempo;
    int fila;
} informacoes;

typedef struct
{
    Fila *preferencial;
    Fila *normal_1;
    Fila *normal_2;
    Fila *normal_3;
    Fila *normal_4;
} Filas;

typedef struct
{
    int Fp;
    int F1;
    int F2;
    int F3;
    int F4;
} Fila_atendida;

typedef struct
{
    int nmrp_preferencial;
    int nmrp_normal_1;
    int nmrp_normal_2;
    int nmrp_normal_3;
    int nmrp_normal_4;

    float tempo_preferencial;
} nmrp;

int coleta_info(informacoes infos[],int *i)
{
    int p;
    p=*i;

    printf("\n");
    printf("Qual a sua idade?\nR:");
    scanf("%d", &infos[p].idade);
    printf("Voc\210 \202 gestante? Sim <1>, N\306o <0>\nR:");
    scanf("%d", &infos[p].gestante);
    printf("Voc\210 tem crian\207a de colo? Sim <1>, N\306o <0>\nR:");
    scanf("%d", &infos[p].crianca);
    infos[p].senha = p + 1;
    printf("\n\n====================\n\n");
    printf("\n\nSua senha e: %4d\n\n",infos[p].senha);
    printf("\n\n====================\n\n");
    do
    {
        infos[p].tempo = rand() % 10;
    }while(infos[p].tempo < 5 );
    printf("\n\nTempo = %g minutos\n\n",infos[p].tempo);
    if(infos[p].idade >= 60 || infos[p].gestante == 1 || infos[p].crianca == 1)
    {
        p++;
        *i = p;
        return 1;
    }
    p++;
    *i = p;
    return 0;
}

void ImprimeFilas(Filas Fp1, nmrp nmr[],informacoes infos[],int pessoas, Fila_atendida Fa1[])
{

    if(nmr[1].nmrp_normal_2 == 0)
        infos[Fa1[1].F2].tempo = 0;

    printf("\n=======================================================\n");
    printf("\n\t\tCaixas\n\n");
    printf("\n\nTempo m\202dio da fila preferencial = %g minutos\n",nmr[1].tempo_preferencial);
    printf("\nCaixa [%g]\t",infos[Fa1[1].Fp].tempo);
    printf("Fila preferencial: ");
    imprimeFila(Fp1.preferencial);
    printf("\nCaixa [%g]\t",infos[Fa1[1].F1].tempo);
    printf("Fila1: ");
    imprimeFila(Fp1.normal_1);
    printf("\nCaixa [%g]\t",infos[Fa1[1].F2].tempo);
    printf("Fila2: ");
    imprimeFila(Fp1.normal_2);
    printf("\nCaixa [%g]\t",infos[Fa1[1].F3].tempo);
    printf("Fila3: ");
    imprimeFila(Fp1.normal_3);
    printf("\nCaixa [%g]\t",infos[Fa1[1].F4].tempo);
    printf("Fila4: ");
    imprimeFila(Fp1.normal_4);
    printf("\n======================================================\n");

    if(infos[Fa1[1].Fp].tempo != 0)
        infos[Fa1[1].Fp].tempo--;
    else
        if(nmr[1].nmrp_preferencial!= 0)
            esvazia(nmr,Fp1,1);

    if(infos[Fa1[1].F1].tempo != 0)
        infos[Fa1[1].F1].tempo--;
    else
        if(nmr[1].nmrp_normal_1!= 0)
            esvazia(nmr,Fp1,2);

    if(infos[Fa1[1].F2].tempo != 0)
        infos[Fa1[1].F2].tempo--;
    else
        if(nmr[1].nmrp_normal_2!= 0)
            esvazia(nmr,Fp1,3);

    if(infos[Fa1[1].F3].tempo != 0)
        infos[Fa1[1].F3].tempo--;
    else
        if(nmr[1].nmrp_normal_3!= 0)
            esvazia(nmr,Fp1,4);

    if(infos[Fa1[1].F4].tempo != 0)
        infos[Fa1[1].F4].tempo--;
    else
        if(nmr[1].nmrp_normal_4!= 0)
            esvazia(nmr,Fp1,5);
}

void esvazia(nmrp numerope[], Filas Fp, int h)
{
    if(h==1)
    {
        RetiraFila(Fp.preferencial);
        numerope[1].nmrp_preferencial--;
    }
    if(h==2)
    {
        RetiraFila(Fp.normal_1);
        numerope[1].nmrp_normal_1--;
    }
    if(h==3)
    {
        RetiraFila(Fp.normal_2);
        numerope[1].nmrp_normal_2--;
    }
    if(h==4)
    {
        RetiraFila(Fp.normal_3);
        numerope[1].nmrp_normal_3--;
    }
    if(h==5)
    {
        RetiraFila(Fp.normal_4);
        numerope[1].nmrp_normal_4--;
    }
}

void organiza(informacoes infos[], int p, int preferencia,nmrp numerope[],Filas Fp, int *ordem, Fila_atendida Fa[])
{
    int i,k;
    int s=100;
    i=p-1;
    int t = * ordem;

    if(preferencia == 1)
    {
        if(numerope[1].nmrp_preferencial < 6 || numerope[1].tempo_preferencial<=5)
        {
            infos[i].fila = 5;
            numerope[1].nmrp_preferencial++;
            numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
            InsereFila(Fp.preferencial, infos[i].senha);
            Fa[1].Fp = Retorna_inicio(Fp.preferencial) - 1;

            ImprimeFilas(Fp,numerope,infos,p,Fa);
        }
        else
        {
            for(int h =0; h<p; h++)
            {
                if(infos[h].fila == 5)
                {
                    if(infos[h].senha<s)
                    {
                        s = infos[h].senha;
                        k=h;
                    }
                }
            }

            printf("\n\n");
            if(t==1)
            {
                infos[k].fila =6;
                numerope[1].nmrp_normal_1++;
                numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                if(numerope[1].nmrp_preferencial > 1)
                {
                    InsereFila_seg(Fp.normal_1,RetiraFila_seg(Fp.preferencial));
                    InsereFila(Fp.preferencial, infos[i].senha);
                }
                else
                {
                    InsereFila(Fp.normal_1, infos[i].senha);
                    Fa[1].F1 = Retorna_inicio(Fp.normal_1) - 1;
                }

                ImprimeFilas(Fp,numerope,infos,p,Fa);

            }
            else
            {
                if(t==2)
                {
                    infos[k].fila = 7;
                    numerope[1].nmrp_normal_2++;
                    numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                    if(numerope[1].nmrp_preferencial > 1)
                    {
                        InsereFila_seg(Fp.normal_2,RetiraFila_seg(Fp.preferencial));
                        InsereFila(Fp.preferencial, infos[i].senha);
                    }
                    else
                    {
                        InsereFila(Fp.normal_2, infos[i].senha);
                        Fa[1].F2 = Retorna_inicio(Fp.normal_2) - 1;
                    }

                    ImprimeFilas(Fp,numerope,infos,p,Fa);
                }
                else
                {
                    if(t==3)
                    {
                        infos[k].fila = 8;
                        numerope[1].nmrp_normal_3++;
                        numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                        if(numerope[1].nmrp_preferencial > 1)
                        {
                            InsereFila_seg(Fp.normal_3,RetiraFila_seg(Fp.preferencial));
                            InsereFila(Fp.preferencial, infos[i].senha);
                        }
                        else
                        {
                            InsereFila(Fp.normal_3, infos[i].senha);
                            Fa[1].F3 = Retorna_inicio(Fp.normal_3) - 1;
                        }

                        ImprimeFilas(Fp,numerope,infos,p,Fa);
                    }
                    else
                    {
                        if(t==4)
                        {
                            infos[k].fila = 9;
                            numerope[1].nmrp_normal_4++;
                            numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                            if(numerope[1].nmrp_preferencial > 1)
                            {
                                InsereFila_seg(Fp.normal_4,RetiraFila_seg(Fp.preferencial));
                                InsereFila(Fp.preferencial, infos[i].senha);
                            }
                            else
                            {
                                InsereFila(Fp.normal_4, infos[i].senha);
                                Fa[1].F4 = Retorna_inicio(Fp.normal_4) - 1;
                            }

                            ImprimeFilas(Fp,numerope,infos,p,Fa);
                        }
                    }
                }
            }
            if(t<4)
                t++;
            else
                t=1;
            *ordem = t;
        }
    }
    else  //se nao for preferencial
    {
        int F[5];

        F[0]= numerope[1].nmrp_normal_1;
        F[1]= numerope[1].nmrp_normal_2;
        F[2]= numerope[1].nmrp_normal_3;
        F[3]= numerope[1].nmrp_normal_4;

        int u = F[0];
        for(int j = 0; j<5; j++)
            if(u>F[j])
                u = F[j];

        printf("\n\n");
        if(numerope[1].nmrp_preferencial>0)
            Fa[1].Fp = Retorna_inicio(Fp.preferencial) - 1;

        if(u==numerope[1].nmrp_normal_1)
        {
            numerope[1].nmrp_normal_1++;
            infos[i].fila = 1;

            numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
            InsereFila(Fp.normal_1, infos[i].senha);
            Fa[1].F1 = Retorna_inicio(Fp.normal_1) - 1;
            ImprimeFilas(Fp,numerope,infos,p,Fa);
        }
        else
        {
            if(u==numerope[1].nmrp_normal_2)
            {
                numerope[1].nmrp_normal_2++;
                infos[i].fila = 2;
                numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                InsereFila(Fp.normal_2, infos[i].senha);
                Fa[1].F2 = Retorna_inicio(Fp.normal_2) - 1;
                ImprimeFilas(Fp,numerope,infos,p,Fa);
            }
            else
            {
                if(u==numerope[1].nmrp_normal_3)
                {
                    numerope[1].nmrp_normal_3++;
                    infos[i].fila = 3;
                    numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                    InsereFila(Fp.normal_3, infos[i].senha);
                    Fa[1].F3 = Retorna_inicio(Fp.normal_3) - 1;
                    ImprimeFilas(Fp,numerope,infos,p,Fa);
                }
                else
                {
                    if(u==numerope[1].nmrp_normal_4)
                    {
                        numerope[1].nmrp_normal_4++;
                        infos[i].fila = 4;
                        numerope[1].tempo_preferencial = tempo_medio(infos,p,numerope,Fp);
                        InsereFila(Fp.normal_4, infos[i].senha);
                        Fa[1].F4 = Retorna_inicio(Fp.normal_4) - 1;
                        ImprimeFilas(Fp,numerope,infos,p,Fa);
                    }
                }
            }
        }
    }
}

int tempo_medio(informacoes infos[], int p,nmrp numerope[],Filas Fp1)
{
    numerope[1].tempo_preferencial = 0;
    No* q;

    for(int i=0; i < p; i++)
        if(infos[i].fila == 5)
            numerope[1].tempo_preferencial = (float)numerope[1].tempo_preferencial + infos[i].tempo;

    numerope[1].tempo_preferencial = numerope[1].tempo_preferencial  / numerope[1].nmrp_preferencial;

    if(numerope[1].nmrp_preferencial == 0)
        return 0;

    return numerope[1].tempo_preferencial;
}

int main()
{
    int atendimento;
    int avaliacao;
    int parar;
    Filas F1;
    Fila_atendida FA[2];

    F1.preferencial =CriaFila();
    F1.normal_1 =CriaFila();
    F1.normal_2 =CriaFila();
    F1.normal_3 =CriaFila();
    F1.normal_4 =CriaFila();
    srand(time(NULL));

    nmrp numerop[2];
    FA[1].F1=99;
    FA[1].F2=99;
    FA[1].F3=99;
    FA[1].F4=99;
    FA[1].Fp=99;
    numerop[1].nmrp_normal_1 = 0;
    numerop[1].nmrp_normal_2 = 0;
    numerop[1].nmrp_normal_3 = 0;
    numerop[1].nmrp_normal_4 = 0;
    numerop[1].nmrp_preferencial = 0;
    numerop[1].tempo_preferencial = 0;

    informacoes info[100];

    int numero_p = 0;
    int a =1,i=0;
    int *ordena = 1;
    int rodizio;

    do
    {
        printf("\n\n========================================================\n\n");
        printf("                      BANCO VERAN\n\n");
        printf("========================================================\n");
        int preferencia = coleta_info(info,&numero_p);

        organiza(info,numero_p,preferencia,numerop, F1,&ordena,FA);

        printf("Deseja imprimir um relatorio de atendimento? Sim <1>, N\306o <0>\nR: ");
        scanf("%d",&atendimento);
        if(atendimento == 1)
        {
            printf("Pessoas atendidas na Fila Prefrencial = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 5 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 1 = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 1 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 1 Preferenciais = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 6 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 2 = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 2 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 2 Preferenciais = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 7 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 3 = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 3 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 3 Preferenciais = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 8 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 4 = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 4 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);

            printf("\n\nPessoas atendidas na Fila 4 Preferenciais = ");
            for(int b = 0;b<i;b++)
                if(info[b].fila == 9 && info[b].tempo == 0)
                    printf(" %d -",info[b].senha);
        }

        do
        {
            fflush(stdin);
            printf("\n\nDeseja inserir mais algum cliente? Sim <1>, N\306o <0>\nR: ");
            scanf("%d",&parar);
        }while(parar < 0 || parar > 1);

        system("cls");
        i++;
    }while(parar == 1);

    printf("\n\n=============================================================================");
    printf("\n\n\n\tObrigado por utilizar o nosso Sistema,\n\t\t\t\t  Equipe VERAN!\n\n\n");
    printf("=============================================================================\n\n\n");
    printf("\n\nQual a nota do nosso atendimento? Bom:\003\003 <1>, M\202dio \002\002 <2>\nR: ");
    scanf("%d",&avaliacao);

    printf("\n\nObrigado por nos ajudar a evoluir!\n\n\n");

    return 0;
}

