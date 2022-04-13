// TRABALHO DA MATÉRIA LG1A1
//Professora: Eurides Balbino

//Autor: Marcelo Ferreira Cruz
//Prontuário: SP3068862
// IFSP campus São Paulo

//Bibliotecas
#include <stdio.h>                 //Biblioteca padrão para usar várias funcionalidades do C
#include <stdlib.h>                //Biblioteca para usar os comandos system e o fflush
#include <conio.h>                 //Biblioteca para usar a função getch e getche
#include <locale.h>                //Biblioteca para respeitar a acentuação gráfica da língua portuguesa
#include <string.h>                //Biblioteca para usar funções para strings
#include "biblioteca_trabLG1A1.h"  //Biblioteca criada pelo programador para definir estruturas heterogêneas do programa

//Variáveis globais	
log login;                         //variável do tipo log para fazer o login do usuário
cadastro reg[5];                   //variável vetor do tipo cadastros
cadastro aux;                      //variável do tipo cadastro para auxilio
int i;                             //indice para percorrer os vetores com o for

//Ponteiros apontando para FILE
FILE * arq0;               
FILE * arq1;
FILE * arq2;
FILE * arq3;
FILE * auxiliar;

//Protótipos de funções
int main ();
void Login (void);
void MASTER (void);
void Cadastrar (void);
void Visualizar (void);
void RealizaTeste (void);
void SobreOTeste (void);
void Pergunta1 (void);
void Pergunta2 (void);
void Pergunta3 (void);
void Pergunta4 (void);
void Pergunta5 (void);
void RESULTADO (void);

//Corpo do programa main
int main ()
{
	setlocale(LC_ALL,"Portuguese_Brazil");   //Mudar idioma para o português brasileiro
	Login();                                 //Chamar a função Login
	return(0);                               //Devolve "0" um número inteiro para a função Main
}

//Corpo do programa Login
void Login (void)
{ 
    system("mode  50,8");        //Redimensiona a tela do prompt
    char M[7] = "MASTER";        //Cria uma variável local do tipo char vetor de string, onde nomeio de "MASTER"
    
    //Pedir para o usuário digitar o nome
	printf ("\n\nDIGITE SEU NOME       : "); fflush(stdin); //Limpa buffer do teclado
	gets(login.nome); //Captura o que o usuário digitou
	
	//Pedir para o usuário digitar o prontuário
	printf ("\n\nDIGITE SEU PRONTUÁRIO : "); fflush(stdin); //Limpa buffer do teclado
	gets(login.prontuario); //Captura o que o usuário digitou
	
	//Testa o que o usuário digitou no nome é igual o MASTER
	if (strcmp(login.nome,M) == 0)
	{
		MASTER();   //Se for ele prosseguirá para a função MASTER
	}
	RealizaTeste(); //Se não ele prosseguirá para a função RealizaTeste
}

//Corpo do programa MASTER
void MASTER (void)
{
	system("mode 66,11");   //Redimensiona a tela
	char opc;               //Variável local ao MASTER, que servirá para pegar a opção que usuário digitar
	
	//Menu de opções ele se manterá em looping até a OPC que for escolhida ser f ou F
	do
	{
		system("cls"); //Limpar tela
	    printf("=================================================");
	    printf("\n       TESTE DOS SISTEMAS REPRESENTACIONAIS");
	    printf("\n=================================================");
	    printf("\n      1. Cadastrar questionário");
	    printf("\n      2. Visualizar questionário");
        printf("\n      3. Realizar teste");
	    printf("\n      4. Sobre o teste");
	    printf("\n      F. Fim");
     	printf("\n=================================================");
    	printf("\n      Escolha -> ");
    	opc = getche(); //opção receberá o que o usuário digitar
    	switch (opc)
    	{
    		//Caso o usuário digitar 1 ela chamará a função Cadastrar
        	case '1' : Cadastrar(); break;  
        	
			//Caso o usuário digitar 2 chamará a função Visualizar
	        case '2' : Visualizar(); break; 
			 
			//Caso o usuário digitar 3 chamará a função RealizaTeste
	        case '3' : RealizaTeste(); break; 
			    
			//Caso o usuário digitar 4 chamará a função SobreOTeste           
	        case '4' : SobreOTeste(); break;  
			       
			//Caso o usuário digitar f ou F o programa vai finalizar        
	        case 'F' : case 'f': exit(0); break;  
			      
			//Caso digitar qualquer coisa diferente dessas opções mostrará uma mensagem de erro    
        	default : system("cls"); system("mode 35,4");
			printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
        }
    }
    while (opc =! 'F' || 'f');
} 

