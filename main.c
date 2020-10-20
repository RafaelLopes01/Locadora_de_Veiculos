#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
//CODIGOS GERAL
// Struct cadastro de usu�rios
typedef struct Usuario{
    char nomeCompleto[50];
    char nomeUsuario[25];
    char senha[25];
    struct usuario *proximoUser;
}Usuario;
Usuario *inicioUser = NULL;
    //memset(inicioUser, '\0', (sizeof(inicioUser)));

//Struct Cadastro de clientes
typedef struct Clientes{
    //int idClientes;
    char nome[50], cpfCnpj [15], parceiro[5],telefone[12], endereco[50], bairro[25], cidade[25], cep[10], uf[4];
    int idade;
    struct Clientes *proximoCli;
}Clientes;
Clientes *inicioCli = NULL;

//Struct Cadastro de Ve�culos
typedef struct Veiculos{
    //int idVeiculos;
    char marca[101], modelo[101], placa[10], combustivel[10], status[31], categoria[31];
    //double km;
    struct Veiculos *inicioVei;
    struct Veiculos *proximoVei;
}Veiculos;
Veiculos *inicioVei = NULL;

//Struct Cadastro de loca��es
typedef struct Locacao{
    int idLocacao, diarias;
    float valorLoc;
    char modelo[101], placa[10], nome[101], cpfCnpj[15], dataIni[10], horaIni[10], dataFim[10], horaFim[10], status[15];
    struct Locacao *inicioLoc;
    struct Locacao *proximoLoc;
}Locacao;
idLocacao = 0;
Locacao *inicioLoc = NULL;

typedef struct sData{
    int dia;
    int mes;
    int ano;
}dma;
dma  dataLocacao,dataRetorno;

//TABELA DE PRE�OS
float vlrEcon, vlrInter, vlrLuxo;// Pre�o Econ�mico, Intermedi�rio e Luxo

//LINHA DE 80 POSI��O COM *.
void linhaEstrela (){
    int x;
    for(x = 0; x < 80;x++){
        printf("*");
    }
    printf("\n");
}

//LINHA DE 80 POSI��O COM -.
void linha (){
    int x;
    for(x = 0; x < 80;x++){
        printf("-");
    }
    printf("\n");
}

//LAYOUT DO MENU
void menu (){
    printf("\n");
    linhaEstrela();
    printf("                                ALUGUE F�CIL  \n");
    linhaEstrela();
}

void subMenu (){
    printf(" 0 SAIR  | 1 VE�CULOS  | 2 CLIENTES  | 3 LOCAC�ES  | 4 USU�RIOS  | 5 RELAT�RIOS\n");
    linhaEstrela();
}

//LAYOUT DE TELA
void tela (char tela[101]){
    linha();
    printf("%s\n", tela);
    linha();
    printf(" 0 - SAIR\n 1 - NOVO\n 2 - EXIBIR REGISTROS\n 3 - PESQUISAR\n");
    linha();
}

void telaLocacoes (char telaLocacoes[101]){
    linha();
    printf("%s\n", telaLocacoes);
    linha();
    printf(" 0 - SAIR\n 1 - NOVO\n 2 - EXIBIR REGISTROS\n 3 - PESQUISAR\n 4 - PRE�OS\n");
    linha();
}

