#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/items.h"
#include "lib/graph.h"
#include "lib/mergesort.h"
#include "lib/knapsack.h"

//Info do frete
void frete(){
    system("clear");
    printf("Informacoes do Frete:\nVeiculo      Carga Maxima        Custo\n");
    printf("-------------------------------------------------------------------\n");
    printf("Moto         340Kg                1%% do valor da carga a cada 80km\n");
    printf("Carro        580Kg               2,5%% do valor da carga a cada 110km\n");
    printf("Caminhonete  760Kg               15%% do valor da carga\n\n");
    
    printf("aperte enter para continuar...");
    getc(stdin);
    getc(stdin);
}

void menu(it *lista, mp *mapa, int x){
    //variaveis
    int choice, flag = x;

    //Menu de escolhar
    system("clear");
    printf("MENU PRINCIPAL:\n");
    printf("1: Criar lista de materiais\n2: Carregar lista de materiais\n");
    if(flag > 0){
        printf("3: Visualizar lista de materiais\n4: Criar mapa\n5: Carregar mapa\n");
    }
    if(flag > 1){
        printf("6: Visualizar lista de cidades\n7: Informacoes do frete\n8: Escolher rota\n");
    }
    printf("9: Sair\n");

    //escolha
    scanf("%d", &choice);

    switch(choice){
        case 1:
            lista = listaInit(lista, 0);
            flag = 1;
        break;

        case 2:
            lista = listaInit(lista, 1);
           flag = 1; 
        break;
        
        case 3:
            printLista(lista);
        break;
        
        case 4:
            mapa = mapaInit(mapa, 0);
            flag = 2;
        break;
        
        case 5:
            mapa = mapaInit(mapa, 1);
            flag = 2;
        break;

        case 6:
            printCidades(mapa);
        break;

        case 8:
            rota(lista, mapa);
        break;

        case 7:
            frete();
        break;

        case 9:
            exit(0);
        break;
    }

    menu(lista, mapa, flag);
}

int main(){
    //Lista de todos os items (nome/peso/valor)
    it *lista;

    //Mapa das cidades
    mp *mapa;


    menu(lista, mapa, 0);
}