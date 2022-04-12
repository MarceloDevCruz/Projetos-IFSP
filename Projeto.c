// Aluno: Marcelo Ferreira Cruz;
// Prontu�rio: SP3068862;

// IFSP Campus S�o Paulo; Eurides Balbino EDDA2;
// Projeto da disciplina Estrutura de Dados, segundo semestre;

// Feito com Visual Studio Code e DEV-C++;
// 17/10/2021, In�cio do projeto.
// 12/12/2021, Fim do projeto.


/*--------------------Bibliotecas---------------------*/
   #include <stdio.h>
   #include <stdlib.h>
   #include <conio.h>
   #include <malloc.h>
   #include <locale.h>
   #include <string.h>
   #include <windows.h>
// A biblioteca windows � apenas necess�ria caso uso da IDE Visual Studio Code.
// por�m no DEV-C++ ela n�o � compilada... ???
/*----------------------------------------------------*/


/*---------------------Defines------------------------*/
#define TRUE       1 // defini��o de TRUE  para tipos booleanos.
#define FALSE     -1 // defini��o de FALSE para tipos booleanos.
#define MAXIMO     5 // definir o m�ximo de produtos que podem ter em uma mesma g�ndola.
// A qualquer momento do programa poder� usar a defini��o de m�ximo, para aumentar a
// capacidade das g�ndolas do supermercado
/*---------------------------------------------------*/


/*-------------------Typedefs------------------------*/
typedef int bool; // defini��o do tipo booleano "bool" para retornos de TRUE ou FALSE.
/*---------------------------------------------------*/


/*----------------------Login------------------------*/
/* Estrutura do registro e gest�o de usu�rios */
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


/*--------------------Prot�tipos de fun��es------------------------*/
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


/*---------------V�riaveis globais------------------*/
bool    indice_p1 = FALSE; // Esse �ndice serve para iniciar a estrutura de dados do tipo pilha.
bool    indice_p2 = FALSE; // Esse �ndice serve para iniciar a estrutura de dados do tipo pilha para o carrinho.
bool    indice_f  = FALSE; // Esse �ndice serve para iniciar a estrutura de dados do tipo fila.
PILHA   gondola[10];       // Uma vari�vel global do tipo PILHA que � um vetor, ser� ess�ncial para criar as 10 g�ndolas do requisito do projeto.
PILHA   carrinho;          // Vari�vel global, ela ser� respons�vel de, assim que o produto sair da gondula, fazer uma c�pia e armazenar no carrinho.
FILA    caixa;             // Vari�vel para utilizar na hora de passar os produtos do carrinho para o caixa/PDV.
/*--------------------------------------------------*/


/*--------------------Fun��es------------------------*/

// A fun��o main � necess�ria para o inicio do programa, nela se defini o idioma do programa que dever� seguir nesse caso o
// Portugu�s do Brasil, � necess�rio a biblioteca locale, logo em seguida � chamada a fun��o de login.
void main () {

    setlocale(LC_ALL, "Portuguese_Brazil");
    menuLOGIN();
}

// A fun��o menuLOGIN, recebe par�metros do usu�rio para fazer login no sistema, � usada a fun��o de busca binaria caso o usu�rio n�o tenha se logado
// como um usu�rio "MASTER", neste caso o usu�rio MASTER ter� acesso exclusivo de algumas funcionalidade do programa, como o ger�nciamento de
// usu�rios, e inclus�o de itens nas g�ndolas. 
void menuLOGIN () {

    LOGIN   login; 
    char    MASTER[7] = "MASTER"; // Esse vetor de char ser� ess�ncial para fazer a compara��o com o que o usu�rio digitou

    system("mode 68,8"); system("color 97");
    printf("\nNOME DO USU�RIO          : "    ); fflush(stdin); gets(login.nome);       // Pega informa��es do usu�rio, o nome dele
    printf("\n\nPRONTU�RIO DO USU�RIO    : "  ); fflush(stdin); gets(login.prontuario); // Pega informa��es do usu�rio, o prontu�rio dele

    if ( strcmp(login.nome, MASTER) == 0 && strcmp(login.prontuario, MASTER) == 0) {    // Compara o que o usu�rio digitou, com "MASTER" se for igual,
        menuUsuario (login);                                                            // ele abrir� o programa do menu do Supermercado.    
    }
    else {
        buscaBinaria(login); // Far� busca bin�ria com os par�metros que foram usados para tentar realizar o login
    }
}

