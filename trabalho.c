#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct token
{
    char nome[12];
    int valor, linha;
    struct token *prox;
}token;
typedef struct lista_token
{
    token *inicio;
    int cont;
}lista_token;
void inicializa_lista_token(lista_token *lt)
{
    lt->inicio = NULL;
    lt->cont=0;
}
void insere_token(char *nome,int linha,lista_token *lt)
{
    token *novo = (token *)malloc(sizeof(token));
    strcpy(novo->nome,nome);
    novo->valor=0;
    novo->linha=linha;
    if(lt->inicio==NULL)
    {
        lt->inicio=novo;
        novo->prox=NULL;
    }
    else
    {
        token *aux=lt->inicio;
        while(aux->prox!=NULL)
        {
            aux=aux->prox;
        }
        aux->prox=novo;
        novo->prox=NULL;
    }
    lt->cont++;
}
void mostra_tokens(lista_token *lt)
{
    int i;
    token *aux=lt->inicio;
    for(i=0;i<lt->cont;i++)
    {
        printf("Token: %s Linha: %d\n",aux->nome,aux->linha);
        aux=aux->prox;
    }
}



typedef struct celula
{
    char conteudo[600];
    struct celula *prox;
}celula;
typedef struct lista
{
    celula *inicio;
    int cont;
}lista;
void inicializaLista(lista *l)
{
    l->inicio = NULL;
    l->cont = 0;
}
int busca(char *x,lista *l)
{
    int i;
    celula *aux=l->inicio;
    int ret=0;
    for(i=0;i<l->cont;i++)
    {
        if(strcmp(x,aux->conteudo)==0) ret=1;
        aux = aux->prox;
    }
    return ret;
}
typedef struct id
{
    char conteudo[600];
    int codigo;
    struct id *prox;
}id;
typedef struct lista_id
{
    id *inicio;
    int cont;
}lista_id;
void inicializa_lista_id(lista_id *li)
{
    li->inicio=NULL;
    li->cont=0;
}
void insere_id(char *s,int cod, lista_id *li)
{
    id *novo=(id *)malloc(sizeof(id));
    novo->codigo=cod;
    strcpy(novo->conteudo,s);
    novo->prox=li->inicio;
    li->inicio=novo;
    li->cont++;
}
int pesquisa(char *x,lista_id *li)
{
    int i,ret=0;
    id *aux=li->inicio;
    if(aux==NULL) return ret;
    while(aux->prox!=NULL)
    {
        if(strcmp(x,aux->conteudo)==0)
        {
            ret=aux->codigo;
        }
        aux=aux->prox;
    }
    if(strcmp(x,aux->conteudo)==0)
    {
        ret=aux->codigo;
    }
    return ret;
}
void insere(char *x,lista *l)
{
    celula *novo;
    novo = (celula *)malloc(sizeof(celula));
    strcpy(novo->conteudo,x);
    novo->prox=l->inicio;
    l->inicio=novo;
    l->cont++;
}
void imprime_id(lista_id *li)
{
    id *aux=li->inicio;
    int i;
    for(i=0;i<li->cont;i++)
    {
        printf("%s\n",aux->conteudo);
        aux=aux->prox;
    }
}
void imprime(lista *l)
{
    int i;
    celula *aux=l->inicio;
    for(i=0;i<l->cont;i++)
    {
        printf("%s\n",aux->conteudo);
        aux=aux->prox;
    }
}