//LAYOUT DE OP��O DE TELAS
void opcaoTelas (int opcao){
    switch(opcao){
        case 1 :
            tela(" VE�CULOS");
            break;
        case 2 :
            tela(" CLIENTES");
            break;
        case 3 :
            telaLocacoes(" LOCAC�ES");
            break;
        case 4 :
            tela(" USU�RIOS");
            break;
    }
}
void importaUsuarios(){
    char linha[101], nome[50], usuario2[25], senha[25];
    FILE *arq;
    arq = fopen("Usuarios.txt","r");
    if (arq == NULL){
        menu();
        subMenu();
        fprintf(stderr, "\n Erro: N�o foi poss�vel carregar os usu�rios!\n\n");
        printf(" ");
        system("pause");
        system("cls");
        return 1;
    }
    while (!feof(arq)){
        memset(linha, '\0', (sizeof(linha)));
        memset(nome, '\0', (sizeof(nome)));
        memset(usuario2, '\0', (sizeof(usuario2)));
        memset(senha, '\0', (sizeof(senha)));
        fgets(linha, "%101s", arq);
        if (linha[1] == NULL){
            break;
        }
        char *Ponteiro = NULL;
        Ponteiro = strtok(linha, "|");
        strcat(nome, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(usuario2, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(senha, Ponteiro);
        senha[strlen(senha)-1]='\0';
        Usuario *usuario = (Usuario*) malloc(sizeof(Usuario));
        strcpy(usuario->nomeCompleto, nome);
        strcpy(usuario->nomeUsuario, usuario2);
        strcpy(usuario->senha, senha);
        usuario->proximoUser = NULL;
        if (inicioUser == NULL){
            inicioUser = usuario;
        }else{
            usuario->proximoUser = inicioUser;
            inicioUser = usuario;
        }
    }
    fclose(arq);
}
void importaVeiculos(){
    char linha[121], marca[25], modelo[25], placa[10], combustivel[10], status[25], categoria[25];
    FILE *arq;
    arq = fopen("Veiculos.txt","r");
    if (arq == NULL){
        menu();
        subMenu();
        fprintf(stderr, "\n Erro: N�o foi poss�vel carregar os ve�culos!\n\n");
        system("pause");
        system("cls");
        return 1;
    }
    while (!feof(arq)){
        memset(linha, '\0', (sizeof(linha)));
        memset(marca, '\0', (sizeof(marca)));
        memset(modelo, '\0', (sizeof(modelo)));
        memset(placa, '\0', (sizeof(placa)));
        memset(combustivel, '\0', (sizeof(combustivel)));
        memset(status, '\0', (sizeof(status)));
        memset(categoria, '\0', (sizeof(categoria)));
        fgets(linha, "%121s", arq);
        if (linha[1] == NULL){
            break;
        }
        char *Ponteiro = NULL;
        Ponteiro = strtok(linha, "|");
        strcat(marca, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(modelo, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(placa, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(combustivel, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(categoria, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        //categoria[strlen(categoria)-1]='\0';
        strcat(status, Ponteiro);
        status[strlen(status)-1]='\0';
        Veiculos *veiculo = (Veiculos*) malloc(sizeof(Veiculos));
        strcpy(veiculo->marca, marca);
        strcpy(veiculo->modelo, modelo);
        strcpy(veiculo->placa, placa);
        strcpy(veiculo->combustivel, combustivel);
        strcpy(veiculo->status, status);
        strcpy(veiculo->categoria, categoria);
        veiculo->proximoVei = NULL;
        if (inicioVei == NULL){
            inicioVei = veiculo;
        }else{
            veiculo->proximoVei = inicioVei;
            inicioVei = veiculo;
        }
    }
    fclose(arq);
}

void importaClientes(){
    int idadeCli;
    char linha[200], nomeCli[50],telefoneCli[12], cpfCnpjCli[15], parceiro[5], enderecoCli[50], bairroCli[25], cidadeCli[25], cepCli[10], ufCli[4];
    FILE *arq;
    arq = fopen("Clientes.txt","r");
    if (arq == NULL){
        menu();
        subMenu();
        fprintf(stderr, "\n Erro: N�o foi poss�vel carregar os clientes!\n\n");
        printf(" ");
        system("pause");
        system("cls");
        return 1;
    }
    while (!feof(arq)){
        memset(linha, '\0', (sizeof(linha)));
        memset(nomeCli, '\0', (sizeof(nomeCli)));
        memset(parceiro, '\0', (sizeof(parceiro)));
        memset(cpfCnpjCli, '\0', (sizeof(cpfCnpjCli)));
        memset(telefoneCli, '\0', (sizeof(telefoneCli)));
        memset(enderecoCli, '\0', (sizeof(enderecoCli)));
        memset(bairroCli, '\0', (sizeof(bairroCli)));
        memset(cidadeCli, '\0', (sizeof(cidadeCli)));
        memset(cepCli, '\0', (sizeof(cepCli)));
        memset(ufCli, '\0', (sizeof(ufCli)));
        fgets(linha, "%121s", arq);
        if (linha[1] == NULL){
            break;
        }
        char *Ponteiro = NULL;
        Ponteiro = strtok(linha, "|");
        strcat(parceiro, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(telefoneCli, Ponteiro);
        telefoneCli[strlen(telefoneCli)-1]='\0';
        Ponteiro = strtok(NULL, "|");
        strcat(nomeCli, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(cpfCnpjCli, Ponteiro);
        cpfCnpjCli[strlen(cpfCnpjCli)-1]='\0';

        //parceiro[strlen(parceiro)-1]

        Ponteiro = strtok(NULL, "|");
        idadeCli =  atoi(Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(enderecoCli, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(bairroCli, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(cidadeCli, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(cepCli, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(ufCli, Ponteiro);
        ufCli[strlen(ufCli)-1]='\0';
        Clientes *clientes = (Clientes*) malloc(sizeof(Clientes));
        strcpy(clientes->nome, nomeCli);
        strcpy(clientes->cpfCnpj, cpfCnpjCli);
        strcpy(clientes->parceiro, parceiro);
        strcpy(clientes->telefone, telefoneCli);
        clientes->idade = idadeCli;
        strcpy(clientes->endereco, enderecoCli);
        strcpy(clientes->bairro, bairroCli);
        strcpy(clientes->cidade, cidadeCli);
        strcpy(clientes->cep, cepCli);
        strcpy(clientes->uf, ufCli);
        clientes->proximoCli = NULL;
        if (inicioCli == NULL){
            inicioCli = clientes;
        }else{
            clientes->proximoCli = inicioCli;
            inicioCli = clientes;
        }
    }
    fclose(arq);
}
//EFETUA O CADASTRO DE VEICULOS
void cadVeiculos (int tela){
    FILE *arq;
    int opcao, op, dif, gravar;
    char marca[25], modelo[25], placa[10], combustivel[10], status[25], categoria[25];
    //double km;//Kilometragem
    Veiculos *inicioVei = NULL;
        do{
            Veiculos *auxVei = inicioVei;
            gravar = 0;
            system("cls");
            menu();
            opcaoTelas(1);
            printf("\n TELA - DIGITE O N�MERO DA OPC�O ESCOLHIDA: ");
            scanf("%d", &opcao);
            getchar();
            switch(opcao){
                case 0 :
                    //printf ("SAIR");
                    break;

                case 1 :
                    op = 0;
                    system("cls");
                    menu();
                    linha();
                    printf ("                            CADASTRO DE VE�CULO\n");
                    linha();
                    printf("\n MARCA: ");
                    fgets(marca, sizeof(marca), stdin);
                    marca[strlen(marca)-1]='\0';
                    fflush(stdin);
                    printf("\n MODELO: ");
                    fgets(modelo,sizeof(modelo) , stdin);
                    modelo[strlen(modelo)-1]='\0';
                    fflush(stdin);
                    printf("\n PLACA(Formato XXX0000): ");
                    fgets(placa,sizeof(placa) , stdin);
                    placa[strlen(placa)-1]='\0';
                    fflush(stdin);
                    Veiculos *check = inicioVei;
                    while (check != NULL){
                        dif = strcmp(check->placa, placa);
                        if (dif == 0){
                            printf("\n Ve�culo j� cadastrado!\n\n");
                            free(check);
                            op = 1;
                            break;
                        }else{
                            check = check->proximoVei;
                        }
                    }
                    if (op != 1){
                        do{
                            printf("\n COMBUST�VEL: 1 - Gasolina | 2 - Etanol | 3 - Flex: ");
                            scanf("%d", &op);
                            fflush(stdin);
                            switch (op) {
                                case 1:
                                    strcpy(combustivel, "Gasolina");
                                    break;

                                case 2:
                                    strcpy(combustivel, "Etanol");
                                    break;

                                case 3:
                                    strcpy(combustivel, "Flex");
                                    break;

                                default:
                                    printf("\n Op��o inv�lida!");//idade
                                    break;
                            }
                        }while ((op != 1) && (op != 2) && (op != 3));
                        do{
                            printf("\n CATEGORIA: 1 - Economica 2 - Intermediaria 3 - Luxo: ");
                            scanf("%d", &op);
                            fflush(stdin);
                            switch (op){
                                case 1:
                                    strcpy(categoria, "Economica");
                                    break;

                                case 2:
                                    strcpy(categoria, "Intermediaria");
                                    break;

                                case 3:
                                    strcpy(categoria, "Luxo");
                                    break;

                                default:
                                    printf("\n Op��o inv�lida!");//idade
                                    //printf("\n\n\n ");
                                    //system("pause");)
                            }
                        }while ((op != 1) && (op != 2) && (op != 3));
                        printf("\n\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
                        scanf("%d", &op);
                        if (dif != 0 && op == 1){
                            Veiculos *veiculo = (Veiculos*) malloc(sizeof(Veiculos));
                            strcpy(veiculo->marca, marca);
                            strcpy(veiculo->modelo, modelo);
                            strcpy(veiculo->placa, placa);
                            strcpy(veiculo->combustivel, combustivel);
                            strcpy(veiculo->categoria, categoria);
                            strcpy(veiculo->status, "Livre");
                            veiculo->proximoVei = NULL;
                            if (inicioVei == NULL){
                                inicioVei = veiculo;
                            }else{
                                veiculo->proximoVei = inicioVei;
                                inicioVei = veiculo;
                            }
                            gravar = 1;
                            printf("\n\n Ve�culo cadastrado com sucesso!\n\n");
                        }else{
                            printf("\n\n Cadastro cancelado!\n\n");
                        }
                    }
                    printf(" ");
                    system("pause");
                    break;

                case 2 :
                    system("cls");
                    menu();
                    linha();
                    printf ("                            VE�CULOS CADASTRADOS \n");
                    auxVei = inicioVei;
                    if (auxVei != NULL){
                        while (auxVei != NULL){
                            linha();
                            printf(" MARCA: %s\n", auxVei->marca);
                            printf(" MODELO: %s\n", auxVei->modelo);
                            printf(" PLACA: %s\n", auxVei->placa);
                            printf(" COMBUSTIVEL: %s\n", auxVei->combustivel);
                            printf(" CATEGORIA: %s\n", auxVei->categoria);
                            printf(" STATUS: %s\n", auxVei->status);
                            auxVei = auxVei->proximoVei;
                        }
                        printf("\n\n\n ");
                        system("pause");
                    }else{
                        printf("\n N�o h� ve�culos cadastrados!\n");
                        printf("\n\n");
                        printf(" ");
                        system("pause");
                    }
                    free(auxVei);
                    break;//uUsuarioCad[x].iIdUser = x+1;

                case 3 :
                    do{
                        system("cls");
                        menu();
                        linha();
                        printf ("                            PESQUISAR VE�CULO \n");
                        linha();
                        Veiculos *pesq = inicioVei;
                        Veiculos *anterior = inicioVei;
                        dif = -1;
                        if (pesq != NULL){
                            printf("\n Digite placa para pesquisa: ");
                            fgets(placa,sizeof(placa),stdin);
                            placa[strlen(placa)-1]='\0';
                            while (pesq != NULL || dif == 0){
                                dif = strcmp(pesq->placa,placa);
                                if (dif == 0){
                                    linha();
                                    printf(" MARCA: %s\n", pesq->marca);
                                    printf(" MODELO: %s\n", pesq->modelo);
                                    printf(" PLACA: %s\n", pesq->placa);
                                    printf(" COMBUSTIVEL: %s\n", pesq->combustivel);
                                    printf(" CATEGORIA: %s\n", pesq->categoria);
                                    printf(" STATUS: %s\n\n\n", pesq->status);
                                    break;
                                }else{
                                    if (dif != 0){
                                        anterior = pesq;
                                        pesq = pesq->proximoVei;
                                    }
                                }
                            }
                        }else{
                            printf("\n N�o h� ve�culos cadastrados!\n\n\n");
                            printf(" ");
                            system("pause");
                            break;
                        }
                        if (dif == 0){
                            do{
                                printf("\n DIGITE: 0 - SAIR | 1 - ALTERAR | 2 - EXCLUIR: ");
                                scanf("%d", &op);
                                getchar();
                                switch(op){
                                    case 0:
                                        break;
                                    case 1://Alterar cadastro
                                        printf("\n MARCA: ");
                                        fgets(marca, sizeof(marca), stdin);
                                        marca[strlen(marca)-1]='\0';
                                        fflush(stdin);
                                        strcpy(pesq->marca, marca);
                                        printf("\n MODELO: ");
                                        fgets(modelo,sizeof(modelo), stdin);
                                        modelo[strlen(modelo)-1]='\0';
                                        fflush(stdin);
                                        strcpy(pesq->modelo, modelo);
                                        printf("\n PLACA(Formato XXX0000): ");
                                        fgets(placa,sizeof(placa), stdin);
                                        placa[strlen(placa)-1]='\0';
                                        fflush(stdin);
                                        strcpy(pesq->placa, placa);
                                        do{
                                            printf("\n COMBUST�VEL: 1 - Gasolina | 2 - Etanol | 3 - Flex: ");
                                            scanf("%d", &op);
                                            fflush(stdin);
                                            switch (op) {
                                                case 1:
                                                    strcpy(combustivel, "Gasolina");
                                                    break;

                                                case 2:
                                                    strcpy(combustivel, "Etanol");
                                                    break;

                                                case 3:
                                                    strcpy(combustivel, "Flex");
                                                    break;

                                                default:
                                                    printf("\n Op��o inv�lida!");//idade
                                                    break;
                                            }
                                        }while ((op != 1) && (op != 2) && (op != 3));
                                        do{
                                            printf("\n CATEGORIA: 1 - Economica 2 - Intermediaria 3 - Luxo: ");
                                            scanf("%d", &op);
                                            fflush(stdin);
                                            switch (op){
                                                case 1:
                                                    strcpy(categoria, "Economica");
                                                    break;

                                                case 2:
                                                    strcpy(categoria, "Intermediaria");
                                                    break;

                                                case 3:
                                                    strcpy(categoria, "Luxo");
                                                    break;

                                                default:
                                                    printf("\n Op��o inv�lida!");//idade
                                                    //printf("\n\n\n ");
                                                    //system("pause");)
                                            }
                                        }while ((op != 1) && (op != 2) && (op != 3));
                                        op = 0;
                                        gravar = 1;
                                        printf("\n\n Registro alterado!\n\n");
                                        printf(" ");
                                        system("pause");
                                        break;

                                    case 2://Excluir cadastro
                                        if (pesq == anterior){
                                            if (pesq->proximoVei == NULL){
                                                inicioVei = NULL;
                                            }else{
                                                inicioVei = pesq->proximoVei; //pesq = NULL;
                                            }

                                        }else{
                                            if (pesq->proximoVei == NULL){
                                                anterior->proximoVei = NULL;
                                                pesq = NULL;
                                            }else{
                                                anterior->proximoVei = pesq->proximoVei;
                                                pesq = NULL;
                                            }
                                        }
                                        op = 0;
                                        gravar = 1;
                                        printf("\n Registro exclu�do!\n\n");
                                        printf(" ");
                                        system("pause");
                                        break;

                                    default :
                                        printf("\n Op��o inv�lida!");
                                        fflush(stdin);
                                        break;
                                    }
                                }while (op != 0);
                            }else{
                                printf("\n Placa inv�lida!\n\n\n");
                                printf(" ");
                                system("pause");
                                break;
                            }
                    }while (op != 0);
                break;
            default :
                printf("\n Op��o inv�lida!");
                fflush(stdin);
                printf(" ");
                system("pause");
                break;
        }
        if (gravar == 1){
            Veiculos *veiculo = inicioVei;
            arq = fopen("Veiculos.txt", "w");
            if(arq == NULL){
                printf("Erro, n�o foi poss�vel abrir o arquivo\n");
                system("pause");
            }else{
                while (veiculo != NULL){
                    fprintf(arq, "%s|%s|%s|%s|%s|%s\n", veiculo->marca, veiculo->modelo, veiculo->placa, veiculo->combustivel, veiculo->categoria, veiculo->status);
                    veiculo = veiculo->proximoVei;
                }
            }
            fclose(arq);
            gravar = 0;
        }
    }while(opcao != 0);
    system("cls");
}
//EFETUA O CADASTRO DE CLIENTES
void cadClientes (int tela){
    int op, opcao, dif, idadeCli, gravar;
    char nomeCli[50], cpfCnpjCli[15], parceiro[5],telefoneCli[12], enderecoCli[50], bairroCli[25], cidadeCli[25], cepCli[10], ufCli[4];
    FILE *arq;
    do{
        system("cls");
        menu();
        opcaoTelas(2);
        printf("\n TELA - DIGITE O N�MERO DA OPC�O ESCOLHIDA: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 0 :
                break;
            case 1 :
                    do{
                        gravar = 0;
                        system("cls");
                        menu();
                        linha();
                        printf ("                             CADASTRO DE CLIENTE\n");
                        linha();
                        do{
                            printf("\n Parceiro? 0 - N�o | 1 - Sim: ");
                            scanf("%d", &op);
                            fflush(stdin);
                            switch (op){
                                case 0:
                                    strcpy(parceiro, "Nao");
                                    printf("\n Op��o escolhida: N�o\n");
                                    op = 0;
                                    break;

                                case 1:
                                    strcpy(parceiro, "Sim");
                                    printf("\n Op��o escolhida: Sim\n");
                                    op = 0;
                                    break;

                                default :
                                    printf("\n Op��o inv�lida!\n\n\n");
                                    op = -1;
                                    break;
                            }
                            if (op == -1){
                                break;
                            }
                        }while (op != 0);
                        if (op == -1){
                            break;
                        }
                        //op = -1;
                        printf("\n Nome Completo: ");
                        fgets(nomeCli, sizeof(nomeCli), stdin);
                        nomeCli[strlen(nomeCli)-1]='\0';
                        fflush(stdin);
                        printf("\n CPF/CNPJ: ");
                        fgets(cpfCnpjCli, sizeof(cpfCnpjCli), stdin);
                        cpfCnpjCli[strlen(cpfCnpjCli)-1]='\0';
                        fflush(stdin);
                        Clientes *check = inicioCli;
                        dif = -1;
                        while (check != NULL){
                            dif = strcmp(check->cpfCnpj, cpfCnpjCli);
                            if (dif == 0){
                                printf("\n Cliente j� cadastrado!\n\n\n");
                                check = NULL;
                                break;
                            }else{
                                check = check->proximoCli;
                            }
                        }
                        if (dif == 0){
                            break;
                        }
                        free(check);
                        printf("\n Telefone(somente n�meros): ");
                        fgets(telefoneCli, sizeof(telefoneCli), stdin);
                        telefoneCli[strlen(telefoneCli)-1]='\0';
                        fflush(stdin);
                        printf("\n Idade do motorista: ");
                        scanf("%d", &idadeCli);
                        fflush(stdin);
                        printf("\n Endere�o: ");
                        fgets(enderecoCli, sizeof(enderecoCli), stdin);
                        enderecoCli[strlen(enderecoCli)-1]='\0';
                        fflush(stdin);
                        printf("\n Bairro: ");
                        fgets(bairroCli, sizeof(bairroCli), stdin);
                        bairroCli[strlen(bairroCli)-1]='\0';
                        fflush(stdin);
                        printf("\n Cidade: ");
                        fgets(cidadeCli, sizeof(cidadeCli), stdin);
                        cidadeCli[strlen(cidadeCli)-1]='\0';
                        fflush(stdin);
                        printf("\n CEP: ");
                        fgets(cepCli, sizeof(cepCli), stdin);
                        cepCli[strlen(cepCli)-1]='\0';
                        fflush(stdin);
                        printf("\n UF: ");
                        fgets(ufCli, sizeof(ufCli), stdin);
                        ufCli[strlen(ufCli)-1]='\0';
                        fflush(stdin);
                        op = 0;
                        if ((strlen(nomeCli) ==  0)||(strlen(cpfCnpjCli) == 0)||(strlen(telefoneCli) == 0)||(strlen(enderecoCli) == 0)||(strlen(bairroCli) == 0)||(strlen(cidadeCli) == 0)||(strlen(cepCli) == 0)||(strlen(ufCli) == 0)){
                            printf("\n Todos o campos s�o de preenchimento Obrigat�rio!\n\n\n");
                            printf(" ");
                            op = -1;
                           // printf(" ");
                            //system("pause");
                            break;
                        }else{
                            printf("\n\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
                            scanf("%d", &op);
                            if (dif != 0 && op == 1){
                                Clientes *cliente = (Clientes*) malloc(sizeof(Clientes));
                                strcpy(cliente->nome, nomeCli);
                                strcpy(cliente->cpfCnpj, cpfCnpjCli);
                                strcpy(cliente->parceiro, parceiro);
                                strcpy(cliente->telefone, telefoneCli);
                                cliente->idade = idadeCli;
                                strcpy(cliente->endereco, enderecoCli);
                                strcpy(cliente->cidade, cidadeCli);
                                strcpy(cliente->bairro, bairroCli);
                                strcpy(cliente->cep, cepCli);
                                strcpy(cliente->uf, ufCli);
                                cliente->proximoCli = NULL;
                                if (inicioCli == NULL){
                                    inicioCli = cliente;
                                }else{
                                    cliente->proximoCli = inicioCli;
                                    inicioCli = cliente;
                                }
                                gravar = 1;
                                printf("\n\n Cliente cadastrado com sucesso!\n\n");
                            }else{
                                printf("\n\n Cadastro cancelado\n\n!");
                            }
                        }
                    }while ((op == -1));
                    getchar();
                    printf(" ");
                    system("pause");
                    break;
            case 2 :
                    system("cls");
                    menu();
                    linha();
                    printf ("                            CLIENTES CADASTRADOS \n");
                    Clientes *aux = inicioCli;
                    if (aux != NULL){
                        while (aux != NULL){
                            linha();
                            printf(" NOME: %s\n", aux->nome);
                            printf(" CPF/CNPJ: %s\n", aux->cpfCnpj);
                            printf(" PARCEIRO: %s\n", aux->parceiro);
                            printf(" TELEFONE: %s\n", aux->telefone);
                            printf(" IDADE DO MORTORISTA: %d\n", aux->idade);
                            printf(" ENDERE�O: %s\n", aux->endereco);
                            printf(" BAIRRO: %s\n", aux->bairro);
                            printf(" CIDADE: %s\n", aux->cidade);
                            printf(" CEP: %s\n", aux->cep);
                            printf(" UF: %s\n", aux->uf);
                            aux = aux->proximoCli;
                        }
                        printf("\n\n");
                        system("pause");
                    }else{
                        printf("\n N�o h� clientes cadastrados!\n");
                        printf("\n\n");
                        system("pause");
                    }
                    free(aux);
                break;
            case 3 :
                    do{
                        system("cls");
                        menu();
                        linha();
                        printf ("                            PESQUISAR CLIENTES \n");
                        linha();
                        Clientes *pesq = inicioCli;
                        Clientes *anterior = inicioCli;
                        dif = -1;
                        if (pesq != NULL){
                            printf("\n Digite o CPF para pesquisa: ");
                            fgets(cpfCnpjCli,sizeof(cpfCnpjCli),stdin);
                            cpfCnpjCli[strlen(cpfCnpjCli)-1]='\0';
                            fflush(stdin);
                            while (pesq != NULL || dif == 0){
                                dif = strcmp(pesq->cpfCnpj,cpfCnpjCli);
                                if (dif == 0){
                                    linha();
                                    printf(" NOME: %s\n", pesq->nome);
                                    printf(" CPF/CNPJ: %s\n", pesq->cpfCnpj);
                                    printf(" PARCEIRO: %s\n", pesq->parceiro);
                                    printf(" TELEFONE: %s\n", pesq->telefone);
                                    printf(" IDADE DO MOTORISTA: %d\n", pesq->idade);
                                    printf(" ENDERE�O: %s\n", pesq->endereco);
                                    printf(" BAIRRO: %s\n", pesq->bairro);
                                    printf(" CIDADE: %s\n", pesq->cidade);
                                    printf(" CEP: %s\n", pesq->cep);
                                    printf(" UF: %s\n", pesq->uf);
                                    break;
                                }else{
                                    if (dif != 0){
                                        anterior = pesq;
                                        pesq = pesq->proximoCli;
                                    }
                                }
                            }
                        }else{
                            printf("\n N�o h� clientes cadastrados!\n\n\n");
                            system("pause");
                            break;
                        }
                        if (dif == 0){
                            do{
                                printf("\n DIGITE: 0 - SAIR | 1 - ALTERAR | 2 - EXCLUIR: ");
                                scanf("%d", &op);
                                getchar();
                                switch(op){
                                    case 0:
                                        break;

                                    case 1://Alterar cadastro
                                        do{
                                            printf("\n Parceiro? 0 - N�o | 1 - Sim: ");
                                            scanf("%d", &op);
                                            fflush(stdin);
                                            switch (op){
                                                case 0:
                                                strcat(parceiro, "Nao");
                                                    op = 0;
                                                    printf("\n Op��o escolhida: N�o");
                                                    break;
                                                case 1:
                                                    strcat(parceiro, "Sim");
                                                    printf("\n Op��o escolhida: Sim");
                                                    op = 0;
                                                    break;
                                                default :
                                                    printf("\n Op��o inv�lida!\n\n");
                                                    break;
                                            }
                                        }while (op != 0);
                                        printf("\n Nome Completo: ");
                                        fgets(nomeCli, sizeof(nomeCli), stdin);
                                        nomeCli[strlen(nomeCli)-1]='\0';
                                        fflush(stdin);
                                        printf("\n CPF/CNPJ: ");
                                        fgets(cpfCnpjCli, sizeof(cpfCnpjCli), stdin);
                                        cpfCnpjCli[strlen(cpfCnpjCli)-1]='\0';
                                        fflush(stdin);
                                        printf("\n Telefone(somente n�meros): ");
                                        fgets(telefoneCli, sizeof(telefoneCli), stdin);
                                        fflush(stdin);
                                        printf("\n Idade do motorista: ");
                                        scanf("%d", &idadeCli);
                                        fflush(stdin);
                                        printf("\n Endere�o: ");
                                        fgets(enderecoCli, sizeof(enderecoCli), stdin);
                                        enderecoCli[strlen(enderecoCli)-1]='\0';
                                        fflush(stdin);
                                        printf("\n Bairro: ");
                                        fgets(bairroCli, sizeof(bairroCli), stdin);
                                        bairroCli[strlen(bairroCli)-1]='\0';
                                        fflush(stdin);
                                        printf("\n Cidade: ");
                                        fgets(cidadeCli, sizeof(cidadeCli), stdin);
                                        cidadeCli[strlen(cidadeCli)-1]='\0';
                                        fflush(stdin);
                                        printf("\n CEP: ");
                                        fgets(cepCli, sizeof(cepCli), stdin);
                                        cepCli[strlen(cepCli)-1]='\0';
                                        fflush(stdin);
                                        printf("\n UF: ");
                                        fgets(ufCli, sizeof(ufCli), stdin);
                                        ufCli[strlen(ufCli)-1]='\0';
                                        fflush(stdin);
                                        op = 0;
                                        gravar = 1;
                                        printf("\n\n Registro alterado!\n\n");
                                        system("pause");
                                        break;

                                    case 2://Excluir cadastro
                                        if (pesq == anterior){
                                            if (pesq->proximoCli == NULL){
                                                inicioCli = NULL;
                                            }else{
                                                inicioCli = pesq->proximoCli;
                                            }
                                        }else{
                                            if (pesq->proximoCli == NULL){
                                                anterior->proximoCli = NULL;
                                                pesq = NULL;
                                            }else{
                                                anterior->proximoCli = pesq->proximoCli;
                                                pesq = NULL;
                                            }
                                        }
                                        op = 0;
                                        gravar = 1;
                                        printf("\n Registro exclu�do!\n\n");
                                        printf(" ");
                                        system("pause");
                                        break;
                                    default :
                                        printf("\n Op��o inv�lida!\n\n");
                                        fflush(stdin);
                                        printf(" ");
                                        system("pause");
                                        break;
                                    }
                                }while (op != 0);
                            }else{
                                printf("\n CPF inv�lido!\n");
                                printf(" ");
                                system("pause");
                                break;
                            }
                    }while (op != 0);
                break;
            default :
                printf("\n Op��o inv�lida!");//idade
                fflush(stdin);
                printf(" ");
                system("pause");
                break;
        }
        if (gravar == 1){
            Clientes *cliente = inicioCli;
            arq = fopen("Clientes.txt", "w");
            if(arq == NULL){
                printf("Erro, n�o foi poss�vel abrir o arquivo clientes\n");
                printf(" ");
                system("pause");
            }else{
                while (cliente != NULL){
                fprintf(arq, "%s|%s|%s|%s|%d|%s|%s|%s|%s|%s\n", cliente->parceiro ,cliente->telefone , cliente->nome, cliente->cpfCnpj, cliente->idade, cliente->endereco, cliente->bairro, cliente->cidade, cliente->cep, cliente->uf);
                cliente = cliente->proximoCli;
                }
            }
            fclose(arq);
            gravar = 0;
        }
    }while(opcao != 0);
    system("cls");
}
// EFETUA O CADASTRO DE LOCACOES
void cadLocacao(){
    float total; // Calcular total da loca��o
    float desconto;//Fator do desconto
    int idadeCli, opcao, op, dif, contador = 0, diarias = 0, qtdHoras = 0;
    char cpfCnpjCli[15], placa[11], dateStr [10], timeStr [10], dataDev[10], parceriaCli[6];
    struct data * data;
    time_t t;
    char dataIni[20];
    time(&t);
    Locacao *auxLoc = inicioLoc;
    Locacao *anteriorLoc = inicioLoc;
    Veiculos *anteriorVei;
    Veiculos *auxVei;
    Clientes *pesqCli;
    do{
        system("cls");
        menu();
        opcaoTelas(3);
        if (inicioCli == NULL){
            printf("\n N�o h� clientes cadastrados!\n\n\n");
            printf(" ");
            system("pause");
            break;
        }
        if (inicioVei == NULL){
            printf("\n N�o h� ve�culos cadastrados!\n\n\n");
            printf(" ");
            system("pause");
            break;
        }
        printf("\n TELA - DIGITE O N�MERO DA OPC�O ESCOLHIDA: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 0 :
                //printf ("SAIR");
                break;

            case 1 :
                do{
                    system("cls");
                    menu();
                    linha();
                    printf ("                             CADASTRO DE LOCAC�O\n");
                    linha();
                    printf("\n Entre com o CPF ou CNPJ do cliente(somente n�meros): ");
                    scanf("%s", cpfCnpjCli);
                    pesqCli = inicioCli;
                    dif = -11;
                    contador = 0;
                    while (pesqCli != NULL || dif == 0){
                        dif = strcmp(pesqCli->cpfCnpj,cpfCnpjCli);
                        if (dif == 0){
                            contador ++;
                            break;
                        }else{
                            if (dif != 0){
                                pesqCli = pesqCli->proximoCli;
                            }
                        }
                    }
                    if (contador == 0){
                        printf("\n CPF ou CNPJ n�o encontrado!\n\n\n");
                        printf(" ");
                        system("pause");
                        break;
                    }else{
                        printf("\n Cliente: %s\n", pesqCli->nome);
                        printf("\n Ve�culos dispon�veis:\n");
                        Veiculos *auxLoc = inicioVei;
                        if (auxLoc != NULL){
                            while (auxLoc != NULL){
                                if (dif = strcmp(auxLoc->status,"Locado") != 0){
                                    contador ++;
                                    linha();
                                    printf(" MARCA: %s\n", auxLoc->marca);
                                    printf(" MODELO: %s\n", auxLoc->modelo);
                                    printf(" PLACA: %s\n", auxLoc->placa);
                                    printf(" COMBUSTIVEL: %s\n", auxLoc->combustivel);
                                    printf(" CATEGORIA: %s\n", auxLoc->categoria);
                                    printf(" STATUS: %s\n", auxLoc->status);
                                    auxLoc = auxLoc->proximoVei;
                                }else{
                                    auxLoc = auxLoc->proximoVei;
                                }
                            }
                        }
                        if (contador == 0){
                        printf("\n N�o h� ve�culos dispon�veis\n\n\n");
                        printf(" ");
                        system("pause");
                        break;
                        }else{
                            getchar();
                            printf("\n Digite a placa do ve�culo desejado: ");
                            fgets(placa, sizeof(placa), stdin);
                            placa[strlen(placa)-1]='\0';
                            Veiculos *pesqLoc = inicioVei;
                            //Veiculos *anteriorLoc = inicioVei;
                            dif = -11;
                            while (pesqLoc != NULL || dif == 0){
                                dif = strcmp(pesqLoc->placa,placa);
                                if (dif == 0){
                                    break;
                                }else{
                                    if (dif != 0){
                                        anteriorLoc = pesqLoc;
                                        pesqLoc = pesqLoc->proximoVei;
                                    }
                                }
                            }
                            if (dif != 0){
                                printf("\n Placa informada inv�lida!\n\n\n");
                                printf(" ");
                                system("pause");
                                break;
                            }
                            system("cls");
                            menu();
                            linha();
                            printf ("                             CADASTRO DE LOCAC�O\n");
                            linha();
                            printf(" CONFIRMAR DADOS DA LOCA��O\n");
                            linha();
                            // Exibe o locat�rio
                            printf("\n <<< LOCAT�RIO >>>\n");
                            printf(" NOME: %s | ", pesqCli->nome);
                            printf(" CPF: %s | ", pesqCli->cpfCnpj);
                            printf(" IDADE: %d\n", pesqCli->idade);
                           // printf(" FAIXA ET�RIA: %s", pesqCli->faixaEtaria);
                            printf(" ENDERE�O: %s | ", pesqCli->endereco);
                            printf(" BAIRRO: %s\n", pesqCli->bairro);
                            printf(" CEP: %s | ", pesqCli->cep);
                            printf(" UF: %s\n", pesqCli->uf);
                            // Exibe o ve�culo escolhido
                            printf("\n <<< VE�CULO >>>\n");
                            printf(" MARCA: %s | ", pesqLoc->marca);
                            printf(" MODELO: %s | ", pesqLoc->modelo);
                            printf(" PLACA: %s\n", pesqLoc->placa);
                            printf(" COMBUSTIVEL: %s | ", pesqLoc->combustivel);
                            printf(" CATEGORIA: %s | ", pesqLoc->categoria);
                            printf(" STATUS: %s", pesqLoc->status);
                            printf("\n\n Quantidade de di�rias: ");
                            scanf("%d", &diarias);
                            fflush(stdin);
                            printf("\n Data de Devolu��o (dd/mm/aa): ");
                            fgets(dataDev, sizeof(dataDev), stdin);
                            dataDev[strlen(dataDev)-1]='\0';
                            fflush(stdin);
                            printf("\n\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
                            scanf("%d", &op);
                            if (op == 1){
                                idLocacao ++;
                                Locacao *locacao = (Locacao*) malloc(sizeof(Locacao));
                                locacao->idLocacao = idLocacao;
                                strcpy(locacao->modelo, pesqLoc->modelo);
                                strcpy(locacao->placa, pesqLoc->placa);
                                strcpy(locacao->nome, pesqCli->nome);
                                strcpy(locacao->cpfCnpj, pesqCli->cpfCnpj);
                                locacao->diarias = diarias;
                                data = localtime(&t);
                                strftime(dataIni, 20, "%d/%m/%y", data);
                                strcpy(locacao->dataIni, dataIni);
                                strcpy(locacao->dataFim, dataDev);
                                strcpy(locacao->horaIni, _strtime( timeStr ));
                                strcpy(locacao->horaFim, _strtime( timeStr ));
                                strcpy(locacao->status, "Aberta");
                                strcpy(pesqLoc->status, "Locado");
                                locacao->proximoLoc = NULL;
                                if (inicioLoc == NULL){
                                    inicioLoc = locacao;
                                }else{
                                    locacao->proximoLoc = inicioLoc;
                                    inicioLoc = locacao;
                                }
                                printf("\n\n Loca��o realizada com sucesso!\n\n");
                                printf(" ");
                                system("pause");
                                system("cls");
                                menu();
                                linha();
                                printf("                           COMPROVANTE DE LOCA��O\n");
                                linha();
                                printf("\n CLIENTE:");
                                printf("\n Nome: %s", locacao->nome);
                                printf("\n CPF/CNPJ: %s", locacao->cpfCnpj);
                                printf("\n\n VE�CULO:");
                                printf("\n Modelo: %s", locacao->modelo);
                                printf("\n Placa: %s", locacao->placa);
                                printf("\n Data Loca��o: %s %s", locacao->dataIni, locacao->horaIni);
                                printf("\n Data devolu��o: %s %s", locacao->dataFim, locacao->horaIni);
                                printf("\n Total de di�rias: %d", locacao->diarias);
                                printf("\n Status: %s", locacao->status);
                                printf("\n\n\n ");
                                system("pause");
                                op = 0;
                            }else{linha();
                                printf("\n\n Cadastro cancelado\n\n!");
                            }
                        }
                    }
                }while (op != 0);
                break;

            case 2 :
                system("cls");
                menu();
                linha();
                printf ("                                 LOCA��ES\n");
                Locacao *auxLoc = inicioLoc;
                if (auxLoc != NULL){
                    while ((auxLoc != NULL) && (strcmp(auxLoc->status, "Cancelado"))!= 0){
                        linha();
                        //printf(" ID: %d\n", auxLoc->idLocacao);
                        printf(" Nome: %s | ", auxLoc->nome);
                        printf(" CPF/CNPJ: %s", auxLoc->cpfCnpj);
                        printf("\n\n Ve�culo: %s | ", auxLoc->modelo);
                        printf(" Placa: %s | ", auxLoc->placa);
                        printf(" Total de di�rias: %d", auxLoc->diarias);
                        printf("\n Data Loca��o: %s %s | ", auxLoc->dataIni, auxLoc->horaIni);
                        printf(" Data devolu��o: %s %s", auxLoc->dataFim, auxLoc->horaIni);
                        printf("\n Status: %s\n", auxLoc->status);
                        auxLoc = auxLoc->proximoLoc;
                    }
                    printf("\n\n\n");
                    printf(" ");
                    system("pause");
                }else{
                    linha();
                    printf("\n N�o h� loca��es realizadas!\n\n\n");
                    printf(" ");
                    system("pause");
                }
                //free(auxLoc);
                break;

            case 3 :
                system("cls");
                menu();
                linha();
                printf("                             PESQUISAR LOCA��ES\n");
                linha();
                auxLoc = inicioLoc;
                Locacao *anteriorLoc = inicioLoc;
                anteriorVei = inicioVei;
                auxVei = inicioVei;
                dif = -1;
                if (auxLoc != NULL){
                    printf(" Digite a placa do ve�culo desejado: ");
                    fgets(placa, sizeof(placa), stdin);
                    fflush(stdin);
                    placa[strlen(placa)-1]='\0';
                    while (auxLoc != NULL || dif == 0){
                        op = -1;
                        dif = strcmp(auxLoc->placa,placa);
                        if (dif == 0){
                            op = 1;
                            linha();
                            //printf(" ID: %d\n", auxLoc->idLocacao);
                            printf(" Nome: %s | ", auxLoc->nome);
                            printf(" CPF/CNPJ: %s", auxLoc->cpfCnpj);
                            printf("\n\n Ve�culo: %s | ", auxLoc->modelo);
                            printf(" Placa: %s | ", auxLoc->placa);
                            printf(" Total de di�rias: %d", auxLoc->diarias);
                            printf("\n Data Loca��o: %s %s | ", auxLoc->dataIni, auxLoc->horaIni);
                            printf(" Data devolu��o: %s %s", auxLoc->dataFim, auxLoc->horaIni);
                            printf("\n Status: %s", auxLoc->status);
                            printf("\n\n DIGITE: 0 - SAIR | 1 - CANCELAR LOCA��O | 2 - FINALIZAR LOCA��O: ");
                            scanf("%d", &op);
                            fflush(stdin);
                            switch (op){
                                case 0 :
                                    break;

                                case 1 :
                                    while (strcmp(auxVei->placa, auxLoc->placa) != 0){
                                        auxVei = auxVei->proximoVei;
                                    }
                                    strcpy(auxVei->status, "Livre");
                                    strcpy(auxLoc->status, "Cancelado");
                                    printf("\n Loca��o cancelada!");
                                    break;

                                case 2 :
                                    while (strcmp(auxVei->placa, auxLoc->placa) != 0){
                                        auxVei = auxVei->proximoVei;
                                    }
                                    system("cls");
                                    menu();
                                    linha();
                                    printf("                             PESQUISAR LOCA��ES\n");
                                    linha();
                                    printf(" Nome: %s | ", auxLoc->nome);
                                    printf(" CPF/CNPJ: %s", auxLoc->cpfCnpj);
                                    printf("\n\n Ve�culo: %s | ", auxLoc->modelo);
                                    printf(" Placa: %s | ", auxLoc->placa);
                                    printf(" Total de di�rias: %d", auxLoc->diarias);
                                    printf("\n Data Loca��o: %s %s | ", auxLoc->dataIni, auxLoc->horaIni);
                                    printf(" Data devolu��o: %s %s", auxLoc->dataFim, auxLoc->horaIni);
                                    printf("\n Status: %s", auxLoc->status);
                                    printf("\n\n Houve atraso na devolu��o?");
                                    printf("\n Se sim informar a quantidade de horas, se n�o informe ""0""(Zero): ");
                                    scanf("%d", &qtdHoras);
                                    strcpy(auxVei->status, "Livre");
                                    strcpy(auxLoc->status, "Finalizado");
                                    //printf("\n Teste %s", auxVei->categoria);
                                    if (strcmp(auxVei->categoria, "Economica") == 0){
                                        if (strcmp(parceriaCli, "Sim") == 0){
                                            total = ((diarias * vlrEcon) + ((vlrEcon / 24)* qtdHoras)) / 1.05;
                                            printf("\n VALOR TOTAL: %0.2f", total);
                                        }else{
                                            if (idadeCli >= 60){
                                                total = ((diarias * vlrEcon) + ((vlrEcon / 24)* qtdHoras)) / 1.10;
                                                printf("\n VALOR TOTAL: %0.2f", total);
                                            }else{
                                                total = ((diarias * vlrEcon) + ((vlrEcon / 24)* qtdHoras));
                                                printf("\n VALOR TOTAL: %0.2f", total);
                                            }
                                        }

                                    }
                                    if (strcmp(auxVei->categoria, "Economica") == 0){
                                        if (strcmp(parceriaCli, "Sim") == 0){
                                            total = ((diarias * vlrInter) + ((vlrInter / 24)* qtdHoras)) / 1.05;
                                            printf("\n VALOR TOTAL: %0.2f", total);
                                        }else{
                                            if (idadeCli >= 60){
                                                total = ((diarias * vlrInter) + ((vlrInter / 24)* qtdHoras)) / 1.10;
                                                printf("\n VALOR TOTAL: %0.2f", total);
                                            }else{
                                                total = ((diarias * vlrInter) + ((vlrInter / 24)* qtdHoras));
                                                printf("\n VALOR TOTAL: %0.2f", total);
                                            }
                                        }

                                    }

                                    if (strcmp(auxVei->categoria, "Economica") == 0){
                                        if (strcmp(parceriaCli, "Sim") == 0){
                                            total = ((diarias * vlrLuxo) + ((vlrLuxo / 24)* qtdHoras)) / 1.05;
                                            printf("\n VALOR TOTAL: %0.2f", total);
                                        }else{
                                            if (idadeCli >= 60){
                                                total = ((diarias * vlrLuxo) + ((vlrLuxo / 24)* qtdHoras)) / 1.10;
                                                printf("\n VALOR TOTAL: %0.2f", total);
                                            }else{
                                                total = ((diarias * vlrLuxo) + ((vlrLuxo / 24)* qtdHoras));
                                                printf("\n VALOR TOTAL: %0.2f", total);
                                            }
                                        }

                                    }

                                    //printf("\n TOTAL � PAGAR: %0.2f", );
                                    printf("\n Loca��o finalizada!");
                                    //printf("\n\n\n ");
                                    //system("pause");
                                    break;

                            }
                            printf("\n\n\n ");
                            system("pause");
                            break;
                        }else{
                            if (dif != 0){
                                anteriorLoc = auxLoc;
                                auxLoc= auxLoc->proximoLoc;
                            }
                        }
                    }
                    if (op == -1){
                        printf("\n Foi digitada uma placa inv�lida!\n\n\n");
                        printf(" ");
                        system("pause");
                        break;
                    }

                }else{
                    linha();
                    printf("\n N�o h� loca��es realizadas!\n\n\n");
                    printf(" ");
                    system("pause");
                }
                //free(auxLoc);
                break;
            case 4 :
                system("cls");
                menu();
                linha();
                printf("                                   PRE�OS\n");
                linha();
                printf(" Cadastrar pre�os: (R$/Dia)\n\n");
                printf(" Categoria - Econ�mico: ");
                scanf("%f", &vlrEcon);
                fflush(stdin);
                printf("\n Categoria - Intermedi�rio: ");
                scanf("%f", &vlrInter);
                fflush(stdin);
                printf("\n Categoria - Luxo: ");
                scanf("%f", &vlrLuxo);
                fflush(stdin);
                printf("\n Valores: %0.2f %0.2f %0.2f", vlrEcon, vlrInter, vlrLuxo);

                printf("\n\n\n ");
                system("pause");
                break;

            default :
                printf("\n Op��o inv�lida!\n\n\n");
                fflush(stdin);
                printf(" ");
                system("pause");
                break;

        }
    }while( opcao != 0);
    free(auxVei);
    free(pesqCli);
    free(auxLoc);
    free(anteriorLoc);
    free(anteriorVei);
    system("cls");
}
//EFETUA O CADASTRO DE USUARIOS
void cadUsuario (){
    FILE *arquivo; //Defino um ponteiro de arquivo
    int opcao, op, dif, gravar;
    char nome[50], user[25], senha[25]; //linhaUser[100],
    do{
        system("cls");//Limpa a tela
        menu(); //Executa a fun��o "Menu"
        opcaoTelas(4); //Executa a fun��o tela
        printf("\n TELA - DIGITE O N�MERO DA OP��O ESCOLHIDA: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 0 :
                break;

            case 1 :
                    do{
                        system("cls");
                        menu();
                        linha(); // Exibe a fun��o linha que cria uma linha de 80 posi��es
                        printf ("                             CADASTRO DE USU�RIO \n");
                        linha();
                        printf("\n Nome completo: ");
                        fgets(nome, sizeof(nome), stdin);
                        nome[strlen(nome)-1]='\0';//remove a quebra de linha da string
                        fflush(stdin); //Limpa o buffer do teclado
                        printf("\n Usu�rio: ");
                        fgets(user, sizeof(user), stdin);
                        user[strlen(user)-1]='\0';
                        fflush(stdin);
                        printf("\n Senha: ");
                        fgets(senha, sizeof(senha), stdin);
                        senha[strlen(senha)-1]='\0';
                        fflush(stdin);
                        if ((strlen(nome) ==  0)||(strlen(user) == 0)||(strlen(senha) == 0)){ //Verifica se todos os campos est�o preenchidos
                            printf("\n Todos o campos s�o de preenchimento Obrigat�rio!\n\n");
                            system("pause"); // Gera uma pausa at� que alguma tecla seja pressionada
                        }
                    }while ((strlen(nome) ==  0)||(strlen(user) == 0)||(strlen(senha) == 0));//Realiza um loop at� que todos os campos estejam preenchidos
                    dif = -1;
                    Usuario *check = inicioUser; //Cria uma struct auxiliar de nome check
                    while (check != NULL){ //Executa o loop at� enquanto check for diferente de NULL
                        dif = strcmp(check->nomeUsuario, user); //compara se o usu�rio ja existe no cadastro
                        if (dif == 0){
                            printf("\n Usu�rio j� cadastrado!\n");
                            printf("\n\n Cadastro cancelado!\n\n");
                            break;
                        }else{
                            check = check->proximoUser; //Enquanto check for diferente de NULL, vai para o pr�ximo registro
                        }
                    }
                    free(check);//Libera a struct check da mem�ria

                    if (dif != 0){
                        printf("\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
                        scanf("%d", &op);
                        if (op == 1){
                            Usuario *usuario = (Usuario*) malloc(sizeof(Usuario)); //Aloca um espa�o de mem�ria para struct usu�rio
                            strcpy(usuario->nomeCompleto, nome); // copia o conte�do da vari�vel para a struct
                            strcpy(usuario->nomeUsuario, user);
                            strcpy(usuario->senha, senha);
                            usuario->proximoUser = NULL;
                            if (inicioUser == NULL){ //Se n�o houver nenhum cadastro
                                inicioUser = usuario;// Cadastra o primeiro registro
                            }else{ //Se n�o
                                usuario->proximoUser = inicioUser; //Aponta para o pr�ximo registro
                                inicioUser = usuario; //Define a struct usuario no inicio
                            }
                            gravar = 1; //vari�vel de apoio
                            printf("\n\n Usu�rio cadastrado com sucesso!\n\n");
                        }else{
                            printf("\n\n Cadastro cancelado\n\n!");
                        }
                    }
                    system("pause");
                break;

            case 2 ://Exibe usu�rios cadastrados
                    system("cls");
                    menu();
                    linha();
                    printf ("                            USU�RIOS CADASTRADOS \n");
                    Usuario *auxUser = inicioUser;
                    if (auxUser != NULL){
                        while (auxUser != NULL){
                            linha();
                            printf(" Nome: %s\n", auxUser->nomeCompleto);
                            printf(" Usu�rio: %s\n", auxUser->nomeUsuario);
                            printf(" Senha: %s\n", auxUser->senha);
                            auxUser = auxUser->proximoUser;
                        }
                        printf("\n\n");
                        system("pause");
                    }else{
                        printf("\n N�o h� usu�rios cadastrados!\n");
                        printf("\n\n");
                        system("pause");
                    }
                    free(auxUser);
                break;

            case 3:
                    do{
                        gravar = 0;
                        system("cls");
                        menu();
                        linha();
                        printf ("                            PESQUISAR USU�RIOS \n");
                        linha();
                        Usuario *auxUser = inicioUser;
                        Usuario *anteriorUser = inicioUser;
                        dif = -1;
                        if (auxUser != NULL){
                            printf("\n Digite o usu�rio para pesquisa: ");
                            fgets(user, sizeof(user), stdin);
                            fflush(stdin);
                            user[strlen(user)-1]='\0';
                            while (auxUser != NULL || dif == 0){
                                dif = strcmp(auxUser->nomeUsuario,user);
                                if (dif == 0){
                                    printf("------------------------------------------\n");
                                    printf(" Nome: %s\n", auxUser->nomeCompleto);
                                    printf(" Usu�rio: %s\n", auxUser->nomeUsuario);
                                    printf(" Senha: %s", auxUser->senha);
                                    break;
                                }else{
                                    if (dif != 0){
                                        anteriorUser = auxUser;
                                        auxUser= auxUser->proximoUser;
                                    }
                                }
                            }
                       }else{
                            printf("\n N�o h� usu�rios cadastrados!\n\n\n");
                            system("pause");
                            break;
                        }
                        if (dif == 0){
                            do{
                                printf("\n DIGITE: 0 - SAIR | 1 - ALTERAR | 2 - EXCLUIR: ");
                                scanf("%d", &op);
                                getchar();
                                switch(op){
                                    case 0:
                                        break;

                                    case 1://Alterar cadastro
                                        do{
                                            system("cls");
                                            menu();
                                            linha();
                                            printf ("                            PESQUISAR USU�RIOS \n");
                                            linha();
                                            printf("\n Nome completo: ");
                                            fgets(nome, sizeof(nome), stdin);
                                            nome[strlen(nome)-1] = '\0';
                                            fflush(stdin);
                                            printf("\n Usu�rio: ");
                                            fgets(user, sizeof(user), stdin);
                                            user[strlen(user)-1] = '\0';
                                            fflush(stdin);
                                            printf("\n Senha: ");
                                            fgets(senha, sizeof(senha), stdin);
                                            senha[strlen(senha)-1] = '\0';
                                            fflush(stdin);
                                            if ((strlen(nome) ==  0)||(strlen(user) == 0)||(strlen(senha) == 0)){
                                                printf("\n Todos o campos s�o de preenchimento Obrigat�rio!\n\n");
                                                system("pause");
                                            }
                                        }while ((strlen(nome) ==  0)||(strlen(user) == 0)||(strlen(senha) == 0));
                                        strcpy(auxUser->nomeCompleto, nome);
                                        strcpy(auxUser->nomeUsuario, user);
                                        strcpy(auxUser->senha, senha);
                                        op = 0;
                                        printf("\n Registro alterado!\n\n");
                                        gravar = 1;
                                        system("pause");
                                        break;

                                    case 2://Excluir cadastro
                                        if (auxUser == anteriorUser){
                                            if (auxUser->proximoUser == NULL){
                                                inicioUser = NULL;
                                            }else{
                                                inicioUser = auxUser->proximoUser;
                                            }

                                        }else{
                                            if (auxUser->proximoUser == NULL){
                                                anteriorUser->proximoUser = NULL;
                                                auxUser = NULL;
                                            }else{
                                                anteriorUser->proximoUser = auxUser->proximoUser;
                                                auxUser = NULL;
                                            }
                                        }
                                        op = 0;
                                        printf("\n Registro exclu�do!\n\n");
                                        gravar = 1;
                                        system("pause");
                                        break;
                                    default :
                                        printf("\n Op��o inv�lida!\n\n");
                                        fflush(stdin);
                                        system("pause");
                                        break;
                                    }
                                }while (op != 0);
                            }else{
                                printf("\n Nome de usu�rio inv�lido!\n");
                                system("pause");
                                break;
                            }
                    }while (op != 0);
                break;
            default :
                    printf("\n Op��o inv�lida!\n\n");
                    fflush(stdin);
                    system("pause");
                    break;
        }
        if (gravar == 1){//Se a variavel gravar for igual a 1, grava os dados da struct no arquivo
            Usuario *usuario = inicioUser;//Move o ponteiro para o primeiro registro da struct
            arquivo = fopen("Usuarios.txt", "w");//Abre o arquivo de usuarios em modo de escrita "W)
            if(arquivo == NULL){//Verifica se o arquivo foi aberto com �xito.
                printf("Erro, n�o foi poss�vel abrir o arquivo\n");
                system("pause");
            }else{
                while (usuario != NULL){ //Enquanto houver registros na struct, grava os mesmo no arquivo
                fprintf(arquivo, "%s|%s|%s\n", usuario->nomeCompleto, usuario->nomeUsuario, usuario->senha);
                usuario = usuario->proximoUser;//Move o ponteiro da struct pelos registros
                }
            }
            fclose(arquivo);//fecha o arquivo
            gravar = 0;
        }
    }while(opcao != 0);
    system("cls");
}    //RECEBER DADOS DE CADASTRO DE USUARIO

void relatorios(){
    int op, opcao;
    do{
        system("cls");
        menu();
        linha(); // Exibe a fun��o linha que cria uma linha de 80 posi��es
        printf (" RELAT�RIOS\n");
        linha();
        printf(" 0 SAIR  | 1 VE�CULOS  | 2 CLIENTES  | 3 LOCAC�ES: ");
        scanf("%d", &op);
        switch (op){
            case 0 :
                break;
            case 1 :
                system("cls");
                menu();
                linha();
                printf ("                                 VE�CULOS\n");
                linha();
                Veiculos *auxVei = inicioVei;
                if (auxVei == NULL){
                        printf("\n N�o h� Ve�culos Cadastrados!");
                }
                while (auxVei != NULL){
                    printf(" MARCA: %s", auxVei->marca);
                    printf("\n MODELO: %s", auxVei->modelo);
                    printf("\n PLACA: %s", auxVei->placa);
                    printf("\n COMBUSTIVEL: %s", auxVei->combustivel);
                    printf("\n STATUS: %s", auxVei->status);
                    printf("\n CATEGORIA: %s", auxVei->categoria);
                    printf("\n");
                    linha();
                    auxVei = auxVei->proximoVei;
                }
                op = -1;
                printf("\n\n\n ");
                system("pause");
                break;

            case 2 :
                system("cls");
                menu();
                linha();
                printf ("                                 CLIENTES\n");
                linha();
                Clientes *auX = inicioCli;
                if (auxVei == NULL){
                    printf("\n N�o h� Clientes Cadastrados!");
                }
                while (auX != NULL){
                    printf(" NOME: %s", auX->nome);
                    printf("\n CPF/CNPJ: %s", auX->cpfCnpj);
                    printf("\n IDADE: %d", auX->idade);
                    printf("\n PARCEIRO: %s", auX->parceiro);
                    printf("\n TELEFONE: %s", auX->telefone);
                    printf("\n ENDERE�O: %s", auX->endereco);
                    printf("\n BAIRRO: %s", auX->bairro);
                    printf("\n CIDADE: %s", auX->cidade);
                    printf("\n CEP: %s", auX->cep);
                    printf("\n UF: %s", auX->uf);
                    printf("\n");
                    linha();
                    auX = auX->proximoCli;
                }
                op = -1;
                printf("\n\n\n ");
                system("pause");
                break;

            case 3 :
                system("cls");
                menu();
                linha();
                printf (" LOCA��ES\n");
                linha();
                Locacao *aux = inicioLoc;
                if (auxVei == NULL){
                    printf("\n N�o h� Loca��es!");
                }
                while (aux != NULL){
                    printf(" MODELO: %s", aux->modelo);
                    printf("\n PLACA: %s", aux->placa);
                    printf("\n NOME: %s", aux->nome);
                    printf("\n CPF/CNPJ: %s", aux->cpfCnpj);
                    printf("\n RETIRADA: %s %s", aux->dataIni, aux->horaIni);
                    printf("\n DEVOLU��O: %s %s", aux->dataFim, aux->horaFim);
                    printf("\n STATUS: %s", aux->status);
                    printf("\n");
                    linha();
                    aux = aux->proximoLoc;
                }
                op = -1;
                printf("\n\n\n ");
                system("pause");
                break;

            default :
                printf("\n Op��o Inv�lida!");
                fflush(stdin);
                break;
        }
        system("cls");
    }while (op != 0);
}
int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    importaUsuarios(); // Fun��o Importar Usu�rios
    importaVeiculos(); // Fun��o Importar Usu�rios
    importaClientes(); // Fun��o importar Clientes
    do{
        menu();
        subMenu();
        printf("\n MENU - DIGITE O N�MERO DA TELA DE ACESSO: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 0 :
                printf ("\n SISTEMA FINALIZADO!\n");
                break;
            case 1 :
                opcaoTelas(opcao);
                cadVeiculos(opcao);
                break;
            case 2 :
                opcaoTelas(opcao);
                cadClientes(opcao);
                break;
            case 3 :
                system("cls");
                cadLocacao(opcao);
                break;
            case 4 :
                system("cls");
                cadUsuario(opcao);
                break;
            case 5 :
                system("cls");
                relatorios(opcao);
                break;

            default :
                printf("\n Op��o inv�lida\n\n");
                fflush(stdin);
                printf(" ");
                system("pause");
                system("cls");
                break;
        }
    }while(opcao != 0);
    return 0;
}
