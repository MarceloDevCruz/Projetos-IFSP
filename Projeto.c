// Aluno: Marcelo Ferreira Cruz;
// Prontuário: SP3068862;

// IFSP Campus São Paulo; Eurides Balbino EDDA2;
// Projeto da disciplina Estrutura de Dados, segundo semestre;

// Feito com Visual Studio Code e DEV-C++;
// 17/10/2021, Início do projeto.
// 12/12/2021, Fim do projeto.


/*--------------------Bibliotecas---------------------*/
   #include <stdio.h>
   #include <stdlib.h>
   #include <conio.h>
   #include <malloc.h>
   #include <locale.h>
   #include <string.h>
   #include <windows.h>
// A biblioteca windows é apenas necessária caso uso da IDE Visual Studio Code.
// porém no DEV-C++ ela não é compilada... ???
/*----------------------------------------------------*/


/*---------------------Defines------------------------*/
#define TRUE       1 // definição de TRUE  para tipos booleanos.
#define FALSE     -1 // definição de FALSE para tipos booleanos.
#define MAXIMO     5 // definir o máximo de produtos que podem ter em uma mesma gôndola.
// A qualquer momento do programa poderá usar a definição de máximo, para aumentar a
// capacidade das gôndolas do supermercado
/*---------------------------------------------------*/


/*-------------------Typedefs------------------------*/
typedef int bool; // definição do tipo booleano "bool" para retornos de TRUE ou FALSE.
/*---------------------------------------------------*/


/*----------------------Login------------------------*/
/* Estrutura do registro e gestão de usuários */
typedef struct {
    char      nome       [100+1];
    char      prontuario [10+1];
}   LOGIN;
/*---------------------------------------------------*/


/*----------------------PILHA------------------------*/
/* Definindo a estrutura da pilha */
typedef struct {
    char      nome      [30+1];
    char      descricao [100+1];
    int       peso;
    float     preco;      
} REGISTRO_p;

typedef struct ELEMENTO_p {
    REGISTRO_p  registro_p;
    struct      ELEMENTO_p *PROXIMO;
} ELEMENTO_p;

typedef ELEMENTO_p *PONTEIRO_p;

typedef struct {
    PONTEIRO_p topo;
} PILHA;
/*---------------------------------------------------*/


/*----------------------FILA-------------------------*/
/* Definindo a estrutura da fila */
typedef struct {
    char      nome      [30+1];
    char      descricao [100+1];
    int       peso;
    float     preco;       
} REGISTRO_f;

typedef struct aux_f {
	REGISTRO_f   registro_f;
	struct       aux_f *PROXIMO_f; 
} ELEMENTO_f;

typedef ELEMENTO_f  *PONTEIRO_f;

typedef struct {
	PONTEIRO_f  inicio;
	PONTEIRO_f  fim;
} FILA;
/*---------------------------------------------------*/


/*--------------------Protótipos de funções------------------------*/
void        main                 ();
void        menuLOGIN            ();
void        gerenciaCadastro     (LOGIN);
void        arquivoDAT           ();
void        visualizarDAT        ();
void        novoUsuarioDAT       ();
int         particiona           (LOGIN*,int,int); 
void        troca_maior          (LOGIN*,int,int); 
void        troca_pivo           (LOGIN*,int,int); 
void        quick_sort           (LOGIN*,int,int);
void        buscaBinaria         (LOGIN);
long int    DAT_tamanho          ();
void        abasteceVetDAT       (LOGIN*);
void        menuUsuario          (LOGIN);
void        menu_gondola         (LOGIN);
bool        CAIXA_PDV            (FILA*);
bool        verUSUARIO_MASTER    (LOGIN);
bool        retirar_produto      (PILHA*,REGISTRO_p*);
bool        PUSH_pilha           (PILHA*,REGISTRO_p);
bool        iniciarPilha         (PILHA*);
REGISTRO_p  inserir_produto      ();
void        consulta_gondolas    (PILHA*);
void        inserePilha          (PILHA*);
bool        estaVazia            (PILHA*);
void        excluiPilha          (PILHA*);
bool        iniciarFILA          (FILA*);
bool        inserirNaFILA        (FILA*,REGISTRO_p);
void        qual_gondola         (PILHA*,char*,LOGIN);
void        caso_abastecer       (char,LOGIN);
void        caso_consultar       (char,LOGIN);
void        caso_retirar         (char,LOGIN);
void        gondola_vazia        ();
int         tamanho_pilha        (PILHA*);
void        gondola_cheia        ();
/*-----------------------------------------------------------------*/


/*---------------Váriaveis globais------------------*/
bool    indice_p1 = FALSE; // Esse índice serve para iniciar a estrutura de dados do tipo pilha.
bool    indice_p2 = FALSE; // Esse índice serve para iniciar a estrutura de dados do tipo pilha para o carrinho.
bool    indice_f  = FALSE; // Esse índice serve para iniciar a estrutura de dados do tipo fila.
PILHA   gondola[10];       // Uma variável global do tipo PILHA que é um vetor, será essêncial para criar as 10 gôndolas do requisito do projeto.
PILHA   carrinho;          // Variável global, ela será responsável de, assim que o produto sair da gondula, fazer uma cópia e armazenar no carrinho.
FILA    caixa;             // Variável para utilizar na hora de passar os produtos do carrinho para o caixa/PDV.
/*--------------------------------------------------*/


/*--------------------Funções------------------------*/

// A função main é necessária para o inicio do programa, nela se defini o idioma do programa que deverá seguir nesse caso o
// Português do Brasil, é necessário a biblioteca locale, logo em seguida é chamada a função de login.
void main () {

    setlocale(LC_ALL, "Portuguese_Brazil");
    menuLOGIN();
}

