typedef struct map{
    int nCidades;
    int **matrizDistancia;
    char **listaCidades;
}mp;


//conectar cidades indiretamente
void conex(mp *mapa){
    //Passar pela matriz toda
    for(int i = 0; i < mapa->nCidades; i++){
        for(int j = 0; j < mapa->nCidades; j++){
            if(mapa->matrizDistancia[i][j] > 0){
                for(int k = 0; k < mapa->nCidades; k++){
                    if(mapa->matrizDistancia[k][j] > 0){
                        if(mapa->matrizDistancia[k][i] == -1 || mapa->matrizDistancia[k][j]+mapa->matrizDistancia[i][j] < mapa->matrizDistancia[k][i]){
                            mapa->matrizDistancia[k][i] = mapa->matrizDistancia[k][j]+mapa->matrizDistancia[i][j];
                        }
                    }
                }
            }
        }
    }
}


mp *mapaInit(mp *mapa, int x){
    //alocar mapa
    mapa = calloc(1, sizeof(mp *));

    //Ler do usuario
    if(x == 0){
        //Numero de cidades
        int nCidades;
        printf("Informe o numero de cidades que deseja cadastrar: ");
        scanf("%d", &nCidades);
        getc(stdin);

        mapa->nCidades = nCidades;
        mapa->listaCidades = malloc(mapa->nCidades*sizeof(char *));
        mapa->matrizDistancia = malloc(mapa->nCidades*sizeof(int *));

        for(int i = 0; i < mapa->nCidades; i++){
            //alocar string
            mapa->listaCidades[i] = malloc(30*sizeof(char));

            //alocar matriz
            mapa->matrizDistancia[i] = malloc(mapa->nCidades*sizeof(int));
            

            //ler nome da cidade
            printf("Digite o nome da cidade %d: ", i+1);
            fgets(mapa->listaCidades[i], 30, stdin);
            for(int j = 1; j <= strlen(mapa->listaCidades[i]); j++){
                if(mapa->listaCidades[i][j] == '\n' && j > 0){
                    printf("%d %d %c", i, j, mapa->listaCidades[i][j]);
                    mapa->listaCidades[i][j] = '\0';
                }
            }
        }
        system("cls");
        printf("Indique o ID das cidades que desja conectar\nEm seguida informe a distancia entre as cidades\nE por fim informe se eh uma via de mao dupla ou unica (utilizando os digitos 1 e 2)\n");
        //Variaveis temporarias de conexao e distancia
        int src, dest, dist, direc;

        while(scanf("%d %d %d %d", &src, &dest, &dist, &direc) == 4){
            //registrar distancia da cidades
            mapa->matrizDistancia[src][dest] = dist; 
            if(direc == 2){
                mapa->matrizDistancia[dest][src] = dist;
            }
        }


    }else{//ler do arquivo
        //Numero de cidades
        mapa->nCidades = 10;
        mapa->listaCidades = malloc(mapa->nCidades*sizeof(char *));
        mapa->matrizDistancia = malloc(mapa->nCidades*sizeof(int *));

        //Abrir arquivo
        FILE *c = fopen("lib/cidades.txt", "r");
            for(int i = 0; i < mapa->nCidades; i++){
                //alocar string
                mapa->listaCidades[i] = malloc(20*sizeof(char));

                //alocar matriz (e zerar as conexoes)
                mapa->matrizDistancia[i] = malloc(mapa->nCidades*sizeof(int));   
                for(int j = 0; j < mapa->nCidades; j++){
                    if(i != j){
                        mapa->matrizDistancia[i][j] = -1;
                    }else{
                        mapa->matrizDistancia[i][j] = 0;
                    }
                }

                //ler nome da cidade
                fgets(mapa->listaCidades[i], 20, c);
                for(int j = 1; j <= strlen(mapa->listaCidades[i]); j++){
                    if(mapa->listaCidades[i][j] == '\n' && j > 0){
                        printf("%d %d %c", i, j, mapa->listaCidades[i][j]);
                        mapa->listaCidades[i][j] = '\0';
                    }
                }
            }
            fclose(c);

            FILE *m = fopen("lib/mapa.txt", "r");

            //Variaveis temporarias de conexao e distancia
            int src, dest, dist, direc;

            while(fscanf(m, "%d %d %d %d", &src, &dest, &dist, &direc) == 4){
                //registrar distancia da cidades
                mapa->matrizDistancia[src][dest] = dist; 
                if(direc == 2){
                    mapa->matrizDistancia[dest][src] = dist;
                }
            }

        fclose(m);
    }

    //Definir todas as conexoes possiveis
    conex(mapa);

    return mapa;
}



//Mostrar lista de cidades
void printCidades(mp *mapa){
    system("clear");

    for(int i = 0; i < mapa->nCidades; i++){
        printf("%.2d: %s", i+1, mapa->listaCidades[i]);
        printf("\n");
    }

    for(int i = 0; i < mapa->nCidades; i++){
        for(int j = 0; j < mapa->nCidades; j++){
            printf("%d|", mapa->matrizDistancia[i][j]);
        }
        printf("\n");
    }

    printf("aperte enter para continuar...");
    getc(stdin);
    getc(stdin);
}