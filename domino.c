#include <stdio.h>
#include <time.h>
#include <stdlib.h>


struct PecasDomino{   // Base das pecas de domino
    int ladoDireito;
    int ladoEsquerdo;
};

struct jogador{
    struct PecasDomino mao[21];
    int tamMao; // Quantas pecas ela tem na mao
};

typedef struct PecasDomino pecasDomino; // Nomeia struct PecasDomino para apenas pecasDomino

pecasDomino mesa[28];

int tamanhoMesa;

struct jogador jogadores[2];

int jogadorAtual;

pecasDomino pecasDisponiveis[28] = {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3},
        {0, 4},
        {0, 5},
        {0, 6},
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 6},
        {2, 2},
        {2, 3},
        {2, 4},
        {2, 5},
        {2, 6},
        {3, 3},
        {3, 4},
        {3, 5},
        {3, 6},
        {4, 4},
        {4, 5},
        {4, 6},
        {5, 5},
        {5, 6},
        {6, 6}
};

int consecutivoPassouVez = 0; // Contar os jogadores consecutivos que passaram a vez


void embaralharPecas(int quantidadePecas){ // Algoritmo de Fisher-Yates
    pecasDomino trocaPeca;
    int indiceRandom;

    srand(time(NULL));

    for(int i = quantidadePecas - 1; i > 0; i--){
        indiceRandom = rand() % (i + 1);
        trocaPeca = pecasDisponiveis[i];
        pecasDisponiveis[i] = pecasDisponiveis[indiceRandom];
        pecasDisponiveis[indiceRandom] = trocaPeca;
    }
}