// A função menuLOGIN, recebe parâmetros do usuário para fazer login no sistema, é usada a função de busca binaria caso o usuário não tenha se logado
// como um usuário "MASTER", neste caso o usuário MASTER terá acesso exclusivo de algumas funcionalidade do programa, como o gerênciamento de
// usuários, e inclusão de itens nas gôndolas. 
void menuLOGIN () {

    LOGIN   login; 
    char    MASTER[7] = "MASTER"; // Esse vetor de char será essêncial para fazer a comparação com o que o usuário digitou

    system("mode 68,8"); system("color 97");
    printf("\nNOME DO USUÁRIO          : "    ); fflush(stdin); gets(login.nome);       // Pega informações do usuário, o nome dele
    printf("\n\nPRONTUÁRIO DO USUÁRIO    : "  ); fflush(stdin); gets(login.prontuario); // Pega informações do usuário, o prontuário dele

    if ( strcmp(login.nome, MASTER) == 0 && strcmp(login.prontuario, MASTER) == 0) {    // Compara o que o usuário digitou, com "MASTER" se for igual,
        menuUsuario (login);                                                            // ele abrirá o programa do menu do Supermercado.    
    }
    else {
        buscaBinaria(login); // Fará busca binária com os parâmetros que foram usados para tentar realizar o login
    }
}

// A função gerenciaCadastro, é um Menu para gerênciar o cadastro de usuários, tem a opção de Reiniciar arquivo DAT, que serve para reiniciar ou criar
// um novo arquivo DAT com usuários default já registrados no código, a opção de visualizad DAT, poderá ver todos os usuários já cadastrados no sistema
// e o Cadastrar novos usuários, como o nome já diz fará o cadastro de novos usuários no sistema.
void gerenciaCadastro (LOGIN loginUsuario) {

    char opc;
    
    /* O menu permanecerá em looping até que seja digitado a tecla 0*/
    do {
    system("cls"); system("mode 44,13"); system("color 03");
    printf("\n");
    printf("____________________________________________"  );
    printf("\n\t GERENCIADOR DE USUÁRIOS "                 );
    printf("\n____________________________________________");
    printf("\n\n\t1. Criar arquivo DAT "                   );
    printf("\n\t2. Visualizar arquivo DAT  "               );
    printf("\n\t3. Cadastrar novos usuários "              );
    printf("\n\t0. Sair  "                                 );
    printf("\n____________________________________________");
    printf("\n\tEscolha: "                                 );
    opc = getche(); getch();

    switch(opc) {
    	
    	// Iniciará o arquivo DAT ou irá restaurar para o original.
        case '1': arquivoDAT     ();             break;
        
        // Poderá visualizar o arquivo DAT, e ver todos os usuários registrados no arquivo.
        case '2': visualizarDAT  ();             break;
        
        // Registrará um novo usuário.
        case '3': novoUsuarioDAT ();             break;
        
        // Retornará para o menu do usuário.
        case '0': menuUsuario    (loginUsuario); break;
        default :        
        system("cls"); printf("\n\n\n\n\n\n\t    ESCOLHA UMA OPÇÃO VÁLIDA!!!");
        getch(); gerenciaCadastro(loginUsuario); 
    }
    }
    while ( opc != '0');
}

// A função arquivoDAT, criará ou reiniciará arquivo USUARIOS.DAT com 29 registros default dos usuários do sistema
void arquivoDAT () {

    int      i;
    FILE    *arquivo;
    LOGIN    usuario[29] = {
        {"Domingos Lucas Latorre de Oliveira"    , "CJ146456"},
        {"Leandro Pinto Santana"                 , "CP220383"},
        {"Rodrigo Ribeiro de Oliveira"           , "RG134168"},
        {"Andre Luiz da Silva"                   , "SP030028"},
        {"Claudia Miyuki Werhmuller"             , "SP030041"},
        {"Claudete de Oliveira Alves"            , "SP03020X"},
        {"Francisco Verissimo Luciano"           , "SP030247"},
        {"Luk Cho Man"                           , "SP060380"},
        {"Ivan Francolin Martinez"               , "SP060835"},
        {"Joao Vianei Tamanini"                  , "SP060914"},
        {"Jose Oscar Machado Alexandre"          , "SP070038"},
        {"Jose Braz de Araujo"                   , "SP070385"},
        {"Paulo Roberto de Abreu"                , "SP070816"},
        {"Eurides Balbino da Silva"              , "SP07102X"},
        {"Domingos Bernardo Gomes Santos"        , "SP090888"},
        {"Andre Evandro Lourenco"                , "SP100092"},
        {"Miguel Angelo Tancredi Molina"         , "SP102763"},
        {"Antonio Airton Palladino"              , "SP112197"},
        {"Luis Fernando Aires Branco Menegueti"  , "SP145385"},
        {"Antonio Ferreira Viana"                , "SP200827"},
        {"Leonardo Bertholdo"                    , "SP204973"},
        {"Marcelo Tavares de Santana"            , "SP20500X"},
        {"Daniel Marques Gomes de Morais"        , "SP220097"},
        {"Alexandre Beletti Ferreira"            , "SP226117"},
        {"Vladimir Camelo Pinto"                 , "SP240291"},
        {"Leonardo Andrade Motta de Lima"        , "SP24031X"},
        {"Aldo Marcelo Paim"                     , "SP240497"},
        {"Cesar Lopes Fernandes"                 , "SP890534"},
        {"Josceli Maria Tenorio"                 , "SZ124382"}
    };
    
    /* Módulo "w" de criação do arquivo, neste caso fará a criação de um novo arquivo, mesmo que já tenha existencia um semelhante*/
    arquivo = fopen ("USUARIOS.DAT", "w");
    
    /* Caso o arquivo for igual um endereço NULL ele retornará ERRO e abortará o programa*/
    if (arquivo == NULL) {
        printf("\nERRO AO CRIAR USUARIOS.DAT");
        getch(); exit(EXIT_FAILURE);
    }
    
    /* Percorrerá os 29 cadastros default */
    for (i=0; i<29; i++) {
    fwrite ( &usuario[i] , sizeof(usuario[i]), 1, arquivo );
    }
    fclose (arquivo);
    printf("\n    USUARIOS.DAT criado com sucesso!"); getch();
}

