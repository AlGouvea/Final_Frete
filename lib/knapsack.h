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
    float van, carro, caminhonete, freteVan, freteCarro, freteCaminhonete;

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
    carro = knapsack(lista, 340);
    caminhonete = knapsack(lista, 580);
    van = knapsack(lista, 760);

    //Calcular frete
    freteCarro = (((carro/100)*1)*distancia/80);
    freteCaminhonete = (((caminhonete/100)*2,5)*distancia/110);
    freteVan = (van/100)*15; 

    //Descontar o frete
    carro = carro-freteCarro;
    caminhonete = caminhonete-freteCaminhonete;
    van = van-freteVan;

    //Definir prioridade
    int choice;
    system("clear");
    printf("Definir veiculo baseado no:\n1: Menor Frete\n2: Maior lucro\n");
    scanf("%d", &choice);
    
    switch(choice){
        case 1://Baseado no menor frete
            if(freteCaminhonete > freteCarro){
                if(freteVan > freteCarro){
                    printf("O veiculo com menor frete eh o carro.\nCusto: R$%.2f\n", freteCarro);
                }else{
                    printf("O veiculo com menor frete eh a van.\nCusto: R$%.2f\n", freteVan);
                }
            }else if(freteCaminhonete > freteVan){
                if(freteVan > freteCarro){
                    printf("O veiculo com menor frete eh o carro.\nCusto: R$%.2f\n", freteCarro);
                }else{
                    printf("O veiculo com menor frete eh a van.\nCusto: R$%.2f\n", freteVan);
                }
            }else{
                printf("O veiculo com menor frete eh a caminhonete.\nCusto: R$%.2f\n", freteCaminhonete);
            }
        break;

        case 2://Baseado no maior lucro
            if(caminhonete < carro){
                if(van < carro){
                    printf("O veiculo com maior lucro eh o carro.\nLucro: R$%.2f\n", carro);
                }else{
                    printf("O veiculo com maior lucro eh a van.\nLucro: R$%.2f\n", van);
                }
            }else if(caminhonete < van){
                printf("O veiculo com maior lucro eh a van.\nLucro: R$%.2f\n", van);
            }else{
                printf("O veiculo com maior lucro eh a caminhonete.\nLucro: R$%.2f\n", caminhonete);
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