void distribuicaoPecas(int numeroPecasDisponiveis, int pecasParaDistribuir, int indiceJogador){

    srand(time(NULL)); //Inicializa o gerador de números aleatórios com o valor da função time(NULL).

    for(int i = 0; i < pecasParaDistribuir; i++){
        int pecaAleatoria = rand() % numeroPecasDisponiveis; // Aleatoriza as pecas disponiveis;
        jogadores[indiceJogador].mao[i] = pecasDisponiveis[pecaAleatoria];
        jogadores[indiceJogador].tamMao++;
        
        pecasDisponiveis[pecaAleatoria] = pecasDisponiveis[numeroPecasDisponiveis - 1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
        numeroPecasDisponiveis--; // Diminui a contagem das pecas disponiveis
    }
}


int determinarJogadorInicial(){
    int maiorDuplaJogador1 = 0;
    int indiceMaiorDuplaJogador1 = 0;
    int maiorDuplaJogador2 = 0;
    int indiceMaiorDuplaJogador2 = 0;

    for(int i = 0; i < 7; i++){
        if(jogadores[0].mao[i].ladoEsquerdo == jogadores[0].mao[i].ladoDireito && jogadores[0].mao[i].ladoEsquerdo > maiorDuplaJogador1){
            maiorDuplaJogador1 = jogadores[0].mao[i].ladoEsquerdo;
            indiceMaiorDuplaJogador1 = i;
        }
        if(jogadores[1].mao[i].ladoEsquerdo == jogadores[1].mao[i].ladoDireito && jogadores[1].mao[i].ladoEsquerdo > maiorDuplaJogador2){
            maiorDuplaJogador2 = jogadores[1].mao[i].ladoEsquerdo;
            indiceMaiorDuplaJogador2= i;
        }
    }

    if(maiorDuplaJogador1 > maiorDuplaJogador2){
        mesa[tamanhoMesa] = jogadores[0].mao[indiceMaiorDuplaJogador1]; // está atribuindo a peça escolhida à próxima posição disponível na mesa.
        tamanhoMesa++; // uma nova peça foi adicionada à mesa, portanto, o tamanho da mesa deve ser atualizado.
        
        jogadores[0].mao[indiceMaiorDuplaJogador1] = jogadores[0].mao[jogadores[0].tamMao-1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
        jogadores[0].tamMao--;// Diminui a contagem das pecas disponiveis
        return 1; // Jogador 1 tem a maior dupla, inicia o jogo.
    }
    else if(maiorDuplaJogador2 > maiorDuplaJogador1){
        mesa[tamanhoMesa] = jogadores[1].mao[indiceMaiorDuplaJogador2];
        tamanhoMesa++;
        
        jogadores[1].mao[indiceMaiorDuplaJogador2] = jogadores[1].mao[jogadores[1].tamMao-1];
        jogadores[1].tamMao--;
        return 2; // Jogador 2 tem a maior dupla, inicia o jogo.
    }

    // Se nenhum jogador possui dupla, verifique a soma das peças.
    int maiorSomaJogador1 = 0;
    int indiceMaiorSomaJogador1 = 0;
    int maiorSomaJogador2 = 0;
    int indiceMaiorSomaJogador2 = 0;

    for(int i = 0; i < 7; i++){
        if(maiorSomaJogador1 < jogadores[0].mao[i].ladoEsquerdo + jogadores[0].mao[i].ladoDireito){
            maiorSomaJogador1 = jogadores[0].mao[i].ladoEsquerdo + jogadores[0].mao[i].ladoDireito;
            indiceMaiorSomaJogador1 = i;
        }
        else if(maiorSomaJogador2 < jogadores[1].mao[i].ladoEsquerdo + jogadores[1].mao[i].ladoDireito){
            maiorSomaJogador2 = jogadores[1].mao[i].ladoEsquerdo + jogadores[1].mao[i].ladoDireito;
            indiceMaiorSomaJogador2 = i;
        }
    }

    if(maiorSomaJogador1 > maiorSomaJogador2){
        mesa[tamanhoMesa] = jogadores[0].mao[indiceMaiorSomaJogador1];
        tamanhoMesa++;
        
        jogadores[0].mao[indiceMaiorSomaJogador1] = jogadores[0].mao[jogadores[0].tamMao-1];
        jogadores[0].tamMao--;
        return 1;
    }
    else if(maiorSomaJogador2 > maiorSomaJogador1) {
        mesa[tamanhoMesa] = jogadores[1].mao[indiceMaiorSomaJogador2];
        tamanhoMesa++;
        
        jogadores[1].mao[indiceMaiorSomaJogador2] = jogadores[1].mao[jogadores[1].tamMao-1];
        jogadores[1].tamMao--;
        return 2;
    }

    // Se a soma também for igual, verifique a peça de maior número.
    int maiorNumeroPecaJogador1;
    int maiorNumeroPecaJogador2;

    if(jogadores[0].mao[indiceMaiorSomaJogador1].ladoEsquerdo > jogadores[0].mao[indiceMaiorSomaJogador1].ladoDireito){
        maiorNumeroPecaJogador1 = jogadores[0].mao[indiceMaiorSomaJogador1].ladoEsquerdo;
    }
    else{
        maiorNumeroPecaJogador1 = jogadores[0].mao[indiceMaiorSomaJogador1].ladoDireito;
    }

    if(jogadores[1].mao[indiceMaiorSomaJogador2].ladoEsquerdo > jogadores[1].mao[indiceMaiorSomaJogador2].ladoDireito){
        maiorNumeroPecaJogador2 = jogadores[1].mao[indiceMaiorSomaJogador2].ladoEsquerdo;
    }
    else{
        maiorNumeroPecaJogador2 = jogadores[1].mao[indiceMaiorSomaJogador2].ladoDireito;
    }

    if(maiorNumeroPecaJogador1 > maiorNumeroPecaJogador2){
        mesa[tamanhoMesa] = jogadores[0].mao[indiceMaiorSomaJogador1];
        tamanhoMesa++;
        
        jogadores[0].mao[indiceMaiorSomaJogador1] = jogadores[0].mao[jogadores[0].tamMao-1];
        jogadores[0].tamMao--;
        return 1;
    }
    else{
        mesa[tamanhoMesa] = jogadores[1].mao[indiceMaiorSomaJogador2];
        tamanhoMesa++;
        
        jogadores[1].mao[indiceMaiorSomaJogador2] = jogadores[1].mao[jogadores[1].tamMao-1];
        jogadores[1].tamMao--;
        return 2;
    }
}


void limparTerminal(){
    getchar();  // Serve como um system("pause")
    system("clear");
    printf("\n---------------------------------------------------------------");
}


void imprimirMesa(int tamMesa){
    printf("\n\n\nMesa:\n");
    for (int i = 0; i < tamMesa; i++) {
        printf("[%d|%d] ", mesa[i].ladoEsquerdo, mesa[i].ladoDireito);
    }
    printf("\n");
}


void imprimirPecasJogador(int indJogador){
    for(int i = 0; i < jogadores[indJogador].tamMao; i++){
        printf("%d.[%d|%d]  ", i+1, jogadores[indJogador].mao[i].ladoEsquerdo, jogadores[indJogador].mao[i].ladoDireito);
    }
    printf("\n");
}


void comprarPeca(int indiceJogador, pecasDomino *peca, int *numeroPecasDisponiveis){
    pecasDomino *trocarPeca = malloc(sizeof(pecasDomino)); //Cria uma cópia temporária de uma peça de dominó antes de efetuar uma troca com outra peça

    jogadores[indiceJogador].mao[jogadores[indiceJogador].tamMao] = *peca;
    jogadores[indiceJogador].tamMao++;

    *trocarPeca = pecasDisponiveis[*numeroPecasDisponiveis - 1];
    pecasDisponiveis[*numeroPecasDisponiveis - 1] = *peca; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
    *peca = *trocarPeca;

    (*numeroPecasDisponiveis)--; // Diminui a contagem das pecas disponiveis
}


void inverterPeca(pecasDomino *peca){
    int copiaLado = peca->ladoEsquerdo;
    peca->ladoEsquerdo = peca->ladoDireito;
    peca->ladoDireito = copiaLado;
}


int movimentoValido(pecasDomino *peca){
    if(tamanhoMesa == 0){
        return 1;
    } else{
        if(peca->ladoEsquerdo == mesa[tamanhoMesa - 1].ladoDireito || peca->ladoDireito == mesa[0].ladoEsquerdo){ // Verifica se a peça pode ser jogada no lado esquerdo ou direito da mesa{ // a mesa tiver três peças e tamanho for igual a 3, então a expressão mesa[tamanho - 1] se refere à última peça na mesa, que está no índice 2 (3 - 1).
            return 1;
        }
        if(peca->ladoEsquerdo == mesa[0].ladoEsquerdo || peca->ladoDireito == mesa[tamanhoMesa - 1].ladoDireito){
            inverterPeca(peca);
            return 1;
        }
    }
    return 0;
}


void selecionarLado(int selecaoLado, pecasDomino pecaEscolhida){
    while(1){
        printf("\nEscolha o lado direito (1) ou esquerdo (2): ");
        scanf("%d", &selecaoLado);

        while(selecaoLado < 1  || selecaoLado > 2){
            setbuf(stdin, NULL); // Limpa o buffer (caso o jogador coloque uma letra na opção)

            printf("\nEscolha o lado direito (1) ou esquerdo (2): ");
            scanf("%d", &selecaoLado);
        }

        if(selecaoLado == 1){
            if(mesa[tamanhoMesa-1].ladoEsquerdo == mesa[tamanhoMesa-2].ladoDireito || mesa[tamanhoMesa-1].ladoDireito == mesa[tamanhoMesa-2].ladoDireito){
                if(mesa[tamanhoMesa-2].ladoDireito != mesa[tamanhoMesa-1].ladoEsquerdo){
                    int aux;
                    aux = mesa[tamanhoMesa-1].ladoEsquerdo;
                    mesa[tamanhoMesa-1].ladoEsquerdo = mesa[tamanhoMesa-1].ladoDireito;
                    mesa[tamanhoMesa-1].ladoDireito = aux;
                }
                return;
            }
            else{
                printf("\n\nA peca escolhida nao pode ser jogada no lado direito!\n\n");
            }
        }

        if(selecaoLado == 2){
            if(pecaEscolhida.ladoDireito == mesa[0].ladoEsquerdo || pecaEscolhida.ladoEsquerdo == mesa[0].ladoEsquerdo){
                if(mesa[0].ladoEsquerdo != pecaEscolhida.ladoDireito){
                    int aux;
                    aux = pecaEscolhida.ladoDireito;
                    pecaEscolhida.ladoDireito = pecaEscolhida.ladoEsquerdo;
                    pecaEscolhida.ladoEsquerdo = aux;
                }

                for(int i = tamanhoMesa; i > 0; i--){ //Move os elementos da mesa uma posição para a direção direita
                    mesa[i] = mesa[i - 1];
                }
                mesa[0] = pecaEscolhida;

                return;
            }
            else{
                printf("\n\nA peca escolhida nao pode ser jogada no lado esquerdo!\n\n");
            }
        }
    }
}


void vencedor(){
    if(jogadores[jogadorAtual].tamMao == 0){
        printf("\n\nJogador %d venceu!", jogadorAtual + 1);
        exit(0);
    }
}


void salvarJogo(){
    FILE *mesaTxt, *tamanhoMesaTxt, *jogadoresTxt, *pecasDisponiveisTxt, *jogadorAtualTxt;
    
    mesaTxt = fopen("mesa.txt", "wb+");
    tamanhoMesaTxt = fopen("tamanhoMesa.txt", "wb+");
    jogadoresTxt = fopen("jogadores.txt", "wb+");
    pecasDisponiveisTxt = fopen("pecasDisponiveis.txt", "wb+");
    jogadorAtualTxt = fopen("jogadorAtual.txt", "wb+");
    
    fwrite(&mesa, sizeof(struct PecasDomino)*28,1,mesaTxt);
    fwrite(&tamanhoMesa, sizeof(int),1,tamanhoMesaTxt);
    fwrite(&jogadores, sizeof(struct jogador)*2,1,jogadoresTxt);
    fwrite(&pecasDisponiveis, sizeof(struct PecasDomino)*28,1,pecasDisponiveisTxt);
    fwrite(&jogadorAtual, sizeof(int),1,jogadorAtualTxt);
    
    fclose(mesaTxt);
    fclose(tamanhoMesaTxt);
    fclose(jogadoresTxt);
    fclose(pecasDisponiveisTxt);
    fclose(jogadorAtualTxt);
}


void continuarJogo(){
    FILE *mesaTxt, *tamanhoMesaTxt, *jogadoresTxt, *pecasDisponiveisTxt, *jogadorAtualTxt;
    
    mesaTxt = fopen("mesa.txt", "rb");
    tamanhoMesaTxt = fopen("tamanhoMesa.txt", "rb");
    jogadoresTxt = fopen("jogadores.txt", "rb");
    pecasDisponiveisTxt = fopen("pecasDisponiveis.txt", "rb");
    jogadorAtualTxt = fopen("jogadorAtual.txt", "rb");
    
    fread(&mesa, sizeof(struct PecasDomino)*28,1,mesaTxt);
    fread(&tamanhoMesa, sizeof(int),1,tamanhoMesaTxt);
    fread(&jogadores, sizeof(struct jogador)*2,1,jogadoresTxt);
    fread(&pecasDisponiveis, sizeof(struct PecasDomino)*28,1,pecasDisponiveisTxt);
    fread(&jogadorAtual, sizeof(int),1,jogadorAtualTxt);
    
    fclose(mesaTxt);
    fclose(tamanhoMesaTxt);
    fclose(jogadoresTxt);
    fclose(pecasDisponiveisTxt);
    fclose(jogadorAtualTxt);
}


int main(); // A função main foi declarada para poder ser utilizada na função realizarTurno (Prototipagem)


void realizarTurno(){
    int numeroPecasDisponiveis = 28;
    numeroPecasDisponiveis = numeroPecasDisponiveis - (jogadores[0].tamMao + jogadores[1].tamMao + tamanhoMesa);
    imprimirMesa(tamanhoMesa);
    int indexPecaEscolhida;

    printf("\nJogador %d - Suas pecas: \n", jogadorAtual + 1);
    imprimirPecasJogador(jogadorAtual);
    printf("\nJogador %d - Quantidade de pecas: %d\n", (!jogadorAtual) + 1, jogadores[!jogadorAtual].tamMao);
    printf("Pilha - Quantidade de pecas: %d\n", numeroPecasDisponiveis);

    int cincoAcoes;

    do{
        printf("\nJogar peca (1) | Comprar peca (2) | Passar a vez (3) | Salvar jogo (4) | Menu (5): ");
        scanf("%d", &cincoAcoes);

        setbuf(stdin, NULL);

        if(cincoAcoes != 3){
            consecutivoPassouVez = 0; // Reseta a contagem caso alguém jogue uma peca ou compre uma peca
        }
    } while(cincoAcoes < 1 || cincoAcoes > 5);

    if(cincoAcoes == 1){
        int escolha;

        do{
            printf("\nEscolha uma peca para jogar entre 1 a %d: ", jogadores[jogadorAtual].tamMao);
            scanf("%d", &escolha);

            setbuf(stdin, NULL);
        } while(escolha < 1 || escolha > jogadores[jogadorAtual].tamMao);

        pecasDomino pecaEscolhida = jogadores[jogadorAtual].mao[escolha-1];

        for(indexPecaEscolhida = 0; indexPecaEscolhida < jogadores[jogadorAtual].tamMao; indexPecaEscolhida++){
            if(jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == pecaEscolhida.ladoEsquerdo && jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == pecaEscolhida.ladoDireito) {
                break;  // Sai do loop quando encontra a peça escolhida
            }
        }

        if(movimentoValido(&pecaEscolhida)){
            mesa[tamanhoMesa] = pecaEscolhida;
            tamanhoMesa++;
            
            jogadores[jogadorAtual].mao[escolha-1] = jogadores[jogadorAtual].mao[jogadores[jogadorAtual].tamMao-1];
            jogadores[jogadorAtual].tamMao--;

            int selecaoLado = 0;
            selecionarLado(selecaoLado, pecaEscolhida);
        }
        else{
            printf("\nMovimento invalido. Tente novamente.\n");
            
            limparTerminal();
            realizarTurno(jogadorAtual);
        }
    }
    else if(cincoAcoes == 2){
        if(numeroPecasDisponiveis > 0){
            int pecaAleatoria = rand() % numeroPecasDisponiveis;
            comprarPeca(jogadorAtual, &pecasDisponiveis[pecaAleatoria], &numeroPecasDisponiveis);
            printf("\nJogador %d comprou uma peca!\n", jogadorAtual + 1);
            
            limparTerminal();
            realizarTurno(jogadorAtual);
        }
        else{
            printf("\nNao ha mais pecas para comprar.\n");
            
            limparTerminal();
            realizarTurno(jogadorAtual);
        }
    }
    else if(cincoAcoes == 3){
        if(numeroPecasDisponiveis == 0){
            printf("\nJogador %d passou a vez!\n", jogadorAtual + 1);
            consecutivoPassouVez++;

            if(consecutivoPassouVez == 2){
                printf("\n\nHouve empate!\n");
                exit(0);
            }
        }
        else{
            printf("\nHa pecas na pilha para comprar.\n");
            
            limparTerminal();
            realizarTurno();
        }
    }
    else if(cincoAcoes == 4){
        salvarJogo();
        printf("\nJogo salvo com sucesso!\n");
        
        limparTerminal();
        realizarTurno();
    }
    else if(cincoAcoes == 5){
        system("clear");
        main();
    }
    
    vencedor();
}


int main(){
    int opcaoMenu;

    printf("\n");
    printf("1 - Começar novo jogo\n");
    printf("2 - Continuar jogo\n");
    printf("3 - Sair\n");

    printf("\nEscolha: ");
    scanf("%d", &opcaoMenu);

    setbuf(stdin, NULL);

    switch(opcaoMenu){
        case 1:
            system("clear");

            printf("\n---------------------------------------------------------------\n\n");

            int numeroPecasDisponiveis = 28;
            int pecasParaCadaJogador = 7;
            embaralharPecas(numeroPecasDisponiveis);
            distribuicaoPecas(numeroPecasDisponiveis, pecasParaCadaJogador, 0);
            distribuicaoPecas(numeroPecasDisponiveis - pecasParaCadaJogador, pecasParaCadaJogador,1);

            int jogadorInicial = determinarJogadorInicial();
            
        jogo:
            if(jogadorInicial == 1) {
                printf("Jogador 1 inicia o jogo!\n");
                
                jogadorAtual = 1;
                
                while(1){
                    realizarTurno();  // Jogador 1 vai lançar primeira peça do jogo, logo a jogada em seguida pertence ao jogador 2
                    limparTerminal();
                    
                    jogadorAtual = 0;
                    
                    realizarTurno();
                    limparTerminal();
                    
                    jogadorAtual = 1;
                }
            }
            else{
                printf("Jogador 2 inicia o jogo!\n");
                
                jogadorAtual = 0;
                
                while(1){
                    realizarTurno();  // Jogador 2 vai lançar primeira peça do jogo, logo a jogada em seguida pertence ao jogador 1
                    limparTerminal();
                    
                    jogadorAtual = 1;
                    
                    realizarTurno();
                    limparTerminal();
                    
                    jogadorAtual = 0;
                }
            }

            imprimirMesa(numeroPecasDisponiveis);
            break;

        case 2:
            continuarJogo();
            system("clear");
            printf("\n---------------------------------------------------------------\n\n");
            goto jogo;  // Estrutura de controle para salto de instruções
            break;

        case 3:
            exit(0);
            break;

        default:
            printf("\nValor invalido. Tente novamente.\n");
            main();
    }

    return 0;
}