// Função de quick_sort faz a ordenação de dados em forma crescente, onde ela particionará os dados de forma recursiva, os parâmetros
// que temos que passar para a função é um ponteiro do tipo de dado que vamos ordenar, o inicio do vetor, e o fim, que no caso seria
// o tamanho do vetor -1. 
void quick_sort (LOGIN *usuario, int inicio, int fim) {

    int pivo;
    
    /* Enquanto o início não for menor que o fim, irá fazer o particionamento dos dados onde temos que eleger um pivo */
    if (inicio < fim) {
        pivo = particiona(usuario,inicio,fim);
        
        /* O quick_sort fará a recursividade passando parâmetros do pivo decrescendo ou crescendo o valor original*/
        quick_sort(usuario, inicio, pivo-1);
        quick_sort(usuario, pivo+1, fim);
    }
}

// A função de particionamento, faz a comparação e a troca de dados entre os dados no caso como está sendo comparada strings
// é essêncial que use a função strcmp para a comparação de strings.
int particiona (LOGIN *usuario, int inicio, int pivo) {

    int maior, i;

    maior = inicio;
    for (i=inicio; i<pivo; i++) {
        if (strcmp(usuario[i].nome, usuario[pivo].nome) <0) {
        	// Função fará a troca do maior dado.
            troca_maior(usuario,i,maior);
            maior++;
        }
    }
    // Função fará a troca do pivo.
    troca_pivo(usuario,maior,pivo);
    return (maior);
}

// Função para trocar o antigo dado [maior] para o novo dado [maior].
void troca_maior (LOGIN *usuario, int i,int maior) {

    LOGIN aux;

    aux = usuario[i];
    usuario[i] = usuario[maior];
    usuario[maior] = aux;
}

// Função para a troca do pivo.
void troca_pivo (LOGIN* usuario, int maior, int pivo) {

    LOGIN aux;

    aux = usuario[maior];
    usuario[maior] = usuario[pivo];
    usuario[pivo] = aux;
}

// A função visualizarDAT, percorrerá o arquivo USUARIOS.DAT já criado e fará a leitura de todos os usuários registrados
// no caso fará a leitura até o "\0" NULL-TERMINATOR do arquivo DAT.
void visualizarDAT () {

    LOGIN     leitura;
    FILE     *arquivo;

    system("cls"); system("mode 96,36");
    
    /* Módulo "r" de leitura de arquivo*/
    arquivo = fopen ("USUARIOS.DAT" , "r");

    if ( arquivo == NULL) {
        printf("\nERRO AO LER USUARIOS.DAT!");
        getch(); exit(EXIT_FAILURE);
    }
    
    /* Vai ler até o NULL-TERMINATOR*/
    while ( !feof(arquivo)) {

        fread ( &leitura, sizeof(leitura), 1, arquivo );
        if ( !feof(arquivo)) {
            printf("[%-38s] [%-12s]\n", leitura.nome, leitura.prontuario);
        }
    }
    getch();
    fclose(arquivo);
}

// A função novoUsuarioDAT, irá registrar um novo usuário para o sistema, onde será incluído no arquivo USUARIOS.DAT
// fazendo a inclusão, o novo usuário poderá se logar no programa e utilizar, lembrando que apenas o usuário MASTER
// tem acesso a essas funcionalidades do DAT.
void novoUsuarioDAT () {

    LOGIN      novoUsuario;
    FILE      *arquivo;
    char       opc;
    
    // Fará a capitação dos dados do usuário, e permanecerá em looping até que o usuário não queira mais registrar
    // novos usuários.
    do {
    system("mode 68,8"); system("cls");
    printf("\nDIGITE NOME DO USUÁRIO          : "    ); fflush(stdin); gets(novoUsuario.nome);
    printf("\n\nDIGITE PRONTUÁRIO DO USUÁRIO    : "  ); fflush(stdin); gets(novoUsuario.prontuario);
    
    // O módulo "a" fará que o arquivo DAT guarde novos dados que serão inseridos no final do arquivo.
    arquivo = fopen ("USUARIOS.DAT" , "a");
    if (arquivo == NULL) {
        printf("\nERRO AO LOCALIZAR USUARIOS.DAT");
        getch(); exit(EXIT_FAILURE);
    }

    fwrite (&novoUsuario, sizeof(novoUsuario),1,arquivo);
    fclose(arquivo);

    printf("\nUsuário adicionado com sucesso!"); getch();
    printf("\nDeseja adicionar outro usuário? n[não]: "); fflush(stdin);
    opc = getche();
    }
    while ( opc != 'n' );
}

// A função buscaBinaria fará a busca da entrada que o usuário digitou no arquivo DAT, para isso acontecer primeiro precisa descobrir o tamanho do arquivo DAT
// em bytes, após isso precisamos saber o tamanho de cada registro LOGIN para calcular o tamanho de quantos registros tem no arquivo DAT.
void buscaBinaria (LOGIN loginUsuario) {

    // O DAT_usuarios é um ponteiro para LOGIN, com isso conseguimos realizar o quick_sort (ordenação de dados em forma crescente)
    // O tipo de dado long int, servirá para calcular o tamanho em bytes de um arquivo, pois um arquivo pode ter algumas dezenas de
    // bytes ou talvez milhões, por isso o long antes do int, do tipo (inteiro longo).
    FILE        *arquivo;
    LOGIN       *DAT_usuarios;
    long int     quantidade_bytes;
    int          TAMANHO, fim, inicio, meio;
    
    // A quantidade de bytes receberá o tamanho em bytes do arquivo DAT.
    // O tamanho de registros do arquivo DAT será o calculo da quantidade de
    // bytes dividido pelo tamanho do sizeof (tamanho) de um registro de login.
    // Com a malloc é alocado a quantidade de bytes para o preenchimento na
    // memória de cada registro dentro do arquivo DAT.
    quantidade_bytes = DAT_tamanho();
    TAMANHO          = quantidade_bytes / sizeof(LOGIN);
    DAT_usuarios     = (LOGIN*) malloc (quantidade_bytes);
    
    // Fará o abastecimento do conteúdo do DAT na memória da variável DAT_usuarios
    // e depois fará o quick_sort (ordenação de dados em forma crescente) do arquivo
    // passando parâmentros do arquivo, o inicio do arquivo que é 0, e o número de
    // registros que será o TAMANHO - 1.
    abasteceVetDAT (DAT_usuarios);
    quick_sort     (DAT_usuarios,0,TAMANHO-1);

    fim    = TAMANHO;
    inicio = 0;

    // Busca binária, comparando nomes, caso o nome de usuário e o prontuário seja
    // igual a algum dado percorrido pelo while, o usuário entrará nas funcionalidades
    // do sistema.
    while ( inicio <= fim) {
        meio = (inicio+fim)/2;
        if ( strcmp( DAT_usuarios[meio].nome , loginUsuario.nome) == 0 && strcmp( DAT_usuarios[meio].prontuario , loginUsuario.prontuario) == 0) {
            free        (DAT_usuarios); 
            menuUsuario (loginUsuario);
        }
        if (strcmp( DAT_usuarios[meio].nome , loginUsuario.nome) >0 ) {
            fim = meio-1;
        }
        else {
            inicio = meio+1;
        }
    }

    printf("\nUSUÁRIO E/OU PRONTUÁRIO INVÁLIDO!");
    free  (DAT_usuarios); 
    getch (); main();
}

