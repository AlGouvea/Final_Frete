typedef struct item{
    char nome[10];
    int peso;
    float valor;
}it;

//Inicializar lista
it *listaInit(it *lista, int x){
    //Variaveis
    char nomes[10][10] = {"Ferro", "Vidro", "Ouro", "Prata", "Marmore", "Porcelana", "Cobre", "Plastico", "Madeira", "Gesso"};

    //Inicializar lista
    lista = calloc(10, sizeof(it));

    //Definir Materiais
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < strlen(nomes[i]); j++){
            lista[i].nome[j] = nomes[i][j];
        }
    }

    //Definir Pesos e valores
    if(x == 0){ //Input do usuario
        printf("Informe o peso da carga de cada material(Kg):\n");

        //Ler pesos
        for(int i = 0; i < 10; i++){
            printf("Material - %s: ", lista[i].nome);
            scanf("%d", &lista[i].peso);
        }

        system("clear");
        printf("Informe o valor da carga de cada material(R$):\n");

        //Ler valores
        for(int i = 0; i < 10; i++){
            printf("Material - %s / Peso - %dKg: ", lista[i].nome, lista[i].peso);
            scanf("%f", &lista[i].valor);
        }

    }else{//Ler do arquivo

        //Abrir arquivo da lista
        FILE *fp = fopen("lib/lista.txt", "r");

        //Scanear pesos e valores
        for(int i = 0; i < 10; i++){
            fscanf(fp, "%d %f", &lista[i].peso, &lista[i].valor);
        }

        fclose(fp);
    }


    return lista;
}


//Visualizar lista
void printLista(it *lista){
    system("clear");
    printf("Cargas:\n");
    for(int i = 0; i < 10; i++){
        printf("Material: %s - Peso: %d - Valor da carga: %.2f\n", lista[i].nome, lista[i].peso, lista[i].valor);
    }

    printf("\naperte enter para continuar...");
    getc(stdin);
    getc(stdin);
}