// A fun��o gerenciaCadastro, � um Menu para ger�nciar o cadastro de usu�rios, tem a op��o de Reiniciar arquivo DAT, que serve para reiniciar ou criar
// um novo arquivo DAT com usu�rios default j� registrados no c�digo, a op��o de visualizad DAT, poder� ver todos os usu�rios j� cadastrados no sistema
// e o Cadastrar novos usu�rios, como o nome j� diz far� o cadastro de novos usu�rios no sistema.
void gerenciaCadastro (LOGIN loginUsuario) {

    char opc;
    
    /* O menu permanecer� em looping at� que seja digitado a tecla 0*/
    do {
    system("cls"); system("mode 44,13"); system("color 03");
    printf("\n");
    printf("____________________________________________"  );
    printf("\n\t GERENCIADOR DE USU�RIOS "                 );
    printf("\n____________________________________________");
    printf("\n\n\t1. Criar arquivo DAT "                   );
    printf("\n\t2. Visualizar arquivo DAT  "               );
    printf("\n\t3. Cadastrar novos usu�rios "              );
    printf("\n\t0. Sair  "                                 );
    printf("\n____________________________________________");
    printf("\n\tEscolha: "                                 );
    opc = getche(); getch();

    switch(opc) {
    	
    	// Iniciar� o arquivo DAT ou ir� restaurar para o original.
        case '1': arquivoDAT     ();             break;
        
        // Poder� visualizar o arquivo DAT, e ver todos os usu�rios registrados no arquivo.
        case '2': visualizarDAT  ();             break;
        
        // Registrar� um novo usu�rio.
        case '3': novoUsuarioDAT ();             break;
        
        // Retornar� para o menu do usu�rio.
        case '0': menuUsuario    (loginUsuario); break;
        default :        
        system("cls"); printf("\n\n\n\n\n\n\t    ESCOLHA UMA OP��O V�LIDA!!!");
        getch(); gerenciaCadastro(loginUsuario); 
    }
    }
    while ( opc != '0');
}

// A fun��o arquivoDAT, criar� ou reiniciar� arquivo USUARIOS.DAT com 29 registros default dos usu�rios do sistema
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
    
    /* M�dulo "w" de cria��o do arquivo, neste caso far� a cria��o de um novo arquivo, mesmo que j� tenha existencia um semelhante*/
    arquivo = fopen ("USUARIOS.DAT", "w");
    
    /* Caso o arquivo for igual um endere�o NULL ele retornar� ERRO e abortar� o programa*/
    if (arquivo == NULL) {
        printf("\nERRO AO CRIAR USUARIOS.DAT");
        getch(); exit(EXIT_FAILURE);
    }
    
    /* Percorrer� os 29 cadastros default */
    for (i=0; i<29; i++) {
    fwrite ( &usuario[i] , sizeof(usuario[i]), 1, arquivo );
    }
    fclose (arquivo);
    printf("\n    USUARIOS.DAT criado com sucesso!"); getch();
}

// Fun��o de quick_sort faz a ordena��o de dados em forma crescente, onde ela particionar� os dados de forma recursiva, os par�metros
// que temos que passar para a fun��o � um ponteiro do tipo de dado que vamos ordenar, o inicio do vetor, e o fim, que no caso seria
// o tamanho do vetor -1. 
void quick_sort (LOGIN *usuario, int inicio, int fim) {

    int pivo;
    
    /* Enquanto o in�cio n�o for menor que o fim, ir� fazer o particionamento dos dados onde temos que eleger um pivo */
    if (inicio < fim) {
        pivo = particiona(usuario,inicio,fim);
        
        /* O quick_sort far� a recursividade passando par�metros do pivo decrescendo ou crescendo o valor original*/
        quick_sort(usuario, inicio, pivo-1);
        quick_sort(usuario, pivo+1, fim);
    }
}

// A fun��o de particionamento, faz a compara��o e a troca de dados entre os dados no caso como est� sendo comparada strings
// � ess�ncial que use a fun��o strcmp para a compara��o de strings.
int particiona (LOGIN *usuario, int inicio, int pivo) {

    int maior, i;

    maior = inicio;
    for (i=inicio; i<pivo; i++) {
        if (strcmp(usuario[i].nome, usuario[pivo].nome) <0) {
        	// Fun��o far� a troca do maior dado.
            troca_maior(usuario,i,maior);
            maior++;
        }
    }
    // Fun��o far� a troca do pivo.
    troca_pivo(usuario,maior,pivo);
    return (maior);
}

// Fun��o para trocar o antigo dado [maior] para o novo dado [maior].
void troca_maior (LOGIN *usuario, int i,int maior) {

    LOGIN aux;

    aux = usuario[i];
    usuario[i] = usuario[maior];
    usuario[maior] = aux;
}

// Fun��o para a troca do pivo.
void troca_pivo (LOGIN* usuario, int maior, int pivo) {

    LOGIN aux;

    aux = usuario[maior];
    usuario[maior] = usuario[pivo];
    usuario[pivo] = aux;
}