// A função DAT_tamanho, calcula o tamanho do arquivo DAT
long int DAT_tamanho () {

    FILE        *arquivo;
    long int     resultado;
    
    /* Módulo r de leitura de um arquivo*/
    arquivo = fopen ("USUARIOS.DAT" , "r" );
    if ( arquivo == NULL) {
        printf("\nUSUARIOS.DAT não encontrado");
        getch(); exit(EXIT_FAILURE);
    }
    
    // A função fseek recebe parâmetro para saltar do começo do a arquivo até seu fim
    // e será retornado para a função que chamou, o tamanho do arquivo com o ftell.
    fseek (arquivo, 0L, SEEK_END);
    resultado = ftell(arquivo);
    return resultado;
}

// A função abasteceVetDAT, fará a cópia do arquivo DAT para a variável vetor que é do
// tipo LOGIN,
void abasteceVetDAT (LOGIN *vetor) {

    FILE  *arquivo;
    int    i=0;
    
    /* Módulo r de leitura de um arquivo */
    arquivo = fopen ("USUARIOS.DAT" , "r" );
    if ( arquivo == NULL) {
        printf("\nUSUARIOS.DAT não encontrado");
        getch(); exit(EXIT_FAILURE);
    }
    
    /* Percorrerá o DAT até o NULL-TERMINATOR */
    while ( !feof(arquivo)) {
    fread ( &vetor[i], sizeof(vetor[i]), 1, arquivo );
    if ( !feof(arquivo)) {
        i++;
    }
    }
    fclose(arquivo);
}

// Assim que o usuário conseguir se logar no sistema, entrará no menu gerenciador de supermercado, onde terá 4 opções de escolha
// caso o usuário aperte '0' a função irá sair do menu e voltará no menu de login. 
void menuUsuario (LOGIN loginUsuario) {
 
    char opc;
    
    // A opção de gerência de gôndolas fará que possa incluir, consultar e retirar produtos da gôndola 
    // O caixa_PDV fará a parte do caixa de um supermercado, assim que o usuáio retirar produtos da gôndola, ele poderá dirigir-se
    // ao caixa e assim ver o total da compra de seus produtos.
    // O gerenciar usuários, faz a parte de iniciar o arquivo DAT, ver usuários cadastrados e adicionar novos usuários, porém, apenas
    // o usuário MASTER poderá ter acesso a funcionalidade.
    do {
    system("cls"); system("mode 54,13"); system("color B0");
    printf("\n");
    printf("______________________________________________________");
    printf("\n\t SISTEMA GERENCIADOR DE SUPERMERCADO");
    printf("\n______________________________________________________");
    printf("\n\n\t\t1. Gerência de gôndolas");
    printf("\n\t\t2. Caixa/PDV");
    printf("\n\t\t3. Gerenciar usuários");
    printf("\n\t\t0. Sair");
    printf("\n\t\tOpção desejada: ");
    opc = getche();

    switch(opc) {
    	
        case '1' : menu_gondola (loginUsuario); break;
        case '2' : CAIXA_PDV    (&caixa);       break;
        case '0' : main         ();             break;
        
        // verUSUARIO_MASTER compara o login do usuário com o usuário MASTER, caso ele seja usuário MASTER a função
        // abrirá o menu, caso não seja, ele retornará para o usuário que não tem permissão para acessar a funcionalidade.
        case '3' : 
        if ( verUSUARIO_MASTER(loginUsuario) == TRUE) {
            gerenciaCadastro  (loginUsuario);
        }
        else {
            printf("\n  Usuário não tem permissão para acessar essa opção!");
            getch(); menuUsuario(loginUsuario); break;
        }
        default:
        system("cls"); printf("\n\n\n\n\n\n\t    ESCOLHA UMA OPÇÃO VÁLIDA!!!");
        getch(); menuUsuario(loginUsuario); 
    }
    }
    while (opc != '0');
}