//Corpo do programa Cadastra
void Cadastrar (void)
{
	//Preenchimento do vetor reg para cada informação da pergunta, na ordem:
	//Número da frase, frase, item1, item2, item3, item4
	reg[0].NroFrase = 1;
	strcpy (reg[0].frase , "Eu tomo decisões importantes baseado em:");
	strcpy (reg[0].item_1 , "intuição.");
	strcpy (reg[0].item_2 , "o que me soa melhor.");
	strcpy (reg[0].item_3 , "o que me parece melhor.");
	strcpy (reg[0].item_4 , "um estudo preciso e minucioso do assunto.");
	
	reg[1].NroFrase = 2;
	strcpy (reg[1].frase , "Durante uma discussão eu sou mais influenciado por:");
	strcpy (reg[1].item_1 , "se eu entro em contato ou não com os sentimentos reais do outro.");
	strcpy (reg[1].item_2 , "o tom da voz da outra pessoa.");
	strcpy (reg[1].item_3 , "se eu posso ou não ver o argumento da outra pessoa.");
	strcpy (reg[1].item_4 , "a lógica do argumento da outra pessoa.");
	
	reg[2].NroFrase = 3;
	strcpy (reg[2].frase , "Eu comunico mais facilmente o que se passa comigo:");
	strcpy (reg[2].item_1 , "pelos sentimentos que compartilho.");
	strcpy (reg[2].item_2 , "pelo tom da minha voz.");
	strcpy (reg[2].item_3 , "do modo como me visto e aparento.");
	strcpy (reg[2].item_4 , "pelas palavras que escolho.");
	
	reg[3].NroFrase = 4;
	strcpy (reg[3].frase , "É muito fácil para min:");
	strcpy (reg[3].item_1 , "escolher os móveis mais confortáveis.");
	strcpy (reg[3].item_2 , "achar o volume e a sintonia ideais num sistema de som.");
	strcpy (reg[3].item_3 , "escolher as combinações de cores mais ricas e atraentes.");
	strcpy (reg[3].item_4 , "selecionar o ponto mais relevante relativo a um assunto interessante.");
	
	reg[4].NroFrase = 5;
	strcpy (reg[4].frase , "Eu me percebo assim:");
	strcpy (reg[4].item_1 , "eu sou muito sensível à maneira como a roupa veste o meu corpo.");
	strcpy (reg[4].item_2 , "se estou muito em sintonia com os sons dos ambientes.");
	strcpy (reg[4].item_3 , "eu respondo fortemente às cores e à aparência de uma sala.");
	strcpy (reg[4].item_4 , "se sou muito capaz de raciocinar com fatos e dados novos.");
	
	//Criação do arquivo DAT
	//Abre o arquivo
	arq2 = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT" , "w");
	if (arq2 == NULL)
	{
		printf("\nERRO AO CADASTRAR O TESTE_SISTEMA_REPRESENTACIONAL.DAT!");
		getch(); exit(0);
	}
	
	//Gravação das informações para o arquivo DAT
	for (i=0; i<5; i++)
	{
		fwrite (&reg[i] , sizeof(reg[i]),1,arq2);
		if(ferror(arq2))
		{
			printf("\nERRO AO GRAVAR O REGISTRO [%i]",i);
			getch(); break;
		}
	}
	
	//Fecha o arquivo
	fclose (arq2);
	//Mostra na tela a mensagem que o arquivo DAT foi Cadastrada
	printf("\nCadastro do TESTE_SISTEMA_REPRESENTACIONAL.DAT concluída.");
	getch();
}