// A fun��o visualizarDAT, percorrer� o arquivo USUARIOS.DAT j� criado e far� a leitura de todos os usu�rios registrados
// no caso far� a leitura at� o "\0" NULL-TERMINATOR do arquivo DAT.
void visualizarDAT () {

    LOGIN     leitura;
    FILE     *arquivo;

    system("cls"); system("mode 96,36");
    
    /* M�dulo "r" de leitura de arquivo*/
    arquivo = fopen ("USUARIOS.DAT" , "r");

    if ( arquivo == NULL) {
        printf("\nERRO AO LER USUARIOS.DAT!");
        getch(); exit(EXIT_FAILURE);
    }
    
    /* Vai ler at� o NULL-TERMINATOR*/
    while ( !feof(arquivo)) {

        fread ( &leitura, sizeof(leitura), 1, arquivo );
        if ( !feof(arquivo)) {
            printf("[%-38s] [%-12s]\n", leitura.nome, leitura.prontuario);
        }
    }
    getch();
    fclose(arquivo);
}

// A fun��o novoUsuarioDAT, ir� registrar um novo usu�rio para o sistema, onde ser� inclu�do no arquivo USUARIOS.DAT
// fazendo a inclus�o, o novo usu�rio poder� se logar no programa e utilizar, lembrando que apenas o usu�rio MASTER
// tem acesso a essas funcionalidades do DAT.
void novoUsuarioDAT () {

    LOGIN      novoUsuario;
    FILE      *arquivo;
    char       opc;
    
    // Far� a capita��o dos dados do usu�rio, e permanecer� em looping at� que o usu�rio n�o queira mais registrar
    // novos usu�rios.
    do {
    system("mode 68,8"); system("cls");
    printf("\nDIGITE NOME DO USU�RIO          : "    ); fflush(stdin); gets(novoUsuario.nome);
    printf("\n\nDIGITE PRONTU�RIO DO USU�RIO    : "  ); fflush(stdin); gets(novoUsuario.prontuario);
    
    // O m�dulo "a" far� que o arquivo DAT guarde novos dados que ser�o inseridos no final do arquivo.
    arquivo = fopen ("USUARIOS.DAT" , "a");
    if (arquivo == NULL) {
        printf("\nERRO AO LOCALIZAR USUARIOS.DAT");
        getch(); exit(EXIT_FAILURE);
    }

    fwrite (&novoUsuario, sizeof(novoUsuario),1,arquivo);
    fclose(arquivo);

    printf("\nUsu�rio adicionado com sucesso!"); getch();
    printf("\nDeseja adicionar outro usu�rio? n[n�o]: "); fflush(stdin);
    opc = getche();
    }
    while ( opc != 'n' );
}

// A fun��o buscaBinaria far� a busca da entrada que o usu�rio digitou no arquivo DAT, para isso acontecer primeiro precisa descobrir o tamanho do arquivo DAT
// em bytes, ap�s isso precisamos saber o tamanho de cada registro LOGIN para calcular o tamanho de quantos registros tem no arquivo DAT.
void buscaBinaria (LOGIN loginUsuario) {

    // O DAT_usuarios � um ponteiro para LOGIN, com isso conseguimos realizar o quick_sort (ordena��o de dados em forma crescente)
    // O tipo de dado long int, servir� para calcular o tamanho em bytes de um arquivo, pois um arquivo pode ter algumas dezenas de
    // bytes ou talvez milh�es, por isso o long antes do int, do tipo (inteiro longo).
    FILE        *arquivo;
    LOGIN       *DAT_usuarios;
    long int     quantidade_bytes;
    int          TAMANHO, fim, inicio, meio;
    
    // A quantidade de bytes receber� o tamanho em bytes do arquivo DAT.
    // O tamanho de registros do arquivo DAT ser� o calculo da quantidade de
    // bytes dividido pelo tamanho do sizeof (tamanho) de um registro de login.
    // Com a malloc � alocado a quantidade de bytes para o preenchimento na
    // mem�ria de cada registro dentro do arquivo DAT.
    quantidade_bytes = DAT_tamanho();
    TAMANHO          = quantidade_bytes / sizeof(LOGIN);
    DAT_usuarios     = (LOGIN*) malloc (quantidade_bytes);
    
    // Far� o abastecimento do conte�do do DAT na mem�ria da vari�vel DAT_usuarios
    // e depois far� o quick_sort (ordena��o de dados em forma crescente) do arquivo
    // passando par�mentros do arquivo, o inicio do arquivo que � 0, e o n�mero de
    // registros que ser� o TAMANHO - 1.
    abasteceVetDAT (DAT_usuarios);
    quick_sort     (DAT_usuarios,0,TAMANHO-1);

    fim    = TAMANHO;
    inicio = 0;

    // Busca bin�ria, comparando nomes, caso o nome de usu�rio e o prontu�rio seja
    // igual a algum dado percorrido pelo while, o usu�rio entrar� nas funcionalidades
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

    printf("\nUSU�RIO E/OU PRONTU�RIO INV�LIDO!");
    free  (DAT_usuarios); 
    getch (); main();
}