// A função menu_gondola, servirá para o gerenciamento das gôndolas, ou seja, você poderá escolher entre abastecer gôndolas, ver gôndolas e retirar
// produto da gôndola.
void menu_gondola (LOGIN loginUsuario) {

    char opc;
    
    // É criada o vetor de char "escolha" para utilizar na função "qual_gondola" dependendo da escolha do usuário, o vetor receberá parâmetros de sua
    // escolha, por exemplo, ao escolher a opção de abastecer gôndolas o vetor receberá a string "abastecer", o mesmo com ver gôndolas que irá receber
    // a string "consultar" e a função retirar produto, que receberá o parâmetro "retirar produto", faz com que seja uma boa prática para codificação,
    // assim, construindo apenas uma função de gôndola que receberá a string "escolha" fazendo assim que não seja criadas mais duas novas funções semelhantes.
    char escolha[20];
    int i;
    
    // A pilha fará sua inicialização, onde será iniciado os 10 vetores da pilha, que cada uma representará uma gôndola.
    if ( indice_p1 != TRUE) {
    	for ( i=0; i<10; i++) {
        indice_p1 = iniciarPilha(&gondola[i]);
    }
    }

    do {
    system("cls"); system("mode 54,13"); system("color 8E");
    printf("\n");
    printf("______________________________________________________");
    printf("\n\t\t       GONDÔLAS");
    printf("\n______________________________________________________");
    printf("\n\n\t\t1. Abastecer gôndolas");
    printf("\n\t\t2. Ver gôndolas");
    printf("\n\t\t3. Retirar produto");
    printf("\n\t\t4. Ver carrinho");
    printf("\n\t\t0. Sair");
    printf("\n\t\tOpção desejada: ");
    opc = getche();

    switch (opc) {
    	
    	// Será chamada a função de qual_gondola, e nessa função ela ira receber o login do usuário, para parâmetros de funcionalidade
    	// pois apenas o usuário MASTER poderá incluir itens na gôndula, e apenas usuários comuns poderão retirar produtos da gôndola
    	// também será passado a string da escolha, além da variável tipo PILHA, gondola.
        case '1' :
        if ( verUSUARIO_MASTER(loginUsuario) == TRUE) { // Caso o usuário for MASTER a função consederá o acesso.
        	strcpy(escolha, "abastecer");
            qual_gondola(gondola,escolha,loginUsuario);           break;
        }
        
        else {
            printf("\n  Usuário não tem permissão para acessar essa opção!");
            getch(); menu_gondola(loginUsuario);      break;
        }
        
        case '2' : 
        	 strcpy(escolha,"consultar");
        	 qual_gondola(gondola,escolha,loginUsuario);          break;              

        case '3' : 
        if ( verUSUARIO_MASTER(loginUsuario) == FALSE) {  // Caso o usuário não for MASTER a função consederá acesso.
            strcpy(escolha,"retirar produto");
			qual_gondola(gondola,escolha,loginUsuario);           break;
        }
        else {
            printf("\n  Usuário não tem permissão para acessar essa opção!");
            getch();                                  break;
        }
        case '4' :   consulta_gondolas(&carrinho);    break;
        case '0' :   menuUsuario  (loginUsuario);     break;
        default  :
        system("cls"); printf("\n\n\n\n\n\n\t    ESCOLHA UMA OPÇÃO VÁLIDA!!!");
        getch(); 
    }
    }
    while ( opc != '0');
}