//Corpo do programa Visualizar
void Visualizar (void)
{
	//Abrir o arquivo de texto QUESTIONÁRIO_1
	auxiliar = fopen ("QUESTIONÁRIO_1.TXT", "w");
	if (auxiliar == NULL)
	{
		printf ("\nErro ao gerar o QUESTIONÁRIO_1.TXT!");
		getch(); exit(0);
	}
	
	//Ler o arquivo DAT TESTE_SISTEMA_REPRESENTACIONAL	
	arq3 = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "r");
	if (arq3 == NULL)
	{
		printf ("\nErro ao ler o TESTE_SISTEMA_REPRESENTACIONAL.DAT");
		getch(); exit(0);
	}
	
	//formatação do arquivo de texto conforme como o trabalho foi pedido
	fprintf(auxiliar,"NroFrase\t\t\t\t\tFrases\t\t\t   C item_1\t\t\t\t\t\t\t\t     A item_2\t\t\t\t\t\t\t\t       V item_3\t\t\t\t\t\t\t            D item_4");
    fprintf(auxiliar,"\n=======================================================================================================================================");
	fprintf(auxiliar,"=========================================================================================================================================");
	fprintf(auxiliar,"============================================================================================");
	
	//Enquanto não for fim do arquivo
	while ( !feof(arq3))	
	{
		//Ler os registros do arquivo DAT
		fread (&aux, sizeof(aux),1,arq3);
		
		//Se der erro ao ler mostrar na tela
		if(ferror(arq3))
		{
			printf ("\nErro ao ler o registro do QUESTIONÁRIO_1");
			getch(); break;
		}
		
		//Testar se leu o EOF
		if (!feof(arq3))
		{
			//Mostra no arquivo texto
			fprintf(auxiliar,"\n%2i %70s %2i %-70s %2i %-70s %2i %-65s %2i %-75s"
			,aux.NroFrase,aux.frase,aux.C,aux.item_1,aux.A,aux.item_2,aux.V,aux.item_3,aux.D,aux.item_4);
		}
	}
	fprintf(auxiliar,"\n=======================================================================================================================================");
	fprintf(auxiliar,"=========================================================================================================================================");
	fprintf(auxiliar,"============================================================================================");
	
	//Fecha o arquivo e o auxiliar
	fclose (arq3);
	fclose (auxiliar);
	
	//Abre com o notepad o arquivo QUESTIONÁRIO_1
	system ("notepad QUESTIONÁRIO_1");
}

//Corpo do programa RealizaTeste
void RealizaTeste (void)
{
	//Função RealizaTeste vai chamar as funções perguntas após o termino
	//mostrará o resultado e por último voltará para o menu
	system ("cls");
	Pergunta1(); Pergunta2(); Pergunta3(); Pergunta4(); Pergunta5(); RESULTADO(); MASTER();
}