// A fun��o DAT_tamanho, calcula o tamanho do arquivo DAT
long int DAT_tamanho () {

    FILE        *arquivo;
    long int     resultado;
    
    /* M�dulo r de leitura de um arquivo*/
    arquivo = fopen ("USUARIOS.DAT" , "r" );
    if ( arquivo == NULL) {
        printf("\nUSUARIOS.DAT n�o encontrado");
        getch(); exit(EXIT_FAILURE);
    }
    
    // A fun��o fseek recebe par�metro para saltar do come�o do a arquivo at� seu fim
    // e ser� retornado para a fun��o que chamou, o tamanho do arquivo com o ftell.
    fseek (arquivo, 0L, SEEK_END);
    resultado = ftell(arquivo);
    return resultado;
}

// A fun��o abasteceVetDAT, far� a c�pia do arquivo DAT para a vari�vel vetor que � do
// tipo LOGIN,
void abasteceVetDAT (LOGIN *vetor) {

    FILE  *arquivo;
    int    i=0;
    
    /* M�dulo r de leitura de um arquivo */
    arquivo = fopen ("USUARIOS.DAT" , "r" );
    if ( arquivo == NULL) {
        printf("\nUSUARIOS.DAT n�o encontrado");
        getch(); exit(EXIT_FAILURE);
    }
    
    /* Percorrer� o DAT at� o NULL-TERMINATOR */
    while ( !feof(arquivo)) {
    fread ( &vetor[i], sizeof(vetor[i]), 1, arquivo );
    if ( !feof(arquivo)) {
        i++;
    }
    }
    fclose(arquivo);
}

// Assim que o usu�rio conseguir se logar no sistema, entrar� no menu gerenciador de supermercado, onde ter� 4 op��es de escolha
// caso o usu�rio aperte '0' a fun��o ir� sair do menu e voltar� no menu de login. 
void menuUsuario (LOGIN loginUsuario) {
 
    char opc;
    
    // A op��o de ger�ncia de g�ndolas far� que possa incluir, consultar e retirar produtos da g�ndola 
    // O caixa_PDV far� a parte do caixa de um supermercado, assim que o usu�io retirar produtos da g�ndola, ele poder� dirigir-se
    // ao caixa e assim ver o total da compra de seus produtos.
    // O gerenciar usu�rios, faz a parte de iniciar o arquivo DAT, ver usu�rios cadastrados e adicionar novos usu�rios, por�m, apenas
    // o usu�rio MASTER poder� ter acesso a funcionalidade.
    do {
    system("cls"); system("mode 54,13"); system("color B0");
    printf("\n");
    printf("______________________________________________________");
    printf("\n\t SISTEMA GERENCIADOR DE SUPERMERCADO");
    printf("\n______________________________________________________");
    printf("\n\n\t\t1. Ger�ncia de g�ndolas");
    printf("\n\t\t2. Caixa/PDV");
    printf("\n\t\t3. Gerenciar usu�rios");
    printf("\n\t\t0. Sair");
    printf("\n\t\tOp��o desejada: ");
    opc = getche();

    switch(opc) {
    	
        case '1' : menu_gondola (loginUsuario); break;
        case '2' : CAIXA_PDV    (&caixa);       break;
        case '0' : main         ();             break;
        
        // verUSUARIO_MASTER compara o login do usu�rio com o usu�rio MASTER, caso ele seja usu�rio MASTER a fun��o
        // abrir� o menu, caso n�o seja, ele retornar� para o usu�rio que n�o tem permiss�o para acessar a funcionalidade.
        case '3' : 
        if ( verUSUARIO_MASTER(loginUsuario) == TRUE) {
            gerenciaCadastro  (loginUsuario);
        }
        else {
            printf("\n  Usu�rio n�o tem permiss�o para acessar essa op��o!");
            getch(); menuUsuario(loginUsuario); break;
        }
        default:
        system("cls"); printf("\n\n\n\n\n\n\t    ESCOLHA UMA OP��O V�LIDA!!!");
        getch(); menuUsuario(loginUsuario); 
    }
    }
    while (opc != '0');
}