// A função verUSUARIO_MASTER, fará a comparação do login da entrada do usuário, para o usuário MASTER. 
bool verUSUARIO_MASTER (LOGIN loginUsuario) {
	
	// Definindo o vetor de char como MASTER, mesmo que a palavra MASTER tenha apenas 6 letras
	// temos que adicionar um elemento a mais para o NULL-TERMINATOR
    char    MASTER[7] = "MASTER";
    
    // Faz a comparação entre o que o usuário digitou com o MASTER, tanto para nome quanto para prontuário.
    if ( strcmp(loginUsuario.nome , MASTER) == 0 && strcmp(loginUsuario.prontuario , MASTER) == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// a Função consulta gondolas, exibi na tela todos os produtos das gôndolas
void consulta_gondolas (PILHA* gondola) {
	
	// o endereco é um tipo de variável do tipo PONTEIRO_p que é igual ao topo da gondola que foi passada para
	// a função, ela será auxiliar para percorrer toda as fatias da PILHA.
    PONTEIRO_p endereco = gondola->topo;  

    system("cls"); system("mode 62,32");
    
    // Enquanto o endereco for diferente de um endereço NULL ele imprimirá na tela todo os dados da pilha.
    while ( endereco != NULL) {
    printf("\nNOME:      [%s]    "  ,endereco->registro_p.nome      );
    printf("\nDESCRIÇÃO: [%s]    "  ,endereco->registro_p.descricao );
    printf("\nPESO:      [%iKG]  "  ,endereco->registro_p.peso      );
    printf("\nPREÇO:     [%.2fR$]"  ,endereco->registro_p.preco     );
    printf("\n");
    
    // Assim que finalizar a impressão na tela a variável endereco receberá o próximo endereço da pilha
    endereco = endereco->PROXIMO;
    }
    getch();
}

// A função retirar_produto, faz a retirada dos produtos na gondola, com ela precisa ser passádo um ponteiro da gondola, e do registro.
bool retirar_produto ( PILHA* gondola, REGISTRO_p* registro) {
	
	// Utilização da variável apagar do tipo PONTEIRO_p para auxiliar
	// no retiro do produto.
	PONTEIRO_p apagar;
	
	// Faz iniciar a estrutura de FILA, ela será ativada apenas uma vez
	// fazendo assim, não perder os dados.
	if ( indice_f != TRUE) {
    indice_f = iniciarFILA(&caixa);
    }
    
    // Faz a inicialização da pilha do carrinho de compras, segue a mesma
    // lógica do inicialização da pilha.
    if ( indice_p2 != TRUE ) {
	indice_p2 = iniciarPilha(&carrinho);
	}
	
	// Se não tiver produtos na gondola para retirar, a função irá retornar
	// FALSE para quem a chamou
	if ( gondola->topo == NULL) {
		return FALSE;
	}
	
	// Antes da fazer a retirada do produto, a função irá montar uma fila, pois
	// a partir de quando você retira um produto, automaticamente você está colocando
	// no carrinho, assim, o usuário irá passar no caixa para pagar sua mercadoria
	// sendo assim é necessário antes de apagar a mercadoria/ retirar da gôndola,
	// fazer uma cópia na estrutura de dados tipo fila, do produto que está sendo retirado.
	// A função recebe o conteudo da estrutura de dados FILA variável caixa, e o conteúdo
	// do topo da gôndola que será retirada.
	inserirNaFILA  (&caixa,gondola->topo->registro_p);
	
	// Em sequência, temos que criar uma nova pilha, para registrar o carrinho de compras
	// assim vou passar o conteúdo do carrinho e o registro do topo da gôndola, todos em PILHA
	PUSH_pilha     (&carrinho,gondola->topo->registro_p); 
	
	// Faz a exclusão do registro de forma que antes seja passado o ponteiro para o próximo nó da
	// PILHA, assim preservando toda a estrutura.
	*registro     = gondola->topo->registro_p;
	apagar        = gondola->topo;
	gondola->topo = apagar->PROXIMO;
	
	free(apagar);
	return TRUE;
}

// Faz a alocação de memória para um novo registro do tipo pilha, nela é essêncial passar
// parâmetros como o ponteiro para PILHA, e o registro de dados que gostaria de adicionar
// na estrutura de dados PILHA
bool PUSH_pilha ( PILHA* gondola, REGISTRO_p registro) {

    system("cls"); system("mode 62,32"); 
    
    // Criação de um novo ponteiro, para criar o novo nó da pilha
    PONTEIRO_p novo_pont;
    
    // Faz a alocação dinâmica do novo ponteiro.
    // Caso a malloc devolver NULL, não será criado o novo nó na pilha.
    novo_pont = (PONTEIRO_p) malloc (sizeof(ELEMENTO_p));
    if ( novo_pont == NULL) {
        printf("\nERRO AO ALOCAR MEMÓRIA!");
        printf("\nNÃO FOI POSSÍVEL INSERIR NA PILHA!");
        getch(); 
        return FALSE;
    }
    
    // Conjunto de instruções para passar para o novo_pont, os parâmetros do novo item,
    // após isso é definido o novo topo da pilha, assim fazendo que todo o nó de pilha
    // seja guardado de forma correta.
    novo_pont->registro_p = registro;
    novo_pont->PROXIMO = gondola->topo;
    gondola->topo = novo_pont;
    return TRUE;
}

// Inicia a estrutura de dados PILHA.
bool iniciarPilha (PILHA* gondola) {
        gondola->topo = NULL;
        return TRUE;
}

// Faz a inserção de dados.
REGISTRO_p inserir_produto () {
	
	// A variável auxiliar irá receber os dados que o usuário digitar.
    REGISTRO_p auxiliar;
    
    system("cls"); system("mode 62,25");

    printf("\nDigite o nome do produto:        "); fflush(stdin); gets (auxiliar.nome);
    printf("\nDigite uma descrição do produto: "); fflush(stdin); gets (auxiliar.descricao);
    printf("\nDigite o peso em KG do produto:  "); fflush(stdin); scanf( "%i", &auxiliar.peso);
    printf("\nDigite o preço do produto:       "); fflush(stdin); scanf( "%f", &auxiliar.preco);
    
    // Fará o retorno para quem a chamou, assim armazenando os dados
    // do tipo REGISTRO_p.
    return auxiliar;
}

// Faz o gerênciamento da inserção estrutura da PILHA
void inserePilha (PILHA * gondola) {
	
	// O registro recebe os dados que o usuário digitar
	REGISTRO_p registro;
	registro = inserir_produto();
	
	// Com o push, a função irá retornar TRUE ou FALSE, sendo que true é uma
	// inserção bem sucedida, e false, não é possível inserir novos dados.
	if ( PUSH_pilha (gondola,registro) == TRUE  ) {
	   system("mode 50,12");
	   printf ("\n\n\n\n\n\t%s inserido com sucesso!", registro.nome);
	   getch();
    }
	else {
	   system("mode 50,12");
	   printf ("\n\n\n\n\n\t%s NÃO inserido!", registro.nome );
	   getch();
    }
}

// Função para mostrar para o usuário que uma gôndola está vazia.
bool estaVazia (PILHA * gondola) {
	if ( gondola->topo == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// Faz o gerênciamento da exclusão da pilha, chamando a função de retirada da pilha, e por fim
// mostrando na tela qual item foi adicionado no carrinho.
void excluiPilha (PILHA* gondola) {
	
	system("cls"); system("mode 62,25");
	
	REGISTRO_p registro;
	if ( retirar_produto(gondola,&registro) == TRUE) {
		printf("\nADICIONADO NO CARRINHO!");
        printf("\nNOME:      [%s]    "  ,registro.nome      );
        printf("\nDESCRIÇÃO: [%s]    "  ,registro.descricao );
        printf("\nPESO:      [%iKG]  "  ,registro.peso      );
        printf("\nPREÇO:     [%.2fR$]"  ,registro.preco     );
        printf("\n");
	}
	
	// Caso não haja produtos na gôndola a função retornará a mensagem na tela
	else {
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t");
		printf(" NÃO HÁ PRODUTO NA GÔNDOLA!");
		getch();
	}
	getch();
}

// Inicia a estrutura de dados do tipo FILA.
bool iniciarFILA ( FILA* caixa) {
	caixa->inicio = NULL;
	caixa->fim    = NULL;
	return TRUE;
}

// Faz a inserção do produto retirado para uma estrutura de dados do tipo FILA, nela será ordenada para 
// o caixa/PDV fazer o calculo do preço dos produtos do carrinho, a função precisa receber parâmetros de
// um ponteiro da estrutura do tipo FILA, e o registro do produto que está sendo retirado da gôndola
// e que será armazenado na fila para o caixa/PDV.
// notasse que a função receberá uma estrutura do tipo pilha, e fará a conversão de pilha para fila.
bool inserirNaFILA (FILA * caixa, REGISTRO_p registro) {
	
	// É definido a variável auxiliar do tipo REGISTRO_f, que fará o auxilio para inserção do produto na
	// fila, e também uma variável do tipo PONTEIRO_f chamada de novo, que receberá parâmetros como o
	// inicio, ou fim, dependendo de ocasião.
	REGISTRO_f auxiliar;
	PONTEIRO_f novo;
	
	// O ponteiro novo, é alocado dinâmicamente.
	novo = (PONTEIRO_f) malloc ( sizeof(ELEMENTO_f));
	
	if ( novo == NULL) {
		return FALSE;
	}
	
	// A variável auxiliar, receberá os parâmetros do registro.
	// um dado do tipo FILA irá receber o conteúdo da variável de registro do
	// tipo PILHA.
	strcpy(auxiliar.nome     , registro.nome     );
	strcpy(auxiliar.descricao, registro.descricao);
	auxiliar.peso  = registro.peso;
	auxiliar.preco = registro.preco;
	
	// A variável novo receberá os parâmetro do auxiliar.
	// E o próximo nó depois irá apontar para NULL.
	novo->registro_f = auxiliar;
	novo->PROXIMO_f  = NULL;
	
	// Se for o primeiro item na FILA ele receberá os parâmetros iniciais,
	// caso não seja o próximo nó será igual o fim.
	if ( caixa->inicio == NULL) {
		caixa->inicio = novo;
	}
	else {
		caixa->fim->PROXIMO_f = novo;
	}
	caixa->fim = novo;

	return TRUE;
}

// A função CAIXA_PDV, faz a retirada dos elementos que estão no carrinho, e somando o valor progressivamente
// na função é preciso passar um ponteiro para estrutura de dados do tipo FILA.
bool CAIXA_PDV (FILA* caixa) {
	
	// É criada uma variável do tipo REGISTRO_f para auxiliar a função
	// e outra variável do tipo PONTEIRO_p para apontar para o inicio e outra
	// para apagar da FILA, lém de uma variável float para calcular
	// o total da compra.
	int i;
	float total=0;
	REGISTRO_f auxiliar;
	PONTEIRO_f endereco;
	PONTEIRO_f apagar;
	
	system("cls"); system("mode 62,25"); system("color 18");
	
	// Endereco recebe o ponteiro do inicio da fila.
	endereco = caixa->inicio;
	
	// Faz o looping de, enquanto o endereco for diferente de NULL ele fará
	// a leitura dos dados e mostrará na tela.
	while ( endereco != NULL ) {
	
	// Quando chegar no fim	da fila mostrará na tela o TOTAL a pagar.
	if ( caixa->inicio == NULL) {
		printf("\nTOTAL A PAGAR: [%.2fR$]",total); getch();
		return FALSE;
	}
	
	// Auxiliar recebe o conteudo do registro do inicio.
	// O total é somado progressivamente.
	auxiliar = caixa->inicio->registro_f;
	total    = total + caixa->inicio->registro_f.preco;
	
	printf("\nNOME:      [%s]    "  ,caixa->inicio->registro_f.nome      );
    printf("\nDESCRIÇÃO: [%s]    "  ,caixa->inicio->registro_f.descricao );
    printf("\nPESO:      [%iKG]  "  ,caixa->inicio->registro_f.peso      );
    printf("\nPREÇO:     [%.2fR$]"  ,caixa->inicio->registro_f.preco     );
    printf("\nTOTAL:     [%.2fR$]"  ,total                               );
    printf("\n");
	
	// O ponteiro apagar é igual o inicio, sendo assim fazendo que apague de maneira
	// correta um nó da FILA, sem perder o vínculo entre os nós.
	apagar         = caixa->inicio;
	caixa->inicio  = caixa->inicio->PROXIMO_f;
	free(apagar);
	
	// Faz um beep de som, simulando uma máquina de leitura de código de barras.
	Beep(500,215);
	
	// Se o inicio for igual a NULL, o fim receberá NULL também.
	if ( caixa->inicio == NULL) {
		caixa->fim = NULL;
	}
	getch();
    }	
}

// A função qual_gondola, serve para escolher, qual gôndola você quer abastecer produto,
// ver produto, ou retirar produto, ela recebe parâmetros de um ponteiro para PILHA, a
// escolha que o usuário faz e o login do usuário para saber se ele tem autorização de
// retirar produto ou abastecer a gondola.
void qual_gondola (PILHA* gondola, char escolha[], LOGIN loginUsuario) {
	
	
	// Os vetores de char A, B, C serve para fazer comparação de qual foi a escolha que o 
	// usuário escolheu.
	char opc;
	char A[10] = {"abastecer"};
	char B[10] = {"consultar"};
	char C[20] = {"retirar produto"};
	
	do {
		system ("cls"); system ("mode 46,18"); system ("color 3A");
		printf("______________________________________________");
		printf("\n  Escolha gôndola que deseja %s",escolha);
		printf("\n______________________________________________");
		printf("\n\t\t0. Gôndola 0");
		printf("\n\t\t1. Gôndola 1");
		printf("\n\t\t2. Gôndola 2");
		printf("\n\t\t3. Gôndola 3");
		printf("\n\t\t4. Gôndola 4");
		printf("\n\t\t5. Gôndola 5");
		printf("\n\t\t6. Gôndola 6");
		printf("\n\t\t7. Gôndola 7");
		printf("\n\t\t8. Gôndola 8");
		printf("\n\t\t9. Gôndola 9");
		printf("\n\t\tF. SAIR");
		printf("\n______________________________________________");
		printf("\n\t\tESCOLHA: ");
		
		opc = getche(); getch();
		    
		    // Para cada if, será análisado a escolha que o usuário escolheu
		    // caso A, abrirá o menu de abastecer, caso B, abrirá a opção de 
		    // consulta e caso C, abrirá a opção de retirada.
			if (strcmp(escolha , A) == 0 ) {
				caso_abastecer(opc,loginUsuario); 
			}
			
			if (strcmp(escolha , B) == 0) {
				caso_consultar(opc,loginUsuario);
			}
			
			if (strcmp(escolha , C) == 0) {
				caso_retirar(opc,loginUsuario);
			}
		}
		while ( opc != 'f' || opc != 'F');	
}

// A função caso_abastecer, fará o abastecimento da gôndola de qual o usuário escolher.
void caso_abastecer (char opc, LOGIN loginUsuario) {
	
	
	// Para cada opção de 0 a 9, fará a inserção da gôndola referente ao número.
	// além disso, fará a comparação do número máximo de produtos que podem ser
	// alocadas na gôndola, como definido no começo do código, o máximo é 5.
	switch(opc) {
		case '0': 
		if (tamanho_pilha(&gondola[0]) < MAXIMO) {
		inserePilha(&gondola[0]);           break;
	    }
	    else gondola_cheia();               break;
		case '1':
		if (tamanho_pilha(&gondola[1]) < MAXIMO) {
		inserePilha(&gondola[1]);           break;
	    }
	    else gondola_cheia();               break;	
		case '2':
		if (tamanho_pilha(&gondola[2]) < MAXIMO) {
		inserePilha(&gondola[2]);           break;
	    }
	    else gondola_cheia();               break;	
		case '3':
		if (tamanho_pilha(&gondola[3]) < MAXIMO) {
		inserePilha(&gondola[3]);           break;
	    }
	    else gondola_cheia();               break;	
		case '4':
		if (tamanho_pilha(&gondola[4]) < MAXIMO) {
		inserePilha(&gondola[4]);           break;
	    }
	    else gondola_cheia();               break;
		case '5':
		if (tamanho_pilha(&gondola[5]) < MAXIMO) {
		inserePilha(&gondola[5]);           break;
	    }
	    else gondola_cheia();               break;
		case '6':
		if (tamanho_pilha(&gondola[6]) < MAXIMO) {
		inserePilha(&gondola[6]);           break;
	    }
	    else gondola_cheia();               break;	
		case '7':
		if (tamanho_pilha(&gondola[7]) < MAXIMO) {
		inserePilha(&gondola[7]);           break;
	    }
	    else gondola_cheia();               break;
		case '8':
		if (tamanho_pilha(&gondola[8]) < MAXIMO) {
		inserePilha(&gondola[8]);           break;
	    }
	    else gondola_cheia();               break;
		case '9':
		if (tamanho_pilha(&gondola[9]) < MAXIMO) {
		inserePilha(&gondola[9]);           break;
	    }
	    else gondola_cheia();               break;	
		case 'f': case 'F': menu_gondola(loginUsuario); break;
		default :
		printf("\nESCOLHA UMA OPÇÃO VÁLIDA!!!");
        getch(); 
	}
}

// A função caso_consultar, fará a consulta da gôndola de qual o usuário escolher.
void caso_consultar (char opc, LOGIN loginUsuario) {
	    
	    // Para cada opção de 0 a 9, fará a consulta da gôndola referente ao número.
        // caso a gôndola não estiver vazia poderá ver o conteúdo de cada gôndola.
		switch(opc) {
		case '0':
			if (estaVazia(&gondola[0]) == FALSE) {
		consulta_gondolas(&gondola[0]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '1':
			if (estaVazia(&gondola[1]) == FALSE) {
		consulta_gondolas(&gondola[1]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '2':
			if (estaVazia(&gondola[2]) == FALSE) {
		consulta_gondolas(&gondola[2]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '3':
			if (estaVazia(&gondola[3]) == FALSE) {
		consulta_gondolas(&gondola[3]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '4':
			if (estaVazia(&gondola[4]) == FALSE) {
		consulta_gondolas(&gondola[4]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '5':
			if (estaVazia(&gondola[5]) == FALSE) {
		consulta_gondolas(&gondola[5]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '6':
			if (estaVazia(&gondola[6]) == FALSE) {
		consulta_gondolas(&gondola[6]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '7':
			if (estaVazia(&gondola[7]) == FALSE) {
		consulta_gondolas(&gondola[7]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '8':
			if (estaVazia(&gondola[8]) == FALSE) {
		consulta_gondolas(&gondola[8]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case '9':
			if (estaVazia(&gondola[9]) == FALSE) {
		consulta_gondolas(&gondola[9]);                  break;
	    } 
	    else gondola_vazia();                            break;
		case 'f': case 'F': menu_gondola(loginUsuario);  break;
		default :
		printf("\nESCOLHA UMA OPÇÃO VÁLIDA!!!");
        getch();
    }
}

// A função caso_retirar, fará a retirada de produtos dá gôndola pela qual o usuário escolheu.
void caso_retirar (char opc, LOGIN loginUsuario) {
	    
	    // Para cada opção de 0 a 9, fará a retirada de produto da gôndola referente ao número
	    // que o usuário escolheu.
		switch(opc) {
		case '0': excluiPilha(&gondola[0]); break;
		case '1': excluiPilha(&gondola[1]); break;
		case '2': excluiPilha(&gondola[2]); break;
		case '3': excluiPilha(&gondola[3]); break;
		case '4': excluiPilha(&gondola[4]); break;
		case '5': excluiPilha(&gondola[5]); break;
		case '6': excluiPilha(&gondola[6]); break;
		case '7': excluiPilha(&gondola[7]); break;
		case '8': excluiPilha(&gondola[8]); break;
		case '9': excluiPilha(&gondola[9]); break;
		case 'f': case 'F': menu_gondola(loginUsuario); break;
		default :
		printf("\nESCOLHA UMA OPÇÃO VÁLIDA!!!");
        getch();
    }
}

// Mostra a mensagem na tela de gôndola vazia.
void gondola_vazia () {
	printf("\n\t\tGONDOLA VÁZIA!");
	getch();
}

// Fará a a contagem do tamanho da estrutura pilha.
int tamanho_pilha (PILHA* gondola) {
	
	int tamanho=0;
	
	// A variável do tipo endereco, aponta para o topo da pilha, e enquanto  
	// o ponteiro for diferente de NULL, irá acrescimar o tamanho.
	PONTEIRO_p endereco = gondola->topo;
	while ( endereco != NULL) {
		tamanho++;
		endereco = endereco->PROXIMO;
	}
	return tamanho;
}

// Mostra a mensagem na tela de gondola está cheia.
void gondola_cheia () {
	printf("\n\t    GÔNDOLA ESTÁ CHEIA!");
	getch();
}
