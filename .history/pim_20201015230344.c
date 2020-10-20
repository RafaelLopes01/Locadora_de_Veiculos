#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
//CODIGOS GERAL
// Struct cadastro de usuários
typedef struct Usuario{
char nomeCompleto[50];
char nomeUsuario[25];
char senha[25];
struct usuario *proximoUser;
}Usuario;
Usuario *inicioUser = NULL;
//Struct Cadastro de clientes
typedef struct Clientes{
char nome[50], cpfCnpj [15], parceiro[5],telefone[12], endereco[50],
bairro[25], cidade[25], cep[10], uf[4];
int idade;
struct Clientes *proximoCli;
}Clientes;
Clientes *inicioCli = NULL;
//Struct Cadastro de Veículos
typedef struct Veiculos{
char marca[101], modelo[101], placa[10], combustivel[10], status[31],
categoria[31];
struct Veiculos *inicioVei;
struct Veiculos *proximoVei;
61
}Veiculos;
Veiculos *inicioVei = NULL;
//Struct Cadastro de locações
typedef struct Locacao{
int idLocacao, diarias;
float valorLoc;
char modelo[101], placa[10], nome[101], cpfCnpj[15], dataIni[10],
horaIni[10], dataFim[10], horaFim[10], status[15];
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
dma dataLocacao,dataRetorno;
//TABELA DE PREÇOS
float vlrEcon, vlrInter, vlrLuxo;// Preço Econômico, Intermediário e Luxo
//LINHA DE 80 POSIÇÃO COM *.
void linhaEstrela (){
int x;
for(x = 0; x < 80;x++){
printf("*");
}
printf("\n");
}
62
//LINHA DE 80 POSIÇÃO COM -.
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
printf(" ALUGUE FÁCIL \n");
linhaEstrela();
}
void subMenu (){
printf(" 0 SAIR | 1 VEÍCULOS | 2 CLIENTES | 3 LOCACÕES | 4
USUÁRIOS | 5 RELATÓRIOS\n");
linhaEstrela();
}
//LAYOUT DE TELA
void tela (char tela[101]){
linha();
printf("%s\n", tela);
linha();
printf(" 0 - SAIR\n 1 - NOVO\n 2 - EXIBIR REGISTROS\n 3 -
PESQUISAR\n");
linha();
}
void telaLocacoes (char telaLocacoes[101]){
63
linha();
printf("%s\n", telaLocacoes);
linha();
printf(" 0 - SAIR\n 1 - NOVO\n 2 - EXIBIR REGISTROS\n 3 -
PESQUISAR\n 4 - PREÇOS\n");
linha();
}
//LAYOUT DE OPÇÃO DE TELAS
void opcaoTelas (int opcao){
switch(opcao){
case 1 :
tela(" VEÍCULOS");
break;
case 2 :
tela(" CLIENTES");
break;
case 3 :
telaLocacoes(" LOCACÕES");
break;
case 4 :
tela(" USUÁRIOS");
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
fprintf(stderr, "\n Erro: Não foi possível carregar os usuários!\n\n");
printf(" ");
64
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
65
}
void importaVeiculos(){
char linha[121], marca[25], modelo[25], placa[10], combustivel[10],
status[25], categoria[25];
FILE *arq;
arq = fopen("Veiculos.txt","r");
if (arq == NULL){
menu();
subMenu();
fprintf(stderr, "\n Erro: Não foi possível carregar os veículos!\n\n");
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
66
strcat(combustivel, Ponteiro);
Ponteiro = strtok(NULL, "|");
strcat(categoria, Ponteiro);
Ponteiro = strtok(NULL, "|");
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
char linha[200], nomeCli[50],telefoneCli[12], cpfCnpjCli[15], parceiro[5],
enderecoCli[50], bairroCli[25], cidadeCli[25], cepCli[10], ufCli[4];
FILE *arq;
arq = fopen("Clientes.txt","r");
if (arq == NULL){
menu();
subMenu();
fprintf(stderr, "\n Erro: Não foi possível carregar os clientes!\n\n");
67
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
Ponteiro = strtok(NULL, "|");
idadeCli = atoi(Ponteiro);
Ponteiro = strtok(NULL, "|");
68
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
69
int opcao, op, dif, gravar;
char marca[25], modelo[25], placa[10], combustivel[10], status[25],
categoria[25];
Veiculos *inicioVei = NULL;
do{
Veiculos *auxVei = inicioVei;
gravar = 0;
system("cls");
menu();
opcaoTelas(1);
printf("\n TELA - DIGITE O NÚMERO DA OPCÃO ESCOLHIDA:
");
scanf("%d", &opcao);
getchar();
switch(opcao){
case 0 :
break;
case 1 :
op = 0;
system("cls");
menu();
linha();
printf (" CADASTRO DE VEÍCULO\n");
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
70
fgets(placa,sizeof(placa) , stdin);
placa[strlen(placa)-1]='\0';
fflush(stdin);
Veiculos *check = inicioVei;
while (check != NULL){
dif = strcmp(check->placa, placa);
if (dif == 0){
printf("\n Veículo já cadastrado!\n\n");
free(check);
op = 1;
break;
}else{
check = check->proximoVei;
}
}
if (op != 1){
do{
printf("\n COMBUSTÍVEL: 1 - Gasolina | 2 - Etanol | 3 -
Flex: ");
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
71
default:
printf("\n Opção inválida!");//idade
break;
}
}while ((op != 1) && (op != 2) && (op != 3));
do{
printf("\n CATEGORIA: 1 - Economica 2 - Intermediaria
3 - Luxo: ");
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
printf("\n Opção inválida!");//idade
}
}while ((op != 1) && (op != 2) && (op != 3));
printf("\n\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
scanf("%d", &op);
if (dif != 0 && op == 1){
Veiculos *veiculo = (Veiculos*) malloc(sizeof(Veiculos));
strcpy(veiculo->marca, marca);
strcpy(veiculo->modelo, modelo);
strcpy(veiculo->placa, placa);
72
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
printf("\n\n Veículo cadastrado com sucesso!\n\n");
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
printf (" VEÍCULOS CADASTRADOS \n");
auxVei = inicioVei;
if (auxVei != NULL){
while (auxVei != NULL){
linha();
printf(" MARCA: %s\n", auxVei->marca);
printf(" MODELO: %s\n", auxVei->modelo);
printf(" PLACA: %s\n", auxVei->placa);
printf(" COMBUSTIVEL: %s\n", auxVei->combustivel);
printf(" CATEGORIA: %s\n", auxVei->categoria);
73
printf(" STATUS: %s\n", auxVei->status);
auxVei = auxVei->proximoVei;
}
printf("\n\n\n ");
system("pause");
}else{
printf("\n Não há veículos cadastrados!\n");
printf("\n\n");
printf(" ");
system("pause");
}
free(auxVei);
break;
case 3 :
do{
system("cls");
menu();
linha();
printf (" PESQUISAR VEÍCULO \n");
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
74
printf(" COMBUSTIVEL: %s\n", pesq-
>combustivel);
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
printf("\n Não há veículos cadastrados!\n\n\n");
printf(" ");
system("pause");
break;
}
if (dif == 0){
do{
printf("\n DIGITE: 0 - SAIR | 1 - ALTERAR | 2 -
EXCLUIR: ");
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
75
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
printf("\n COMBUSTÍVEL: 1 - Gasolina | 2 -
Etanol | 3 - Flex: ");
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
printf("\n Opção inválida!");//idade
break;
}
}while ((op != 1) && (op != 2) && (op != 3));
do{
76
printf("\n CATEGORIA: 1 - Economica 2 -
Intermediaria 3 - Luxo: ");
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
printf("\n Opção inválida!");//idade
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
77
inicioVei = pesq->proximoVei; //pesq =
NULL;
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
printf("\n Registro excluído!\n\n");
printf(" ");
system("pause");
break;
default :
printf("\n Opção inválida!");
fflush(stdin);
break;
}
}while (op != 0);
}else{
printf("\n Placa inválida!\n\n\n");
printf(" ");
system("pause");
break;
}
}while (op != 0);
break;
78
default :
printf("\n Opção inválida!");
fflush(stdin);
printf(" ");
system("pause");
break;
}
if (gravar == 1){
Veiculos *veiculo = inicioVei;
arq = fopen("Veiculos.txt", "w");
if(arq == NULL){
printf("Erro, não foi possível abrir o arquivo\n");
system("pause");
}else{
while (veiculo != NULL){
fprintf(arq, "%s|%s|%s|%s|%s|%s\n", veiculo->marca,
veiculo->modelo, veiculo->placa, veiculo->combustivel, veiculo->categoria,
veiculo->status);
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
char nomeCli[50], cpfCnpjCli[15], parceiro[5],telefoneCli[12],
enderecoCli[50], bairroCli[25], cidadeCli[25], cepCli[10], ufCli[4];
FILE *arq;
do{
79
system("cls");
menu();
opcaoTelas(2);
printf("\n TELA - DIGITE O NÚMERO DA OPCÃO ESCOLHIDA: ");
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
printf (" CADASTRO DE CLIENTE\n");
linha();
do{
printf("\n Parceiro? 0 - Não | 1 - Sim: ");
scanf("%d", &op);
fflush(stdin);
switch (op){
case 0:
strcpy(parceiro, "Nao");
printf("\n Opção escolhida: Não\n");
op = 0;
break;
case 1:
strcpy(parceiro, "Sim");
printf("\n Opção escolhida: Sim\n");
op = 0;
break;
80
default :
printf("\n Opção inválida!\n\n\n");
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
printf("\n Cliente já cadastrado!\n\n\n");
check = NULL;
break;
}else{
check = check->proximoCli;
}
}
if (dif == 0){
break;
81
}
free(check);
printf("\n Telefone(somente números): ");
fgets(telefoneCli, sizeof(telefoneCli), stdin);
telefoneCli[strlen(telefoneCli)-1]='\0';
fflush(stdin);
printf("\n Idade do motorista: ");
scanf("%d", &idadeCli);
fflush(stdin);
printf("\n Endereço: ");
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
if ((strlen(nomeCli) == 0)||(strlen(cpfCnpjCli) ==
0)||(strlen(telefoneCli) == 0)||(strlen(enderecoCli) == 0)||(strlen(bairroCli) ==
0)||(strlen(cidadeCli) == 0)||(strlen(cepCli) == 0)||(strlen(ufCli) == 0)){
82
printf("\n Todos o campos são de preenchimento
Obrigatório!\n\n\n");
printf(" ");
op = -1;
break;
}else{
printf("\n\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
scanf("%d", &op);
if (dif != 0 && op == 1){
Clientes *cliente = (Clientes*)
malloc(sizeof(Clientes));
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
83
}while ((op == -1));
getchar();
printf(" ");
system("pause");
break;
case 2 :
system("cls");
menu();
linha();
printf (" CLIENTES CADASTRADOS \n");
Clientes *aux = inicioCli;
if (aux != NULL){
while (aux != NULL){
linha();
printf(" NOME: %s\n", aux->nome);
printf(" CPF/CNPJ: %s\n", aux->cpfCnpj);
printf(" PARCEIRO: %s\n", aux->parceiro);
printf(" TELEFONE: %s\n", aux->telefone);
printf(" IDADE DO MORTORISTA: %d\n", aux->idade);
printf(" ENDEREÇO: %s\n", aux->endereco);
printf(" BAIRRO: %s\n", aux->bairro);
printf(" CIDADE: %s\n", aux->cidade);
printf(" CEP: %s\n", aux->cep);
printf(" UF: %s\n", aux->uf);
aux = aux->proximoCli;
}
printf("\n\n");
system("pause");
}else{
printf("\n Não há clientes cadastrados!\n");
printf("\n\n");
system("pause");
}
free(aux);
84
break;
case 3 :
do{
system("cls");
menu();
linha();
printf (" PESQUISAR CLIENTES \n");
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
printf(" IDADE DO MOTORISTA: %d\n", pesq-
>idade);
printf(" ENDEREÇO: %s\n", pesq->endereco);
printf(" BAIRRO: %s\n", pesq->bairro);
printf(" CIDADE: %s\n", pesq->cidade);
printf(" CEP: %s\n", pesq->cep);
printf(" UF: %s\n", pesq->uf);
break;
}else{
if (dif != 0){
85
anterior = pesq;
pesq = pesq->proximoCli;
}
}
}
}else{
printf("\n Não há clientes cadastrados!\n\n\n");
system("pause");
break;
}
if (dif == 0){
do{
printf("\n DIGITE: 0 - SAIR | 1 - ALTERAR | 2 -
EXCLUIR: ");
scanf("%d", &op);
getchar();
switch(op){
case 0:
break;
case 1://Alterar cadastro
do{
printf("\n Parceiro? 0 - Não | 1 - Sim: ");
scanf("%d", &op);
fflush(stdin);
switch (op){
case 0:
strcat(parceiro, "Nao");
op = 0;
printf("\n Opção escolhida: Não");
break;
case 1:
strcat(parceiro, "Sim");
printf("\n Opção escolhida: Sim");
86
op = 0;
break;
default :
printf("\n Opção inválida!\n\n");
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
printf("\n Telefone(somente números): ");
fgets(telefoneCli, sizeof(telefoneCli), stdin);
fflush(stdin);
printf("\n Idade do motorista: ");
scanf("%d", &idadeCli);
fflush(stdin);
printf("\n Endereço: ");
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
87
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
printf("\n Registro excluído!\n\n");
printf(" ");
system("pause");
88
break;
default :
printf("\n Opção inválida!\n\n");
fflush(stdin);
printf(" ");
system("pause");
break;
}
}while (op != 0);
}else{
printf("\n CPF inválido!\n");
printf(" ");
system("pause");
break;
}
}while (op != 0);
break;
default :
printf("\n Opção inválida!");//idade
fflush(stdin);
printf(" ");
system("pause");
break;
}
if (gravar == 1){
Clientes *cliente = inicioCli;
arq = fopen("Clientes.txt", "w");
if(arq == NULL){
printf("Erro, não foi possível abrir o arquivo clientes\n");
printf(" ");
system("pause");
}else{
while (cliente != NULL){
89
fprintf(arq, "%s|%s|%s|%s|%d|%s|%s|%s|%s|%s\n", cliente-
>parceiro ,cliente->telefone , cliente->nome, cliente->cpfCnpj, cliente->idade,
cliente->endereco, cliente->bairro, cliente->cidade, cliente->cep, cliente->uf);
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
float total; // Calcular total da locação
float desconto;//Fator do desconto
int idadeCli, opcao, op, dif, contador = 0, diarias = 0, qtdHoras = 0;
char cpfCnpjCli[15], placa[11], dateStr [10], timeStr [10], dataDev[10],
parceriaCli[6];
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
90
printf("\n Não há clientes cadastrados!\n\n\n");
printf(" ");
system("pause");
break;
}
if (inicioVei == NULL){
printf("\n Não há veículos cadastrados!\n\n\n");
printf(" ");
system("pause");
break;
}
printf("\n TELA - DIGITE O NÚMERO DA OPCÃO ESCOLHIDA: ");
scanf("%d", &opcao);
getchar();
switch(opcao){
case 0 :
break;
case 1 :
do{
system("cls");
menu();
linha();
printf (" CADASTRO DE LOCACÃO\n");
linha();
printf("\n Entre com o CPF ou CNPJ do cliente(somente
números): ");
scanf("%s", cpfCnpjCli);
pesqCli = inicioCli;
dif = -11;
contador = 0;
while (pesqCli != NULL || dif == 0){
dif = strcmp(pesqCli->cpfCnpj,cpfCnpjCli);
if (dif == 0){
91
contador ++;
break;
}else{
if (dif != 0){
pesqCli = pesqCli->proximoCli;
}
}
}
if (contador == 0){
printf("\n CPF ou CNPJ não encontrado!\n\n\n");
printf(" ");
system("pause");
break;
}else{
printf("\n Cliente: %s\n", pesqCli->nome);
printf("\n Veículos disponíveis:\n");
Veiculos *auxLoc = inicioVei;
if (auxLoc != NULL){
while (auxLoc != NULL){
if (dif = strcmp(auxLoc->status,"Locado") != 0){
contador ++;
linha();
printf(" MARCA: %s\n", auxLoc->marca);
printf(" MODELO: %s\n", auxLoc->modelo);
printf(" PLACA: %s\n", auxLoc->placa);
printf(" COMBUSTIVEL: %s\n", auxLoc-
>combustivel);
printf(" CATEGORIA: %s\n", auxLoc->categoria);
printf(" STATUS: %s\n", auxLoc->status);
auxLoc = auxLoc->proximoVei;
}else{
auxLoc = auxLoc->proximoVei;
}
}
92
}
if (contador == 0){
printf("\n Não há veículos disponíveis\n\n\n");
printf(" ");
system("pause");
break;
}else{
getchar();
printf("\n Digite a placa do veículo desejado: ");
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
printf("\n Placa informada inválida!\n\n\n");
printf(" ");
system("pause");
break;
}
system("cls");
menu();
93
linha();
printf (" CADASTRO DE LOCACÃO\n");
linha();
printf(" CONFIRMAR DADOS DA LOCAÇÃO\n");
linha();
// Exibe o locatário
printf("\n <<< LOCATÁRIO >>>\n");
printf(" NOME: %s | ", pesqCli->nome);
printf(" CPF: %s | ", pesqCli->cpfCnpj);
printf(" IDADE: %d\n", pesqCli->idade);
// printf(" FAIXA ETÁRIA: %s", pesqCli->faixaEtaria);
printf(" ENDEREÇO: %s | ", pesqCli->endereco);
printf(" BAIRRO: %s\n", pesqCli->bairro);
printf(" CEP: %s | ", pesqCli->cep);
printf(" UF: %s\n", pesqCli->uf);
// Exibe o veículo escolhido
printf("\n <<< VEÍCULO >>>\n");
printf(" MARCA: %s | ", pesqLoc->marca);
printf(" MODELO: %s | ", pesqLoc->modelo);
printf(" PLACA: %s\n", pesqLoc->placa);
printf(" COMBUSTIVEL: %s | ", pesqLoc->combustivel);
printf(" CATEGORIA: %s | ", pesqLoc->categoria);
printf(" STATUS: %s", pesqLoc->status);
printf("\n\n Quantidade de diárias: ");
scanf("%d", &diarias);
fflush(stdin);
printf("\n Data de Devolução (dd/mm/aa): ");
fgets(dataDev, sizeof(dataDev), stdin);
dataDev[strlen(dataDev)-1]='\0';
fflush(stdin);
printf("\n\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
94
scanf("%d", &op);
if (op == 1){
idLocacao ++;
Locacao *locacao = (Locacao*)
malloc(sizeof(Locacao));
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
printf("\n\n Locação realizada com sucesso!\n\n");
printf(" ");
system("pause");
system("cls");
menu();
linha();
printf(" COMPROVANTE DE
LOCAÇÃO\n");
95
linha();
printf("\n CLIENTE:");
printf("\n Nome: %s", locacao->nome);
printf("\n CPF/CNPJ: %s", locacao->cpfCnpj);
printf("\n\n VEÍCULO:");
printf("\n Modelo: %s", locacao->modelo);
printf("\n Placa: %s", locacao->placa);
printf("\n Data Locação: %s %s", locacao->dataIni,
locacao->horaIni);
printf("\n Data devolução: %s %s", locacao->dataFim,
locacao->horaIni);
printf("\n Total de diárias: %d", locacao->diarias);
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
printf (" LOCAÇÕES\n");
Locacao *auxLoc = inicioLoc;
if (auxLoc != NULL){
while ((auxLoc != NULL) && (strcmp(auxLoc->status,
"Cancelado"))!= 0){
linha();
96
printf(" Nome: %s | ", auxLoc->nome);
printf(" CPF/CNPJ: %s", auxLoc->cpfCnpj);
printf("\n\n Veículo: %s | ", auxLoc->modelo);
printf(" Placa: %s | ", auxLoc->placa);
printf(" Total de diárias: %d", auxLoc->diarias);
printf("\n Data Locação: %s %s | ", auxLoc->dataIni,
auxLoc->horaIni);
printf(" Data devolução: %s %s", auxLoc->dataFim,
auxLoc->horaIni);
printf("\n Status: %s\n", auxLoc->status);
auxLoc = auxLoc->proximoLoc;
}
printf("\n\n\n");
printf(" ");
system("pause");
}else{
linha();
printf("\n Não há locações realizadas!\n\n\n");
printf(" ");
system("pause");
}
break;
case 3 :
system("cls");
menu();
linha();
printf(" PESQUISAR LOCAÇÕES\n");
linha();
auxLoc = inicioLoc;
Locacao *anteriorLoc = inicioLoc;
anteriorVei = inicioVei;
auxVei = inicioVei;
dif = -1;
97
if (auxLoc != NULL){
printf(" Digite a placa do veículo desejado: ");
fgets(placa, sizeof(placa), stdin);
fflush(stdin);
placa[strlen(placa)-1]='\0';
while (auxLoc != NULL || dif == 0){
op = -1;
dif = strcmp(auxLoc->placa,placa);
if (dif == 0){
op = 1;
linha();
printf(" Nome: %s | ", auxLoc->nome);
printf(" CPF/CNPJ: %s", auxLoc->cpfCnpj);
printf("\n\n Veículo: %s | ", auxLoc->modelo);
printf(" Placa: %s | ", auxLoc->placa);
printf(" Total de diárias: %d", auxLoc->diarias);
printf("\n Data Locação: %s %s | ", auxLoc->dataIni,
auxLoc->horaIni);
printf(" Data devolução: %s %s", auxLoc->dataFim,
auxLoc->horaIni);
printf("\n Status: %s", auxLoc->status);
printf("\n\n DIGITE: 0 - SAIR | 1 - CANCELAR
LOCAÇÃO | 2 - FINALIZAR LOCAÇÃO: ");
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
98
strcpy(auxLoc->status, "Cancelado");
printf("\n Locação cancelada!");
break;
case 2 :
while (strcmp(auxVei->placa, auxLoc->placa) != 0){
auxVei = auxVei->proximoVei;
}
system("cls");
menu();
linha();
printf(" PESQUISAR LOCAÇÕES\n");
linha();
printf(" Nome: %s | ", auxLoc->nome);
printf(" CPF/CNPJ: %s", auxLoc->cpfCnpj);
printf("\n\n Veículo: %s | ", auxLoc->modelo);
printf(" Placa: %s | ", auxLoc->placa);
printf(" Total de diárias: %d", auxLoc->diarias);
printf("\n Data Locação: %s %s | ", auxLoc->dataIni,
auxLoc->horaIni);
printf(" Data devolução: %s %s", auxLoc->dataFim,
auxLoc->horaIni);
printf("\n Status: %s", auxLoc->status);
printf("\n\n Houve atraso na devolução?");
printf("\n Se sim informar a quantidade de horas, se
não informe ""0""(Zero): ");
scanf("%d", &qtdHoras);
strcpy(auxVei->status, "Livre");
strcpy(auxLoc->status, "Finalizado");
if (strcmp(auxVei->categoria, "Economica") == 0){
if (strcmp(parceriaCli, "Sim") == 0){
total = ((diarias * vlrEcon) + ((vlrEcon / 24)*
qtdHoras)) / 1.05;
99
printf("\n VALOR TOTAL: %0.2f", total);
}else{
if (idadeCli >= 60){
total = ((diarias * vlrEcon) + ((vlrEcon / 24)*
qtdHoras)) / 1.10;
printf("\n VALOR TOTAL: %0.2f", total);
}else{
total = ((diarias * vlrEcon) + ((vlrEcon / 24)*
qtdHoras));
printf("\n VALOR TOTAL: %0.2f", total);
}
}
}
if (strcmp(auxVei->categoria, "Economica") == 0){
if (strcmp(parceriaCli, "Sim") == 0){
total = ((diarias * vlrInter) + ((vlrInter / 24)*
qtdHoras)) / 1.05;
printf("\n VALOR TOTAL: %0.2f", total);
}else{
if (idadeCli >= 60){
total = ((diarias * vlrInter) + ((vlrInter / 24)*
qtdHoras)) / 1.10;
printf("\n VALOR TOTAL: %0.2f", total);
}else{
total = ((diarias * vlrInter) + ((vlrInter / 24)*
qtdHoras));
printf("\n VALOR TOTAL: %0.2f", total);
}
}
}
if (strcmp(auxVei->categoria, "Economica") == 0){
100
if (strcmp(parceriaCli, "Sim") == 0){
total = ((diarias * vlrLuxo) + ((vlrLuxo / 24)*
qtdHoras)) / 1.05;
printf("\n VALOR TOTAL: %0.2f", total);
}else{
if (idadeCli >= 60){
total = ((diarias * vlrLuxo) + ((vlrLuxo / 24)*
qtdHoras)) / 1.10;
printf("\n VALOR TOTAL: %0.2f", total);
}else{
total = ((diarias * vlrLuxo) + ((vlrLuxo / 24)*
qtdHoras));
printf("\n VALOR TOTAL: %0.2f", total);
}
}
}
printf("\n Locação finalizada!");
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
printf("\n Foi digitada uma placa inválida!\n\n\n");
printf(" ");
system("pause");
101
break;
}
}else{
linha();
printf("\n Não há locações realizadas!\n\n\n");
printf(" ");
system("pause");
}
break;
case 4 :
system("cls");
menu();
linha();
printf(" PREÇOS\n");
linha();
printf(" Cadastrar preços: (R$/Dia)\n\n");
printf(" Categoria - Econômico: ");
scanf("%f", &vlrEcon);
fflush(stdin);
printf("\n Categoria - Intermediário: ");
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
102
printf("\n Opção inválida!\n\n\n");
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
menu(); //Executa a função "Menu"
opcaoTelas(4); //Executa a função tela
printf("\n TELA - DIGITE O NÚMERO DA OPÇÃO ESCOLHIDA: ");
scanf("%d", &opcao);
getchar();
switch(opcao){
case 0 :
break;
case 1 :
do{
system("cls");
103
menu();
linha(); // Exibe a função linha que cria uma linha de 80
posições
printf (" CADASTRO DE USUÁRIO \n");
linha();
printf("\n Nome completo: ");
fgets(nome, sizeof(nome), stdin);
nome[strlen(nome)-1]='\0';//remove a quebra de linha da
string
fflush(stdin); //Limpa o buffer do teclado
printf("\n Usuário: ");
fgets(user, sizeof(user), stdin);
user[strlen(user)-1]='\0';
fflush(stdin);
printf("\n Senha: ");
fgets(senha, sizeof(senha), stdin);
senha[strlen(senha)-1]='\0';
fflush(stdin);
if ((strlen(nome) == 0)||(strlen(user) == 0)||(strlen(senha)
== 0)){ //Verifica se todos os campos estão preenchidos
printf("\n Todos o campos são de preenchimento
Obrigatório!\n\n");
system("pause"); // Gera uma pausa até que alguma
tecla seja pressionada
}
}while ((strlen(nome) == 0)||(strlen(user) == 0)||(strlen(senha)
== 0));//Realiza um loop até que todos os campos estejam preenchidos
dif = -1;
Usuario *check = inicioUser; //Cria uma struct auxiliar de
nome check
while (check != NULL){ //Executa o loop até enquanto check
for diferente de NULL
dif = strcmp(check->nomeUsuario, user); //compara se o
usuário ja existe no cadastro
104
if (dif == 0){
printf("\n Usuário já cadastrado!\n");
printf("\n\n Cadastro cancelado!\n\n");
break;
}else{
check = check->proximoUser; //Enquanto check for
diferente de NULL, vai para o próximo registro
}
}
free(check);//Libera a struct check da memória
if (dif != 0){
printf("\n Cadastro: 0 - Cancelar | 1 - Gravar: ");
scanf("%d", &op);
if (op == 1){
Usuario *usuario = (Usuario*) malloc(sizeof(Usuario));
//Aloca um espaço de memória para struct usuário
strcpy(usuario->nomeCompleto, nome); // copia o
conteúdo da variável para a struct
strcpy(usuario->nomeUsuario, user);
strcpy(usuario->senha, senha);
usuario->proximoUser = NULL;
if (inicioUser == NULL){ //Se não houver nenhum
cadastro
inicioUser = usuario;// Cadastra o primeiro registro
}else{ //Se não
usuario->proximoUser = inicioUser; //Aponta para o
próximo registro
inicioUser = usuario; //Define a struct usuario no inicio
}
gravar = 1; //variável de apoio
printf("\n\n Usuário cadastrado com sucesso!\n\n");
}else{
printf("\n\n Cadastro cancelado\n\n!");
105
}
}
system("pause");
break;
case 2 ://Exibe usuários cadastrados
system("cls");
menu();
linha();
printf (" USUÁRIOS CADASTRADOS \n");
Usuario *auxUser = inicioUser;
if (auxUser != NULL){
while (auxUser != NULL){
linha();
printf(" Nome: %s\n", auxUser->nomeCompleto);
printf(" Usuário: %s\n", auxUser->nomeUsuario);
printf(" Senha: %s\n", auxUser->senha);
auxUser = auxUser->proximoUser;
}
printf("\n\n");
system("pause");
}else{
printf("\n Não há usuários cadastrados!\n");
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
106
linha();
printf (" PESQUISAR USUÁRIOS \n");
linha();
Usuario *auxUser = inicioUser;
Usuario *anteriorUser = inicioUser;
dif = -1;
if (auxUser != NULL){
printf("\n Digite o usuário para pesquisa: ");
fgets(user, sizeof(user), stdin);
fflush(stdin);
user[strlen(user)-1]='\0';
while (auxUser != NULL || dif == 0){
dif = strcmp(auxUser->nomeUsuario,user);
if (dif == 0){
printf("------------------------------------------\n");
printf(" Nome: %s\n", auxUser->nomeCompleto);
printf(" Usuário: %s\n", auxUser->nomeUsuario);
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
printf("\n Não há usuários cadastrados!\n\n\n");
system("pause");
break;
}
if (dif == 0){
do{
107
printf("\n DIGITE: 0 - SAIR | 1 - ALTERAR | 2 -
EXCLUIR: ");
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
printf (" PESQUISAR
USUÁRIOS \n");
linha();
printf("\n Nome completo: ");
fgets(nome, sizeof(nome), stdin);
nome[strlen(nome)-1] = '\0';
fflush(stdin);
printf("\n Usuário: ");
fgets(user, sizeof(user), stdin);
user[strlen(user)-1] = '\0';
fflush(stdin);
printf("\n Senha: ");
fgets(senha, sizeof(senha), stdin);
senha[strlen(senha)-1] = '\0';
fflush(stdin);
if ((strlen(nome) == 0)||(strlen(user) ==
0)||(strlen(senha) == 0)){
printf("\n Todos o campos são de
preenchimento Obrigatório!\n\n");
system("pause");
}
108
}while ((strlen(nome) == 0)||(strlen(user) ==
0)||(strlen(senha) == 0));
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
anteriorUser->proximoUser = auxUser-
>proximoUser;
auxUser = NULL;
}
}
op = 0;
printf("\n Registro excluído!\n\n");
gravar = 1;
system("pause");
break;
109
default :
printf("\n Opção inválida!\n\n");
fflush(stdin);
system("pause");
break;
}
}while (op != 0);
}else{
printf("\n Nome de usuário inválido!\n");
system("pause");
break;
}
}while (op != 0);
break;
default :
printf("\n Opção inválida!\n\n");
fflush(stdin);
system("pause");
break;
}
if (gravar == 1){//Se a variavel gravar for igual a 1, grava os dados da
struct no arquivo
Usuario *usuario = inicioUser;//Move o ponteiro para o primeiro
registro da struct
arquivo = fopen("Usuarios.txt", "w");//Abre o arquivo de usuarios
em modo de escrita "W)
if(arquivo == NULL){//Verifica se o arquivo foi aberto com êxito.
printf("Erro, não foi possível abrir o arquivo\n");
system("pause");
}else{
while (usuario != NULL){ //Enquanto houver registros na struct,
grava os mesmo no arquivo
fprintf(arquivo, "%s|%s|%s\n", usuario->nomeCompleto,
usuario->nomeUsuario, usuario->senha);
110
usuario = usuario->proximoUser;//Move o ponteiro da struct
pelos registros
}
}
fclose(arquivo);//fecha o arquivo
gravar = 0;
}
}while(opcao != 0);
system("cls");
} //RECEBER DADOS DE CADASTRO DE USUARIO
void relatorios(){
int op, opcao;
do{
system("cls");
menu();
linha(); // Exibe a função linha que cria uma linha de 80 posições
printf (" RELATÓRIOS\n");
linha();
printf(" 0 SAIR | 1 VEÍCULOS | 2 CLIENTES | 3 LOCACÕES: ");
scanf("%d", &op);
switch (op){
case 0 :
break;
case 1 :
system("cls");
menu();
linha();
printf (" VEÍCULOS\n");
linha();
Veiculos *auxVei = inicioVei;
if (auxVei == NULL){
printf("\n Não há Veículos Cadastrados!");
}
111
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
printf (" CLIENTES\n");
linha();
Clientes *auX = inicioCli;
if (auxVei == NULL){
printf("\n Não há Clientes Cadastrados!");
}
while (auX != NULL){
printf(" NOME: %s", auX->nome);
printf("\n CPF/CNPJ: %s", auX->cpfCnpj);
printf("\n IDADE: %d", auX->idade);
printf("\n PARCEIRO: %s", auX->parceiro);
printf("\n TELEFONE: %s", auX->telefone);
printf("\n ENDEREÇO: %s", auX->endereco);
printf("\n BAIRRO: %s", auX->bairro);
112
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
printf (" LOCAÇÕES\n");
linha();
Locacao *aux = inicioLoc;
if (auxVei == NULL){
printf("\n Não há Locações!");
}
while (aux != NULL){
printf(" MODELO: %s", aux->modelo);
printf("\n PLACA: %s", aux->placa);
printf("\n NOME: %s", aux->nome);
printf("\n CPF/CNPJ: %s", aux->cpfCnpj);
printf("\n RETIRADA: %s %s", aux->dataIni, aux->horaIni);
printf("\n DEVOLUÇÃO: %s %s", aux->dataFim, aux-
>horaFim);
printf("\n STATUS: %s", aux->status);
printf("\n");
linha();
aux = aux->proximoLoc;
113
}
op = -1;
printf("\n\n\n ");
system("pause");
break;
default :
printf("\n Opção Inválida!");
fflush(stdin);
break;
}
system("cls");
}while (op != 0);
}
int main() {
setlocale(LC_ALL, "Portuguese");
int opcao;
importaUsuarios(); // Função Importar Usuários
importaVeiculos(); // Função Importar Usuários
importaClientes(); // Função importar Clientes
do{
menu();
subMenu();
printf("\n MENU - DIGITE O NÚMERO DA TELA DE ACESSO: ");
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
114
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
printf("\n Opção inválida\n\n");
fflush(stdin);
printf(" ");
system("pause");
system("cls");
break;
}
}while(opcao != 0);
return 0;
}