// A fun��o menu_gondola, servir� para o gerenciamento das g�ndolas, ou seja, voc� poder� escolher entre abastecer g�ndolas, ver g�ndolas e retirar
// produto da g�ndola.
void menu_gondola (LOGIN loginUsuario) {

    char opc;
    
    // � criada o vetor de char "escolha" para utilizar na fun��o "qual_gondola" dependendo da escolha do usu�rio, o vetor receber� par�metros de sua
    // escolha, por exemplo, ao escolher a op��o de abastecer g�ndolas o vetor receber� a string "abastecer", o mesmo com ver g�ndolas que ir� receber
    // a string "consultar" e a fun��o retirar produto, que receber� o par�metro "retirar produto", faz com que seja uma boa pr�tica para codifica��o,
    // assim, construindo apenas uma fun��o de g�ndola que receber� a string "escolha" fazendo assim que n�o seja criadas mais duas novas fun��es semelhantes.
    char escolha[20];
    int i;
    
    // A pilha far� sua inicializa��o, onde ser� iniciado os 10 vetores da pilha, que cada uma representar� uma g�ndola.
    if ( indice_p1 != TRUE) {
    	for ( i=0; i<10; i++) {
        indice_p1 = iniciarPilha(&gondola[i]);
    }
    }

    do {
    system("cls"); system("mode 54,13"); system("color 8E");
    printf("\n");
    printf("______________________________________________________");
    printf("\n\t\t       GOND�LAS");
    printf("\n______________________________________________________");
    printf("\n\n\t\t1. Abastecer g�ndolas");
    printf("\n\t\t2. Ver g�ndolas");
    printf("\n\t\t3. Retirar produto");
    printf("\n\t\t4. Ver carrinho");
    printf("\n\t\t0. Sair");
    printf("\n\t\tOp��o desejada: ");
    opc = getche();

    switch (opc) {
    	
    	// Ser� chamada a fun��o de qual_gondola, e nessa fun��o ela ira receber o login do usu�rio, para par�metros de funcionalidade
    	// pois apenas o usu�rio MASTER poder� incluir itens na g�ndula, e apenas usu�rios comuns poder�o retirar produtos da g�ndola
    	// tamb�m ser� passado a string da escolha, al�m da vari�vel tipo PILHA, gondola.
        case '1' :
        if ( verUSUARIO_MASTER(loginUsuario) == TRUE) { // Caso o usu�rio for MASTER a fun��o conseder� o acesso.
        	strcpy(escolha, "abastecer");
            qual_gondola(gondola,escolha,loginUsuario);           break;
        }
        
        else {
            printf("\n  Usu�rio n�o tem permiss�o para acessar essa op��o!");
            getch(); menu_gondola(loginUsuario);      break;
        }
        
        case '2' : 
        	 strcpy(escolha,"consultar");
        	 qual_gondola(gondola,escolha,loginUsuario);          break;              

        case '3' : 
        if ( verUSUARIO_MASTER(loginUsuario) == FALSE) {  // Caso o usu�rio n�o for MASTER a fun��o conseder� acesso.
            strcpy(escolha,"retirar produto");
			qual_gondola(gondola,escolha,loginUsuario);           break;
        }
        else {
            printf("\n  Usu�rio n�o tem permiss�o para acessar essa op��o!");
            getch();                                  break;
        }
        case '4' :   consulta_gondolas(&carrinho);    break;
        case '0' :   menuUsuario  (loginUsuario);     break;
        default  :
        system("cls"); printf("\n\n\n\n\n\n\t    ESCOLHA UMA OP��O V�LIDA!!!");
        getch(); 
    }
    }
    while ( opc != '0');
}