//Corpo do programa Pergunta1
void Pergunta1 ()
{
	//Mostra na tela a estrutura da pergunta 1
	system("mode  72,21");
	printf("Nas frases a seguir, pontue com:");
	printf("\n4 a que melhor descreve você;");
	printf("\n3 a próxima melhor descrição;");
	printf("\n2 a próxima melhor; e");
	printf("\n1 aquela que menos descreve você.");
	
	printf("\n\n\n1. Eu tomo decisões importantes baseado em:");
	printf("\na) intuição.");
	printf("\nb) o que me soa melhor.");
	printf("\nc) o que me parece melhor.");
	printf("\nd) um estudo preciso e minucioso do assunto.");
	
	//Captura o que o usuário digitou e também faz uma comparação de possíveis erros que o usuário cometeu
	//A resposta tem que ser entre o número 1 e 4, sendo que todas as respostas diferentes uma das outras
	//Caso ele erre, o programa retornará uma mensagem de erro e voltará direto para o menu de escolhas
	printf("\n\n[a] -> "); fflush(stdin); scanf("%i",&reg[0].C);
	if (reg[0].C < 1 || reg[0].C > 4)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[b] -> "); fflush(stdin); scanf("%i",&reg[0].A);
	
	if (reg[0].A < 1 || reg[0].A > 4 || reg[0].A == reg[0].C)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[c] -> "); fflush(stdin); scanf("%i",&reg[0].V);
	
	if (reg[0].V < 1 || reg[0].V > 4 || reg[0].V == reg[0].C || reg[0].V== reg[0].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[d] -> "); fflush(stdin); scanf("%i",&reg[0].D);
	
	if (reg[0].D < 1 || reg[0].D > 4 || reg[0].D == reg[0].C || reg[0].D == reg[0].A || reg[0].D == reg[0].V)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
} 

//Corpo do programa Pergunta2
void Pergunta2 ()
{
	//mostra na tela a estrutura da pergunta 2
	system("cls"); system("mode  72,21");
	printf("Nas frases a seguir, pontue com:");
	printf("\n4 a que melhor descreve você;");
	printf("\n3 a próxima melhor descrição;");
	printf("\n2 a próxima melhor; e");
	printf("\n1 aquela que menos descreve você.");
	printf("\n\n\n2. Durante uma discussão eu sou mais influenciado por:");
	printf("\na) o tom da voz da outra pessoa.");
	printf("\nb) se eu posso ou não ver o argumento da outra pessoa.");
	printf("\nc) a lógica do argumento da outra pessoa.");
	printf("\nd) se eu entro em contato ou não com os sentimentos reais do outro.");
	
	//Captura o que o usuário digitou e também faz uma comparação de possíveis erros que o usuário cometeu
	//A resposta tem que ser entre o número 1 e 4, sendo que todas as respostas diferentes uma das outras
	//Caso ele erre, o programa retornará uma mensagem de erro e voltará direto para o menu de escolhas
	printf("\n\n[a] -> "); fflush(stdin); scanf("%i",&reg[1].A);
	if (reg[1].A < 1 || reg[1].A > 4)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[b] -> "); fflush(stdin); scanf("%i",&reg[1].V);
	
	if (reg[1].V < 1 || reg[1].V > 4 || reg[1].V == reg[1].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[c] -> "); fflush(stdin); scanf("%i",&reg[1].D);
	
	if (reg[1].D < 1 || reg[1].D > 4 || reg[1].D == reg[1].V || reg[1].D == reg[1].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[d] -> "); fflush(stdin); scanf("%i",&reg[1].C);
	
	if (reg[1].C < 1 || reg[1].C > 4 || reg[1].C == reg[1].D || reg[1].C == reg[1].V || reg[1].C == reg[1].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
}

//Corpo do programa Pergunta3
void Pergunta3 ()
{
	//Mostra na tela a estrutura da pergunta 3
	system("cls"); system("mode  72,21");
	printf("Nas frases a seguir, pontue com:");
	printf("\n4 a que melhor descreve você;");
	printf("\n3 a próxima melhor descrição;");
	printf("\n2 a próxima melhor; e");
	printf("\n1 aquela que menos descreve você.");
	printf("\n\n\n3. Eu comunico mais facilmente o que se passa comigo:");
	printf("\na) do modo como me visto e aparento.");
	printf("\nb) pelos sentimentos que compartilho.");
	printf("\nc) pelas palavras que escolho.");
	printf("\nd) pelo tom da minha voz.");
	
	//Captura o que o usuário digitou e também faz uma comparação de possíveis erros que o usuário cometeu
	//A resposta tem que ser entre o número 1 e 4, sendo que todas as respostas diferentes uma das outras
	//Caso ele erre, o programa retornará uma mensagem de erro e voltará direto para o menu de escolhas
	printf("\n\n[a] -> "); fflush(stdin); scanf("%i",&reg[2].V);
	if (reg[2].V < 1 || reg[2].V > 4)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[b] -> "); fflush(stdin); scanf("%i",&reg[2].C);
	
	if (reg[2].C < 1 || reg[2].C > 4 || reg[2].C == reg[2].V)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[c] -> "); fflush(stdin); scanf("%i",&reg[2].D);
	
	if (reg[2].D < 1 || reg[2].D > 4 || reg[2].D == reg[2].C || reg[2].D == reg[2].V)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[d] -> "); fflush(stdin); scanf("%i",&reg[2].A);
	
	if (reg[2].A < 1 || reg[2].A > 4 || reg[2].A == reg[2].D || reg[2].A == reg[2].C || reg[2].A == reg[2].V)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
}

//Corpo do programa Pergunta4
void Pergunta4 ()
{
	//Mostra na tela a estrutura da pergunta 4
	system("cls"); system("mode  72,21");
	printf("Nas frases a seguir, pontue com:");
	printf("\n4 a que melhor descreve você;");
	printf("\n3 a próxima melhor descrição;");
	printf("\n2 a próxima melhor; e");
	printf("\n1 aquela que menos descreve você.");
	printf("\n\n\n4. É muito fácil para min:");
	printf("\na) achar o volume e a sintonia ideais num sistema de som.");
	printf("\nb) selecionar o ponto mais relevante relativo a um assunto interessante.");
	printf("\nc) escolher os móveis mais confortáveis.");
	printf("\nd) escolher as combinações de cores mais ricas e atraentes.");
	
	//Captura o que o usuário digitou e também faz uma comparação de possíveis erros que o usuário cometeu
	//A resposta tem que ser entre o número 1 e 4, sendo que todas as respostas diferentes uma das outras
	//Caso ele erre, o programa retornará uma mensagem de erro e voltará direto para o menu de escolhas
	printf("\n\n[a] -> "); fflush(stdin); scanf("%i",&reg[3].A);
	if (reg[3].A < 1 || reg[3].A > 4)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[b] -> "); fflush(stdin); scanf("%i",&reg[3].D);
	
	if (reg[3].D < 1 || reg[3].D > 4 || reg[3].D == reg[3].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[c] -> "); fflush(stdin); scanf("%i",&reg[3].C);
	
	if (reg[3].C < 1 || reg[3].C > 4 || reg[3].C == reg[3].D || reg[3].C == reg[3].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[d] -> "); fflush(stdin); scanf("%i",&reg[3].V);
	
	if (reg[3].V < 1 || reg[3].V > 4 || reg[3].V == reg[3].C || reg[3].V == reg[3].D || reg[3].V == reg[3].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
}

//Corpo do programa Pergunta5
void Pergunta5 ()
{
	//Mostra na tela a estrutura da pergunta 5
	system("cls"); system("mode  72,21");
	printf("Nas frases a seguir, pontue com:");
	printf("\n4 a que melhor descreve você;");
	printf("\n3 a próxima melhor descrição;");
	printf("\n2 a próxima melhor; e");
	printf("\n1 aquela que menos descreve você.");
	printf("\n\n\n5. Eu me percebo assim:");
	printf("\na) se estou muito em sintonia com os sons dos ambientes.");
	printf("\nb) se sou muito capaz de raciocinar com fatos e dados novos.");
	printf("\nc) eu sou muito sensível à maneira como a roupa veste o meu corpo.");
	printf("\nd) eu respondo fortemente às cores e à aparência de uma sala.");
	
	//Captura o que o usuário digitou e também faz uma comparação de possíveis erros que o usuário cometeu
	//A resposta tem que ser entre o número 1 e 4, sendo que todas as respostas diferentes uma das outras
	//Caso ele erre, o programa retornará uma mensagem de erro e voltará direto para o menu de escolhas
	printf("\n\n[a] -> "); fflush(stdin); scanf("%i",&reg[4].A);
	if (reg[4].A < 1 || reg[4].A > 4)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[b] -> "); fflush(stdin); scanf("%i",&reg[4].D);
	
	if (reg[4].D < 1 || reg[4].D > 4 || reg[4].D == reg[4].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[c] -> "); fflush(stdin); scanf("%i",&reg[4].C);
	
	if (reg[4].C < 1 || reg[4].C > 4 || reg[4].C == reg[4].D || reg[4].C == reg[4].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
	printf("\n[d] -> "); fflush(stdin); scanf("%i",&reg[4].V);
	
	if (reg[4].V < 1 || reg[4].V > 4 || reg[4].V == reg[4].C || reg[4].V == reg[4].D || reg[4].V == reg[4].A)
	{
		system("cls"); system("mode 35,4");
		printf("\n\t ERRO AO ESCOLHER!"); getch(); MASTER();
	} 
}

//Corpo do programa SobreOTeste
void SobreOTeste (void)
{
	//Cria o arquivo de texto REFERENCIAL_TEORICO
	arq1 = fopen("REFERENCIAL_TEORICO.TXT", "w");
	
	//Copia para o arquivo de texto as seguintes mensagens:
	fprintf(arq1,"REFERENCIAL TEÓRICO");
	fprintf(arq1,"\n===================");
	fprintf(arq1,"\n\nSegundo Albert Merabian, em seu livro “Silent Messages”, o poder de influência das palavras não passa de 7%%,");
	fprintf(arq1,"\nenquanto a forma como as palavras são ditas e a fisiologia representam 38%% e 55%% deste poder, respectivamente.");
	fprintf(arq1,"\n\nPara Merabian 55%% do impacto da comunicação é não-verbal. Corresponde à postura, gestos e contato visual da pessoa enquanto se comunica.");
	fprintf(arq1,"\n\nO tom da voz representa 38%% do impacto da comunicação.");
	fprintf(arq1,"\n\nPor fim, as palavras propriamente ditas detêm 7%% do impacto da comunicação.");
	fprintf(arq1,"\n\nAssim sendo, conclui Merabian, não é o que dizemos, mas como dizemos que faz a diferença na comunicação.");
	fprintf(arq1,"\n\nAs portas da percepção são os nossos sentidos, nossos olhos, nariz, ouvidos, boca e pele, nossos únicos pontos de conato com o mundo exterior.");
	fprintf(arq1,"\nDa mesma forma que utilizamos os sentidos para filtrarmos as experiências, utilizamos os sentidos para estruturar nosso pensamento e nossa comunicação");
	fprintf(arq1,"\n\nDe acordo com a Programação Neurolinguística existem os seguintes sistemas representacionais.");
	fprintf(arq1,"\n\n- Auditivo");
	fprintf(arq1,"\n- Digital");
	fprintf(arq1,"\n- Cinestésico");
	fprintf(arq1,"\n- Visual");
	fprintf(arq1,"\n\nAlgumas pessoas captam melhor as mensagens do mundo exterior através da audição, são as pessoas chamadas auditivas.");
	fprintf(arq1,"\nOutras pessoas sentem necessidade de perguntar muito, necessitam de muitas informações e fatos. Estas são as digitais.");
	fprintf(arq1,"\nAs cinestésicas aprendem melhor por meio das sensações táteis, como o tato, a temperatura, a umidade, as sensações internas e as emoções.");
	fprintf(arq1,"\nJá as pessoas visuais aprendem melhor quando se valendo da visão.");
	fprintf(arq1,"\n\nCada pessoa tem um sistema representacional predominante e adequar a comunicação ao sistema representacional dominante dela é fundamental para diálogos eficientes.");
	
	//Fecha o arquivo
	fclose (arq1);
	
	//Função para abrir o arquivo de texto REFENCIAL_TEORICO com o notepad
	system ("notepad REFERENCIAL_TEORICO.TXT");
}

//Corpo do programa RESULTADO
void RESULTADO (void)
{
	//Variáveis locais da função RESULTADO
	int cin,aud,dig,vis;               //Variáveis int para pegar o resultado da soma e multiplicação dos itens
	char PERFIL[14];                   //Variável char para pegar o maior resultado do teste
	char ARQ_NOME[200], CHAMADA[200];  //Variaveis para poder nomear o arquivo TXT
	
	//Calculo do resultado do teste
	cin = (int)(reg[0].C + reg[1].C + reg[2].C + reg[3].C + reg[4].C)*2;
	aud = (int)(reg[0].A + reg[1].A + reg[2].A + reg[3].A + reg[4].A)*2;
	dig = (int)(reg[0].D + reg[1].D + reg[2].D + reg[3].D + reg[4].D)*2;
	vis = (int)(reg[0].V + reg[1].V + reg[2].V + reg[3].V + reg[4].V)*2;
	
	//Testar cada variável para saber qual é a maior nota
	//Ao percorrer os ifs ele renomeará o variável PERFIL de acordo com o maior resultado
	if (cin > aud && cin > dig && cin > vis)
	{
		strcpy(PERFIL,"CINESTÉSICO");
	}
	if (aud > cin && aud > dig && aud > vis)
	{
		strcpy(PERFIL,"AUDITIVO");
	}
	if (dig > cin && dig > aud && dig > vis)
	{
		strcpy(PERFIL,"DIGITAL");
	}
	if (vis > cin && vis > aud && vis > dig)
    {
    	strcpy(PERFIL,"VISUAL");
	}
	
	//Passa o nome que o usuário digitou para letras maiusculas
	for (i=0; i<strlen(login.nome);i++)
	{
		login.nome[i] = toupper(login.nome[i]);
		//Para cada ' ' "espaço" que o usuário digitou, virará '_' "underline"
		if (login.nome[i] == ' ')
		    login.nome[i] = '_';
	}
	
	//Passa o prontuário que o usuário digitou para letras maiusculas
	for (i=0; i<strlen(login.prontuario);i++)
	{
		login.prontuario[i] = toupper(login.prontuario[i]);
    }
    
    //Limpa o nome do arquivo
	for (i=0; i<strlen(ARQ_NOME); i++)
	{
		ARQ_NOME[i] = '\0';
	}
	
	//Criação da variavel ARQ_NAME servirá para preencher o nome do arquivo texto que será exibido no teste do usuário
	strcat(ARQ_NOME, "RESULTADO_");
	strcat(ARQ_NOME, login.nome);        //Pega o nome do usuário
	strcat(ARQ_NOME, "_");
	strcat(ARQ_NOME, login.prontuario);  //Pega o prontuário do usuário
	strcat(ARQ_NOME, ".TXT");
	
	//Abre o arquivo renomeado
	arq0 = fopen (ARQ_NOME,"w");
	if (arq0 == NULL)
	{
		printf("\nERRO AO ABRIR O %s!",ARQ_NOME);
		getch(); exit(0);
	}
	fprintf(arq0,"======================== PERFIL REPRESENTACIONAL DE %s ========================",login.nome);
	fprintf(arq0,"\n %i%% Visual \t %i%% Auditivo \t %i%% Cinestésico \t %i%% Digital",vis,aud,cin,dig);
	fprintf(arq0,"\n===================================================================================");
	fprintf(arq0,"\nAlgumas pessoas captam melhor as mensagens do mundo exterior através da audição, são as pessoas chamadas auditivas.");
	fprintf(arq0,"\nOutras pessoas sentem necessidade de perguntar muito, necessitam de muitas informações e fatos. Estas são as digitais.");
	fprintf(arq0,"\nAs cinestésicas aprendem melhor por meio das sensações táteis, como o tato, a temperatura, a umidade, as sensações internas e as emoções.");
	fprintf(arq0,"\nJá as pessoas visuais aprendem melhor quando se valendo da visão.");
	fprintf(arq0,"\n===================================================================================");
	fprintf(arq0,"\nSeu perfil é: %s",PERFIL);
	fprintf(arq0,"\n===================================================================================");
	
	//Outra variável para criação de uma string que a função system chamará abrindo com o notepad
	strcpy(CHAMADA, "notepad ");
	strcat(CHAMADA, ARQ_NOME);
	//Fecha arquivo
	fclose (arq0);
	//Função system que chamará o arquivo de texto Perfil representacional do usuário
	system (CHAMADA);
}