typedef struct sintatico
{
    int valor;
    struct sintatico *prox;
}sintatico;
typedef struct pilha_sintatico
{
    sintatico *inicio_sintatico;
    int cont;
}pilha_sintatico;
void inicializa_sintatico(pilha_sintatico *ps)
{
    ps->inicio_sintatico = NULL;
    ps->cont=0;
}
void empilha_sintatico(int valor,pilha_sintatico *ps)
{
    sintatico *novo = (sintatico *)malloc(sizeof(sintatico));
    novo->valor=valor;
    if(ps->inicio_sintatico==NULL)
    {
        ps->inicio_sintatico=novo;
        novo->prox=NULL;
        ps->cont++;
    }
    else
    {
        novo->prox=ps->inicio_sintatico;
        ps->inicio_sintatico=novo;
        ps->cont++;
    }
}
int espia_sintatico(pilha_sintatico *ps)
{
    sintatico *aux = ps->inicio_sintatico;
    if(aux!=NULL)
        return aux->valor;
    return -1;
}
void desempilha_sintatico(pilha_sintatico *ps)
{
    sintatico *aux = ps->inicio_sintatico;
    if(aux==NULL)
        return;
    ps->inicio_sintatico=aux->prox;
    free(aux);
    ps->cont--;
}

/*
* Lista de valores para sintatico
* Variaveis
* 1 - <Programa>
* 2 - <Decl_Sequencia>
* 3 - <Decl>
* 4 - <Decl'>
* 5 - <Comandos>
* 6 - <Comandos'>
* 7 - <Comando>
* 8 - <Exp1>
* 9 - <Exp1'>
* 10 - <Exp2>
* 11 - <Exp2'>
* 12 - <Exp3>
* Terminais
* 13 - inicio
* 14 - fim
* 15 - ;
* 16 - ,
* 17 - :
* 18 - escreva
* 19 - leia
* 20 - id
* 21 - :=
* 22 - (
* 23 - )
* 24 - num
* 25 - +
* 26 - -
* 27 - *
* 28 - int
* 29 - $
*/
void analise_preditiva_tabular(lista_token *tok, pilha_sintatico *ps)
{

    token *unidade_controle = tok->inicio;
    while(unidade_controle!=NULL)
    {
        printf("U.C: %s\n",unidade_controle->nome);
        if(strcmp(unidade_controle->nome,"INICIO")==0) // Unidade de controle aponta para 'inicio'
        {
            if(espia_sintatico(ps)==1) // <Programa> no topo da pilha
            {
                //empilha inicio<Decl_Sequencia>;<Comandos>;fim
                desempilha_sintatico(ps);
                empilha_sintatico(14,ps);
                empilha_sintatico(15,ps);
                empilha_sintatico(5,ps);
                empilha_sintatico(15,ps);
                empilha_sintatico(2,ps);
                empilha_sintatico(13,ps);
            }
            else if(espia_sintatico(ps)==13) // 'inicio' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"PONTOVIRGULA")==0) // Unidade de controle aponta para ';'
        {
            if(espia_sintatico(ps)==4) // <Decl'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==6) //<Comandos'> no topo da pilha
            {
                token *auxiliar = unidade_controle->prox; // Ambiguidade: olha um a frente na unidade de controle
                if(strcmp(auxiliar->nome,"ID")==0||strcmp(auxiliar->nome,"LEIA")==0||strcmp(auxiliar->nome,"ESCREVA")==0) //caso ID, inicio ou escreva
                {
                    // empilha ;<Comando><Comandos'>
                    desempilha_sintatico(ps);
                    empilha_sintatico(6,ps);
                    empilha_sintatico(5,ps);
                    empilha_sintatico(15,ps);
                }
                else
                {
                    desempilha_sintatico(ps);
                }
            }
            else if(espia_sintatico(ps)==9) // <Exp1'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==11) // <Exp2'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==15) // ';' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"VIRGULA")==0) // Unidade de controle aponta para ','
        {
            if(espia_sintatico(ps)==4) // <Decl'> no topo da pilha
            {
                //empilha ,<Decl>
                desempilha_sintatico(ps);
                empilha_sintatico(3,ps);
                empilha_sintatico(16,ps);
            }
            else if(espia_sintatico(ps)==16) // ',' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"ESCREVA")==0) // Unidade de controle aponta para 'escreva'
        {
            if(espia_sintatico(ps)==5) // <Comandos> no topo da pilha
            {
                //empilha <Comando><Comandos'>
                desempilha_sintatico(ps);
                empilha_sintatico(6,ps);
                empilha_sintatico(7,ps);
            }
            else if(espia_sintatico(ps)==7) //<Comando> no topo da pilha
            {
                //empilha escreva(id)
                desempilha_sintatico(ps);
                empilha_sintatico(23,ps);
                empilha_sintatico(20,ps);
                empilha_sintatico(22,ps);
                empilha_sintatico(18,ps);
            }
            else if(espia_sintatico(ps)==18) // 'escreva' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d token: %s\n",unidade_controle->linha,unidade_controle->nome);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"LEIA")==0) // Unidade de controle aponta para 'leia'
        {
            if(espia_sintatico(ps)==5) // <Comandos> no topo da pilha
            {
                //empilha <Comando><Comandos'>
                desempilha_sintatico(ps);
                empilha_sintatico(6,ps);
                empilha_sintatico(7,ps);
            }
            else if(espia_sintatico(ps)==7) //<Comando> no topo da pilha
            {
                //empilha leia(id)
                desempilha_sintatico(ps);
                empilha_sintatico(23,ps);
                empilha_sintatico(20,ps);
                empilha_sintatico(22,ps);
                empilha_sintatico(19,ps);
            }
            else if(espia_sintatico(ps)==19) // 'leia' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"ID")==0) // Unidade de controle aponta para 'ID'
        {
            if(espia_sintatico(ps)==3) // <Decl> no topo da pilha
            {
                //empilha id<Decl'>
                desempilha_sintatico(ps);
                empilha_sintatico(4,ps);
                empilha_sintatico(20,ps);
            }
            else if(espia_sintatico(ps)==5) // <Comandos> no topo da pilha
            {
                //empilha <Comando><Comandos>
                desempilha_sintatico(ps);
                empilha_sintatico(6,ps);
                empilha_sintatico(7,ps);
            }
            else if(espia_sintatico(ps)==7) // <Comando> no topo da pilha
            {
                //empilha id:=<Exp1>
                desempilha_sintatico(ps);
                empilha_sintatico(8,ps);
                empilha_sintatico(21,ps);
                empilha_sintatico(20,ps);
            }
            else if(espia_sintatico(ps)==8) // <Exp1> no topo da pilha
            {
                //empilha <Exp2><Exp1'>
                desempilha_sintatico(ps);
                empilha_sintatico(9,ps);
                empilha_sintatico(10,ps);
            }
            else if(espia_sintatico(ps)==10) // <Exp2> no topo da pilha
            {
                //empilha <Exp3><Exp2'>
                desempilha_sintatico(ps);
                empilha_sintatico(11,ps);
                empilha_sintatico(12,ps);
            }
            else if(espia_sintatico(ps)==12) // <Exp3> no topo da pilha
            {
                //empilha id
                desempilha_sintatico(ps);
                empilha_sintatico(20,ps);
            }
            else if(espia_sintatico(ps)==20) // 'id' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"ABREPAR")==0) // Unidade de controle aponta para '('
        {
            if(espia_sintatico(ps)==8) // <Exp1> no topo da pilha
            {
                //empilha <Exp2><Exp1'>
                desempilha_sintatico(ps);
                empilha_sintatico(9,ps);
                empilha_sintatico(10,ps);
            }
            else if(espia_sintatico(ps)==10) //<Exp2> no topo da pilha
            {
                //empilha <Exp3><Exp2'>
                desempilha_sintatico(ps);
                empilha_sintatico(11,ps);
                empilha_sintatico(12,ps);
            }
            else if(espia_sintatico(ps)==12) // <Exp3> no topo da pilha
            {
                //empilha (<Exp1>)
                desempilha_sintatico(ps);
                empilha_sintatico(23,ps);
                empilha_sintatico(8,ps);
                empilha_sintatico(22,ps);
            }
            else if(espia_sintatico(ps)==22) // '(' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"FECHAPAR")==0) // Unidade de controle aponta para ')'
        {
            if(espia_sintatico(ps)==9) // <Exp1'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==11) // <Exp2'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==23) // ')' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"NUM")==0) // Unidade de controle aponta para 'num'
        {
            if(espia_sintatico(ps)==8) // <Exp1> no topo da pilha
            {
                //empilha <Exp2><Exp1'>
                desempilha_sintatico(ps);
                empilha_sintatico(9,ps);
                empilha_sintatico(10,ps);
            }
            else if(espia_sintatico(ps)==10) //<Exp2> no topo da pilha
            {
                //empilha <Exp3><Exp2'>
                desempilha_sintatico(ps);
                empilha_sintatico(11,ps);
                empilha_sintatico(12,ps);
            }
            else if(espia_sintatico(ps)==12) // <Exp3> no topo da pilha
            {
                //empilha num
                desempilha_sintatico(ps);
                empilha_sintatico(24,ps);
            }
            else if(espia_sintatico(ps)==24) // 'num' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"MAIS")==0) // Unidade de controle aponta para +
        {
            if(espia_sintatico(ps)==9) // <Exp1'> no topo da pilha
            {
                // empilha +<Exp2><Exp1'>
                desempilha_sintatico(ps);
                empilha_sintatico(9,ps);
                empilha_sintatico(10,ps);
                empilha_sintatico(25,ps);
            }
            else if(espia_sintatico(ps)==11) // <Exp2'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==25) // '+' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"MENOS")==0) // Unidade de controle aponta para '-'
        {
            if(espia_sintatico(ps)==9) // <Exp1'> no topo da pilha
            {
                //empilha -<Exp2><Exp1'>
                desempilha_sintatico(ps);
                empilha_sintatico(9,ps);
                empilha_sintatico(10,ps);
                empilha_sintatico(26,ps);
            }
            else if(espia_sintatico(ps)==11) // <Exp2'> no topo da pilha
            {
                desempilha_sintatico(ps);
            }
            else if(espia_sintatico(ps)==26) // '-' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"PRODUTO")==0) //Unidade de controle aponta para '*'
        {
            if(espia_sintatico(ps)==11) // <Exp2'> no topo da pilha
            {
                //empilha *<Exp3><Exp2'>
                desempilha_sintatico(ps);
                empilha_sintatico(11,ps);
                empilha_sintatico(12,ps);
                empilha_sintatico(27,ps);
            }
            else if(espia_sintatico(ps)==27) // '*' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"INT")==0) //Unidade de controle aponta para 'int'
        {

            if(espia_sintatico(ps)==2) // <Decl_Sequencia> no topo da pilha
            {
                //empilha int:<Decl>
                desempilha_sintatico(ps);
                empilha_sintatico(3,ps);
                empilha_sintatico(17,ps);
                empilha_sintatico(28,ps);
            }
            else if(espia_sintatico(ps)==28) // 'int' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"DOISPONTOS")==0) // Unidade de controle aponta para ':'
        {
            if(espia_sintatico(ps)==17) // ':' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"ATRIBUI")==0) // Unidade de controle aponta para ':='
        {
            if(espia_sintatico(ps)==21) // ':=' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
        else if(strcmp(unidade_controle->nome,"FIM")==0) // Unidade de controle aponta para 'fim'
        {
            if(espia_sintatico(ps)==14) // 'fim' no topo da pilha
            {
                desempilha_sintatico(ps);
                unidade_controle=unidade_controle->prox;
            }
            else
            {
                printf("\nErro sintatico: linha %d\n",unidade_controle->linha);
                return;
            }
        }
    }
}

int main(void)
{
    FILE *fp;
    fp = fopen("exemplo1.txt","r");
    char c;
    int contLinha = 1;
    //int contID=1;
    /* Declarando lista de tokens */
    lista_token tok;
    inicializa_lista_token(&tok);
    /* Fim declaracao de lista de tokens */

    /* Construindo lista de palavras reservadas */
    lista pr;
    inicializaLista(&pr);
    insere("inicio",&pr);
    insere("fim",&pr);
    insere("leia",&pr);
    insere("escreva",&pr);
    insere("num",&pr);
    insere("id",&pr);
    insere("int",&pr);
    insere("+",&pr);
    insere("-",&pr);
    insere("*",&pr);
    insere(";",&pr);
    insere(":",&pr);
    insere(":=",&pr);
    insere("(",&pr);
    insere(")",&pr);
    insere(",",&pr);
    /* Fim contrucao da lista de palavras reservadas */

    // Pilha para analise sintatica
    pilha_sintatico ps;
    inicializa_sintatico(&ps);
    empilha_sintatico(1,&ps);

    // Fim pilha

    /* Lista de ID's */
    lista_id ids;
    inicializa_lista_id(&ids);
    while((c=fgetc(fp))!=EOF)
    {
        if(c=='\n')
        {
            contLinha++;
        }
        else if(c==' '||c==9){}
        else if(c=='/')
        {
            c=fgetc(fp);
            if(c=='*')
            {
                while((c=fgetc(fp))!='/'&&c!=EOF)
                {
                    if(c!='*')
                    {
                        while((c=fgetc(fp))!='*'&&c!=EOF)
                        {
                            if(c=='\n') contLinha++;
                        }
                    }
                    else if(c!='/'&&c=='*')
                    {
                        while((c=fgetc(fp))=='*'&&c!=EOF)
                        {
                            if(c=='\n') contLinha++;
                        }
                    }
                }
            }
            else
            {
                while((c=fgetc(fp))!=' '&&c!=EOF)
                {
                    if(c=='\n') contLinha++;
                }
                printf("Erro lexico na linha %d: identificador invalido\n",contLinha);
            }
        }
        else if(c>=48&&c<=57) /* Caso Numero */
        {
            int isNumber=1;
            int idInvalido=0;
            int numeroInvalido=0;
            char s[600];
            char s2[1];
            s2[0]=c;
            strcat(s,s2);
            c=fgetc(fp);
            while(c!=' '&&c!='\n'&&c!=EOF)
            {
                s2[0]=c;
                strcat(s,s2);
                if(c>=48&&c<=57){}
                else if(c=='.')
                {
                    isNumber=0;
                    numeroInvalido=1;
                }
                else
                {
                    isNumber=0;
                    numeroInvalido=0;
                    idInvalido=1;
                }
                c=fgetc(fp);
            }
            if(isNumber==1)
            {
                insere_token("NUM",contLinha,&tok);
            }
            else if(numeroInvalido==1)
            {
                printf("Erro lexico na linha %d: Numero invalido\n",contLinha);
            }
            else
            {
                printf("Erro lexico na linha %d: Id invalido\n",contLinha);
            }
            if(c=='\n') contLinha++;
        }
        else if((c>=97&&c<=122)||(c>=65&&c<=90)) /* Caso caractere */
        {
            int idInvalido=0;
            char s[600];
            s[0]='\0';
            char s2[2];
            s2[0]=c;
            s2[1]='\0';
            strcat(s,s2);
            while((c=fgetc(fp))!=' '&&c!='\n'&&c!=EOF)
            {
                s2[0]=c;
                strcat(s,s2);
                if((c>=97&&c<=122)||(c>=65&&c<=90)||(c>=48&&c<=57)){}
                else
                {
                    idInvalido=1;
                }
            }
            if(idInvalido==1)
            {
                printf("Erro lexico na linha %d: ID invalido\n",contLinha);
            }
            else if(idInvalido==0&&(busca(s,&pr)==0))
            {
                if(pesquisa(s,&ids)==0)
                {
                    insere_token("ID",contLinha,&tok);
                    //insere_id(s,contID,&ids);
                    //contID++;
                }
                else
                {
                    insere_token("ID",contLinha,&tok);
                }

            }
            else if(idInvalido==0&&busca(s,&pr)==1)
            {
                if(strcmp(s,"inicio")==0)
                {
                    insere_token("INICIO",contLinha,&tok);
                }
                else if(strcmp(s,"fim")==0)
                {
                    insere_token("FIM",contLinha,&tok);
                }
                else if(strcmp(s,"leia")==0)
                {
                    insere_token("LEIA",contLinha,&tok);
                }
                else if(strcmp(s,"escreva")==0)
                {
                    insere_token("ESCREVA",contLinha,&tok);
                }
                else if(strcmp(s,"num")==0)
                {
                    insere_token("NUMERO",contLinha,&tok);
                }
                else if(strcmp(s,"id")==0)
                {
                    insere_token("ID",contLinha,&tok);
                }
                else if(strcmp(s,"int")==0)
                {
                    insere_token("INT",contLinha,&tok);
                }
            }
            if(c=='\n') contLinha++;
        }
        else if(c=='-')
        {
            int numInvalido=1;
            int idInvalido=0;
            while((c=fgetc(fp))!=' '&&c!='\n'&&c!=EOF)
            {
                if((c>=48&&c<=57)||c=='.'){}
                else
                {
                    numInvalido=0;
                    idInvalido=1;
                }
            }
            if(numInvalido==1)
            {
                printf("Erro lexico na linha %d: numero invalido\n",contLinha);
            }
            else if(idInvalido==1)
            {
                printf("Erro lexico na linha %d: ID invalido\n",contLinha);
            }
            if(c=='\n') contLinha++;
        }
        else if(c=='+'||c=='-'||c=='*'||c==';'||c==':'||c=='('||c==')'||c==',')
        {
            char s[600];
            s[0]='\0';
            char s2[2];
            s2[0]=c;
            s2[1]='\0';
            strcat(s,s2);
            while((c=fgetc(fp))!=' '&&c!='\n'&&c!=EOF)
            {
                s2[0]=c;
                strcat(s,s2);
            }
            if(strcmp(s,"+")==0)
            {
                insere_token("MAIS",contLinha,&tok);
            }
            else if(strcmp(s,"-")==0)
            {
                insere_token("MENOS",contLinha,&tok);
            }
            else if(strcmp(s,"*")==0)
            {
                insere_token("PRODUTO",contLinha,&tok);
            }
            else if(strcmp(s,";")==0)
            {
                insere_token("PONTOVIRGULA",contLinha,&tok);
            }
            else if(strcmp(s,":")==0)
            {
                insere_token("DOISPONTOS",contLinha,&tok);
            }
            else if(strcmp(s,":=")==0)
            {
                insere_token("ATRIBUI",contLinha,&tok);
            }
            else if(strcmp(s,"(")==0)
            {
                insere_token("ABREPAR",contLinha,&tok);
            }
            else if(strcmp(s,")")==0)
            {
                insere_token("FECHAPAR",contLinha,&tok);
            }
            else if(strcmp(s,",")==0)
            {
                insere_token("VIRGULA",contLinha,&tok);
            }
            else
            {
                printf("Erro lexico na linha %d: ID invalido\n",contLinha);
            }
            if(c=='\n') contLinha++;

        }
        else
        {
            while((c=fgetc(fp))!=' '&&c!='\n'&&c!=EOF){printf("%c",c);}
            printf("Erro lexico na linha %d: ID invalido\n",contLinha);
            if(c=='\n') contLinha;
        }
    }
    printf("\n");
    mostra_tokens(&tok);
    // ------------------------------------****-------------------------------------------------------------------
    // INICIO ANALISE SINTATICA
    analise_preditiva_tabular(&tok,&ps);
    //FIM ANALISE SINTATICA
    fclose(fp);
    return 0;
}