// A fun��o verUSUARIO_MASTER, far� a compara��o do login da entrada do usu�rio, para o usu�rio MASTER. 
bool verUSUARIO_MASTER (LOGIN loginUsuario) {
	
	// Definindo o vetor de char como MASTER, mesmo que a palavra MASTER tenha apenas 6 letras
	// temos que adicionar um elemento a mais para o NULL-TERMINATOR
    char    MASTER[7] = "MASTER";
    
    // Faz a compara��o entre o que o usu�rio digitou com o MASTER, tanto para nome quanto para prontu�rio.
    if ( strcmp(loginUsuario.nome , MASTER) == 0 && strcmp(loginUsuario.prontuario , MASTER) == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// a Fun��o consulta gondolas, exibi na tela todos os produtos das g�ndolas
void consulta_gondolas (PILHA* gondola) {
	
	// o endereco � um tipo de vari�vel do tipo PONTEIRO_p que � igual ao topo da gondola que foi passada para
	// a fun��o, ela ser� auxiliar para percorrer toda as fatias da PILHA.
    PONTEIRO_p endereco = gondola->topo;  

    system("cls"); system("mode 62,32");
    
    // Enquanto o endereco for diferente de um endere�o NULL ele imprimir� na tela todo os dados da pilha.
    while ( endereco != NULL) {
    printf("\nNOME:      [%s]    "  ,endereco->registro_p.nome      );
    printf("\nDESCRI��O: [%s]    "  ,endereco->registro_p.descricao );
    printf("\nPESO:      [%iKG]  "  ,endereco->registro_p.peso      );
    printf("\nPRE�O:     [%.2fR$]"  ,endereco->registro_p.preco     );
    printf("\n");
    
    // Assim que finalizar a impress�o na tela a vari�vel endereco receber� o pr�ximo endere�o da pilha
    endereco = endereco->PROXIMO;
    }
    getch();
}

// A fun��o retirar_produto, faz a retirada dos produtos na gondola, com ela precisa ser pass�do um ponteiro da gondola, e do registro.
bool retirar_produto ( PILHA* gondola, REGISTRO_p* registro) {
	
	// Utiliza��o da vari�vel apagar do tipo PONTEIRO_p para auxiliar
	// no retiro do produto.
	PONTEIRO_p apagar;
	
	// Faz iniciar a estrutura de FILA, ela ser� ativada apenas uma vez
	// fazendo assim, n�o perder os dados.
	if ( indice_f != TRUE) {
    indice_f = iniciarFILA(&caixa);
    }
    
    // Faz a inicializa��o da pilha do carrinho de compras, segue a mesma
    // l�gica do inicializa��o da pilha.
    if ( indice_p2 != TRUE ) {
	indice_p2 = iniciarPilha(&carrinho);
	}
	
	// Se n�o tiver produtos na gondola para retirar, a fun��o ir� retornar
	// FALSE para quem a chamou
	if ( gondola->topo == NULL) {
		return FALSE;
	}
	
	// Antes da fazer a retirada do produto, a fun��o ir� montar uma fila, pois
	// a partir de quando voc� retira um produto, automaticamente voc� est� colocando
	// no carrinho, assim, o usu�rio ir� passar no caixa para pagar sua mercadoria
	// sendo assim � necess�rio antes de apagar a mercadoria/ retirar da g�ndola,
	// fazer uma c�pia na estrutura de dados tipo fila, do produto que est� sendo retirado.
	// A fun��o recebe o conteudo da estrutura de dados FILA vari�vel caixa, e o conte�do
	// do topo da g�ndola que ser� retirada.
	inserirNaFILA  (&caixa,gondola->topo->registro_p);
	
	// Em sequ�ncia, temos que criar uma nova pilha, para registrar o carrinho de compras
	// assim vou passar o conte�do do carrinho e o registro do topo da g�ndola, todos em PILHA
	PUSH_pilha     (&carrinho,gondola->topo->registro_p); 
	
	// Faz a exclus�o do registro de forma que antes seja passado o ponteiro para o pr�ximo n� da
	// PILHA, assim preservando toda a estrutura.
	*registro     = gondola->topo->registro_p;
	apagar        = gondola->topo;
	gondola->topo = apagar->PROXIMO;
	
	free(apagar);
	return TRUE;
}

// Faz a aloca��o de mem�ria para um novo registro do tipo pilha, nela � ess�ncial passar
// par�metros como o ponteiro para PILHA, e o registro de dados que gostaria de adicionar
// na estrutura de dados PILHA
bool PUSH_pilha ( PILHA* gondola, REGISTRO_p registro) {

    system("cls"); system("mode 62,32"); 
    
    // Cria��o de um novo ponteiro, para criar o novo n� da pilha
    PONTEIRO_p novo_pont;
    
    // Faz a aloca��o din�mica do novo ponteiro.
    // Caso a malloc devolver NULL, n�o ser� criado o novo n� na pilha.
    novo_pont = (PONTEIRO_p) malloc (sizeof(ELEMENTO_p));
    if ( novo_pont == NULL) {
        printf("\nERRO AO ALOCAR MEM�RIA!");
        printf("\nN�O FOI POSS�VEL INSERIR NA PILHA!");
        getch(); 
        return FALSE;
    }
    
    // Conjunto de instru��es para passar para o novo_pont, os par�metros do novo item,
    // ap�s isso � definido o novo topo da pilha, assim fazendo que todo o n� de pilha
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

// Faz a inser��o de dados.
REGISTRO_p inserir_produto () {
	
	// A vari�vel auxiliar ir� receber os dados que o usu�rio digitar.
    REGISTRO_p auxiliar;
    
    system("cls"); system("mode 62,25");

    printf("\nDigite o nome do produto:        "); fflush(stdin); gets (auxiliar.nome);
    printf("\nDigite uma descri��o do produto: "); fflush(stdin); gets (auxiliar.descricao);
    printf("\nDigite o peso em KG do produto:  "); fflush(stdin); scanf( "%i", &auxiliar.peso);
    printf("\nDigite o pre�o do produto:       "); fflush(stdin); scanf( "%f", &auxiliar.preco);
    
    // Far� o retorno para quem a chamou, assim armazenando os dados
    // do tipo REGISTRO_p.
    return auxiliar;
}

// Faz o ger�nciamento da inser��o estrutura da PILHA
void inserePilha (PILHA * gondola) {
	
	// O registro recebe os dados que o usu�rio digitar
	REGISTRO_p registro;
	registro = inserir_produto();
	
	// Com o push, a fun��o ir� retornar TRUE ou FALSE, sendo que true � uma
	// inser��o bem sucedida, e false, n�o � poss�vel inserir novos dados.
	if ( PUSH_pilha (gondola,registro) == TRUE  ) {
	   system("mode 50,12");
	   printf ("\n\n\n\n\n\t%s inserido com sucesso!", registro.nome);
	   getch();
    }
	else {
	   system("mode 50,12");
	   printf ("\n\n\n\n\n\t%s N�O inserido!", registro.nome );
	   getch();
    }
}

// Fun��o para mostrar para o usu�rio que uma g�ndola est� vazia.
bool estaVazia (PILHA * gondola) {
	if ( gondola->topo == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// Faz o ger�nciamento da exclus�o da pilha, chamando a fun��o de retirada da pilha, e por fim
// mostrando na tela qual item foi adicionado no carrinho.
void excluiPilha (PILHA* gondola) {
	
	system("cls"); system("mode 62,25");
	
	REGISTRO_p registro;
	if ( retirar_produto(gondola,&registro) == TRUE) {
		printf("\nADICIONADO NO CARRINHO!");
        printf("\nNOME:      [%s]    "  ,registro.nome      );
        printf("\nDESCRI��O: [%s]    "  ,registro.descricao );
        printf("\nPESO:      [%iKG]  "  ,registro.peso      );
        printf("\nPRE�O:     [%.2fR$]"  ,registro.preco     );
        printf("\n");
	}
	
	// Caso n�o haja produtos na g�ndola a fun��o retornar� a mensagem na tela
	else {
		printf("\n\n\n\n\n\n\n\n\n");
		printf("\t\t");
		printf(" N�O H� PRODUTO NA G�NDOLA!");
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

// Faz a inser��o do produto retirado para uma estrutura de dados do tipo FILA, nela ser� ordenada para 
// o caixa/PDV fazer o calculo do pre�o dos produtos do carrinho, a fun��o precisa receber par�metros de
// um ponteiro da estrutura do tipo FILA, e o registro do produto que est� sendo retirado da g�ndola
// e que ser� armazenado na fila para o caixa/PDV.
// notasse que a fun��o receber� uma estrutura do tipo pilha, e far� a convers�o de pilha para fila.
bool inserirNaFILA (FILA * caixa, REGISTRO_p registro) {
	
	// � definido a vari�vel auxiliar do tipo REGISTRO_f, que far� o auxilio para inser��o do produto na
	// fila, e tamb�m uma vari�vel do tipo PONTEIRO_f chamada de novo, que receber� par�metros como o
	// inicio, ou fim, dependendo de ocasi�o.
	REGISTRO_f auxiliar;
	PONTEIRO_f novo;
	
	// O ponteiro novo, � alocado din�micamente.
	novo = (PONTEIRO_f) malloc ( sizeof(ELEMENTO_f));
	
	if ( novo == NULL) {
		return FALSE;
	}
	
	// A vari�vel auxiliar, receber� os par�metros do registro.
	// um dado do tipo FILA ir� receber o conte�do da vari�vel de registro do
	// tipo PILHA.
	strcpy(auxiliar.nome     , registro.nome     );
	strcpy(auxiliar.descricao, registro.descricao);
	auxiliar.peso  = registro.peso;
	auxiliar.preco = registro.preco;
	
	// A vari�vel novo receber� os par�metro do auxiliar.
	// E o pr�ximo n� depois ir� apontar para NULL.
	novo->registro_f = auxiliar;
	novo->PROXIMO_f  = NULL;
	
	// Se for o primeiro item na FILA ele receber� os par�metros iniciais,
	// caso n�o seja o pr�ximo n� ser� igual o fim.
	if ( caixa->inicio == NULL) {
		caixa->inicio = novo;
	}
	else {
		caixa->fim->PROXIMO_f = novo;
	}
	caixa->fim = novo;

	return TRUE;
}

// A fun��o CAIXA_PDV, faz a retirada dos elementos que est�o no carrinho, e somando o valor progressivamente
// na fun��o � preciso passar um ponteiro para estrutura de dados do tipo FILA.
bool CAIXA_PDV (FILA* caixa) {
	
	// � criada uma vari�vel do tipo REGISTRO_f para auxiliar a fun��o
	// e outra vari�vel do tipo PONTEIRO_p para apontar para o inicio e outra
	// para apagar da FILA, l�m de uma vari�vel float para calcular
	// o total da compra.
	int i;
	float total=0;
	REGISTRO_f auxiliar;
	PONTEIRO_f endereco;
	PONTEIRO_f apagar;
	
	system("cls"); system("mode 62,25"); system("color 18");
	
	// Endereco recebe o ponteiro do inicio da fila.
	endereco = caixa->inicio;
	
	// Faz o looping de, enquanto o endereco for diferente de NULL ele far�
	// a leitura dos dados e mostrar� na tela.
	while ( endereco != NULL ) {
	
	// Quando chegar no fim	da fila mostrar� na tela o TOTAL a pagar.
	if ( caixa->inicio == NULL) {
		printf("\nTOTAL A PAGAR: [%.2fR$]",total); getch();
		return FALSE;
	}
	
	// Auxiliar recebe o conteudo do registro do inicio.
	// O total � somado progressivamente.
	auxiliar = caixa->inicio->registro_f;
	total    = total + caixa->inicio->registro_f.preco;
	
	printf("\nNOME:      [%s]    "  ,caixa->inicio->registro_f.nome      );
    printf("\nDESCRI��O: [%s]    "  ,caixa->inicio->registro_f.descricao );
    printf("\nPESO:      [%iKG]  "  ,caixa->inicio->registro_f.peso      );
    printf("\nPRE�O:     [%.2fR$]"  ,caixa->inicio->registro_f.preco     );
    printf("\nTOTAL:     [%.2fR$]"  ,total                               );
    printf("\n");
	
	// O ponteiro apagar � igual o inicio, sendo assim fazendo que apague de maneira
	// correta um n� da FILA, sem perder o v�nculo entre os n�s.
	apagar         = caixa->inicio;
	caixa->inicio  = caixa->inicio->PROXIMO_f;
	free(apagar);
	
	// Faz um beep de som, simulando uma m�quina de leitura de c�digo de barras.
	Beep(500,215);
	
	// Se o inicio for igual a NULL, o fim receber� NULL tamb�m.
	if ( caixa->inicio == NULL) {
		caixa->fim = NULL;
	}
	getch();
    }	
}

// A fun��o qual_gondola, serve para escolher, qual g�ndola voc� quer abastecer produto,
// ver produto, ou retirar produto, ela recebe par�metros de um ponteiro para PILHA, a
// escolha que o usu�rio faz e o login do usu�rio para saber se ele tem autoriza��o de
// retirar produto ou abastecer a gondola.
void qual_gondola (PILHA* gondola, char escolha[], LOGIN loginUsuario) {
	
	
	// Os vetores de char A, B, C serve para fazer compara��o de qual foi a escolha que o 
	// usu�rio escolheu.
	char opc;
	char A[10] = {"abastecer"};
	char B[10] = {"consultar"};
	char C[20] = {"retirar produto"};
	
	do {
		system ("cls"); system ("mode 46,18"); system ("color 3A");
		printf("______________________________________________");
		printf("\n  Escolha g�ndola que deseja %s",escolha);
		printf("\n______________________________________________");
		printf("\n\t\t0. G�ndola 0");
		printf("\n\t\t1. G�ndola 1");
		printf("\n\t\t2. G�ndola 2");
		printf("\n\t\t3. G�ndola 3");
		printf("\n\t\t4. G�ndola 4");
		printf("\n\t\t5. G�ndola 5");
		printf("\n\t\t6. G�ndola 6");
		printf("\n\t\t7. G�ndola 7");
		printf("\n\t\t8. G�ndola 8");
		printf("\n\t\t9. G�ndola 9");
		printf("\n\t\tF. SAIR");
		printf("\n______________________________________________");
		printf("\n\t\tESCOLHA: ");
		
		opc = getche(); getch();
		    
		    // Para cada if, ser� an�lisado a escolha que o usu�rio escolheu
		    // caso A, abrir� o menu de abastecer, caso B, abrir� a op��o de 
		    // consulta e caso C, abrir� a op��o de retirada.
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

// A fun��o caso_abastecer, far� o abastecimento da g�ndola de qual o usu�rio escolher.
void caso_abastecer (char opc, LOGIN loginUsuario) {
	
	
	// Para cada op��o de 0 a 9, far� a inser��o da g�ndola referente ao n�mero.
	// al�m disso, far� a compara��o do n�mero m�ximo de produtos que podem ser
	// alocadas na g�ndola, como definido no come�o do c�digo, o m�ximo � 5.
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
		printf("\nESCOLHA UMA OP��O V�LIDA!!!");
        getch(); 
	}
}

// A fun��o caso_consultar, far� a consulta da g�ndola de qual o usu�rio escolher.
void caso_consultar (char opc, LOGIN loginUsuario) {
	    
	    // Para cada op��o de 0 a 9, far� a consulta da g�ndola referente ao n�mero.
        // caso a g�ndola n�o estiver vazia poder� ver o conte�do de cada g�ndola.
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
		printf("\nESCOLHA UMA OP��O V�LIDA!!!");
        getch();
    }
}

// A fun��o caso_retirar, far� a retirada de produtos d� g�ndola pela qual o usu�rio escolheu.
void caso_retirar (char opc, LOGIN loginUsuario) {
	    
	    // Para cada op��o de 0 a 9, far� a retirada de produto da g�ndola referente ao n�mero
	    // que o usu�rio escolheu.
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
		printf("\nESCOLHA UMA OP��O V�LIDA!!!");
        getch();
    }
}

// Mostra a mensagem na tela de g�ndola vazia.
void gondola_vazia () {
	printf("\n\t\tGONDOLA V�ZIA!");
	getch();
}

// Far� a a contagem do tamanho da estrutura pilha.
int tamanho_pilha (PILHA* gondola) {
	
	int tamanho=0;
	
	// A vari�vel do tipo endereco, aponta para o topo da pilha, e enquanto  
	// o ponteiro for diferente de NULL, ir� acrescimar o tamanho.
	PONTEIRO_p endereco = gondola->topo;
	while ( endereco != NULL) {
		tamanho++;
		endereco = endereco->PROXIMO;
	}
	return tamanho;
}

// Mostra a mensagem na tela de gondola est� cheia.
void gondola_cheia () {
	printf("\n\t    G�NDOLA EST� CHEIA!");
	getch();
}
