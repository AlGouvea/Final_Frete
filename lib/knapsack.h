int max(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

float knapsack(it *lista, int m){
    float **memory;

    memory = calloc(10, sizeof(float *));

    mergeSort(lista, 0, 9);

    for(int i = 0; i < 10; i++){
        memory[i] = calloc(m+1, sizeof(float));
        for(int j = 0; j <= m; j++){
            if(i == 0 || j == 0){
                memory[i][j] = 0;
            }else{
                if(lista[i-1].peso > j){
                    memory[i][j] = memory[i-1][j];
                }else{
                    int valor = lista[i-1].valor;
                    int peso = lista[i-1].peso;
                    int expectedValue = valor+memory[i-1][j-peso];

                    memory[i][j] = max(expectedValue, memory[i-1][j]);
                }
            }
        }
    }
    return memory[9][m];
}

//Menor rota e knapsack
void rota(it *lista, mp *mapa){
    system("clear");

    //variaveis
    int opt, origem, dest, distancia;
    float Caminhonete, Moto, Carro, freteCaminhonete, freteMoto, freteCarro;

    //Ler cidades
    printf("Informe o ID da cidade de origem: ");
    scanf("%d", &origem);

    printf("Informe o ID da cidade de destino: ");
    scanf("%d", &dest);


    distancia = mapa->matrizDistancia[origem-1][dest-1];

    if(distancia == -1 || distancia == 0){
        printf("Essa rota nao eh possivel!\n");
        printf("\naperte enter para continuar...");
        getc(stdin);
        getc(stdin);

        return;
    }

    //Fazer os knapsacks
    Moto = knapsack(lista, 340);
    Carro = knapsack(lista, 580);
    Caminhonete = knapsack(lista, 760);

    //Calcular frete
    freteMoto = (((Moto/100)*1)*distancia/80);
    freteCarro = (((Carro/100)*2,5)*distancia/110);
    freteCaminhonete = (Caminhonete/100)*15; 

    //Descontar o frete
    Moto = Moto-freteMoto;
    Carro = Carro-freteCarro;
    Caminhonete = Caminhonete-freteCaminhonete;

    //Definir prioridade
    int choice;
    system("clear");
    printf("Definir veiculo baseado no:\n1: Menor Frete\n2: Maior lucro\n");
    scanf("%d", &choice);
    
    switch(choice){
        case 1://Baseado no menor frete
            if(freteCarro > freteMoto){
                if(freteCaminhonete > freteMoto){
                    printf("O veiculo com menor frete eh o Moto.\nCusto: R$%.2f\n", freteMoto);
                }else{
                    printf("O veiculo com menor frete eh a Caminhonete.\nCusto: R$%.2f\n", freteCaminhonete);
                }
            }else if(freteCarro > freteCaminhonete){
                if(freteCaminhonete > freteMoto){
                    printf("O veiculo com menor frete eh o Moto.\nCusto: R$%.2f\n", freteMoto);
                }else{
                    printf("O veiculo com menor frete eh a Caminhonete.\nCusto: R$%.2f\n", freteCaminhonete);
                }
            }else{
                printf("O veiculo com menor frete eh a Carro.\nCusto: R$%.2f\n", freteCarro);
            }
        break;

        case 2://Baseado no maior lucro
            if(Carro < Moto){
                if(Caminhonete < Moto){
                    printf("O veiculo com maior lucro eh o Moto.\nLucro: R$%.2f\n", Moto);
                }else{
                    printf("O veiculo com maior lucro eh a Caminhonete.\nLucro: R$%.2f\n", Caminhonete);
                }
            }else if(Carro < Caminhonete){
                printf("O veiculo com maior lucro eh a Caminhonete.\nLucro: R$%.2f\n", Caminhonete);
            }else{
                printf("O veiculo com maior lucro eh a Carro.\nLucro: R$%.2f\n", Carro);
            }
        break;

        default:
            system("clear");
            printf("Definir veiculo baseado no:\n1: Menor Frete\n2:Maior lucro\n");
            scanf("%d", &choice);
        break;
    }

    printf("\naperte enter para continuar...");
    getc(stdin);
    getc(stdin);
}