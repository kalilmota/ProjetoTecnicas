#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>


//gerando uma struct para dados dos lutadores
struct lutadores{
       char nome[30];
       int idade;
       int peso; 
       int identificador;
       int venceu;      
}lutador[16];

//gerando struct para dados das lutas
struct estatisticas{
       int chutesErrados[16],chutesAcertados[16],chutesSofrido[16];
}estatistica[7];


//menu inicial
void menu();
char cadastraTorneio(int *);//cadastro do tipo de torneio
void adicionar(int,int *,int);//adiciona lutadores
void remover(int *);//remove lutadores
void verificaIdentificador(int aux,int cont);//gerar numero para sorteio
void chaves(int aux);//funçao que gera chaves inicial
void lutas(int aux,int luta[16]);
void mostraLutadores(int aux);



int main(int argc, char *argv[])
{
     //variaveis
     char opcao;// opcao  para menu
     int marcador=0;
     int *n,numero_participantes;//variaveis para numero de participantes
     int *p,peso;//categoria de peso dos atleta
     int cadastrados=0,cadastradosAux=0;
     //atribuindo endereços aos ponteiros
     p=&peso;
     n=&numero_participantes;     
      
     do
     { 
          system("cls");
          menu();
          do
          {
             opcao=getch();
             if(opcao!='1' && opcao!='2' && opcao!='3' && opcao!='4' && opcao!='5')
                 printf(" Erro Informe novamente \n");
          }while  (opcao!='1' && opcao!='2' && opcao!='3'  && opcao!='4' && opcao!='5' );
          switch(opcao)
          {
             case'1': 
             {
                    if(marcador==0)
                    {
                       opcao=cadastraTorneio(&*n);
                       marcador++;
                       if(opcao=='1')
                       peso=63;
                       else
                         if(opcao=='2')
                           peso=70;
                          else
                             if(opcao=='3')
                                  peso=76;                     
                       
                    }
                    break;         
             }
             case'2':
             {
                     if(marcador==1)
                     {
                         printf(" 1 - Adicionar\n 2 - Remover ");
                         opcao=getch();
                         switch(opcao)
                         {
                           case '1':{ 
                                while(lutador[cadastrados].identificador!=0)
                                   cadastrados++;
                                if(cadastrados<*n)
                                {
                                   adicionar(cadastrados,&*p,*n);
                                   if(cadastrados==cadastradosAux)
                                      cadastradosAux++;
                                   cadastrados++;
                                }
                                
                           
                               break;
                           }
                           case '2':  
                           {
                                if(cadastrados>0)
                                {   
                                   remover(&cadastrados);
                                }
                           }                
                         }
                     }
                     break;
             }
             case '3':
             {
                  while(lutador[cadastrados].identificador!=0)
                  {
                                   
                                    if(lutador[cadastrados].identificador==0)
                                    {
                                       cadastrados=cadastradosAux-1;
                                       break;
                                    }
                                    cadastrados++;
                  }
                  if(cadastrados==*n)
                  {   
                     
                     marcador=2;
                     chaves(*n);
                  }
                  break;             
             }
             case '4':
                   if(marcador==2)    
                      mostraLutadores(*n); 
          }
     }while(opcao!='5');	
  return 0;
}
//MENU
void menu()
{
     puts("1 - Tipo do torneio");
     puts("2 - Adiocionar ou remover");
     puts("3 - Comecar torneio");
     puts("4 - Visualizar estatistica");
     puts("5 - Fechar o programa");    
}


//funcao para cadastar tipo de torneio
char cadastraTorneio(int *participantes)
{
     char opcao,cont;
     //Numero de atletas para ser registrado
     do
     {
       printf(" Iforme o numero de participantes: ");
       printf(" \n 4 - 8 - 16 \n ");
       scanf("%d",&*participantes);
       if(*participantes!=4 && *participantes!=8 && *participantes!=16)
       {
          system("cls");
          printf(" Informe novamente!\n");
       }    
     }while(*participantes!=4 && *participantes!=8 && *participantes!=16);
     
     //categoria de peso
     do
     {
        printf(" Informe o peso para o torneio: ");
        printf("\n 1 - 63 - 69");
        printf("\n 2 - 70 - 76");
        printf("\n 3 - 76 - 82\n");
        opcao=getch();                 
     }while(opcao!='1' && opcao!='2' && opcao!='3');
   for(cont=0;cont<*participantes;cont++)
      lutador[cont].identificador=0;
   return opcao;
          
       
         
}

void adicionar(int cont,int *p,int aux)//adiciona lutadores
{
     //auxliar para contagem de participantes
     int identificador;
     int tamanho;//contagem de caracter
          fflush(stdin);
          system("cls");
          do
          {
            printf(" LUTADOR n%d\n",cont+1);
            printf(" Nome do participante : ");
            fgets(lutador[cont].nome,20,stdin);//leitura a partir do teclado para que não estoure o vetor
            if(lutador[cont].nome[0]=='n')
               printf("Informe novamente: ");   
          }while(lutador[cont].nome[0]=='n');
          tamanho=strlen(lutador[cont].nome)-1;//contagem de caracter par ao nome
          lutador[cont].nome[tamanho]='\0';
          do
          {
             printf(" Idade :");
             scanf("%d",&lutador[cont].idade); 
             if(lutador[cont].idade<15 || lutador[cont].idade>30)
             {   
                printf(" Idade minima = 15\n Idade maxima =30");
                printf(" \n Informe novamente: ");
                scanf("%d",&lutador[cont].idade);
             }              
          }while(lutador[cont].idade<15 || lutador[cont].idade>30);
          do
          {
             printf("\n Peso: ");
             scanf("%d",&lutador[cont].peso);
             if(lutador[cont].peso<*p || lutador[cont].peso>*p+6)
             {    
                 printf(" Peso minimo = %d",*p);
                 printf("Informe nomavente ");
                 
             }
          }while(lutador[cont].peso<*p || lutador[cont].peso>*p+6);  
          verificaIdentificador(aux,cont);
          lutador[cont].venceu=1;

}


void remover(int *cadastrados)//remove lutadores
{
int cont;
     int opcao;
     
     system("cls");
     for(cont=0;cont<*cadastrados;cont++)
          printf(" %d - %s ",cont+1,lutador[cont].nome);
     do
     {
          scanf("%d",&opcao);
     }while(opcao>*cadastrados || opcao<1);
     *cadastrados=opcao-1;
     lutador[opcao-1].identificador=0;   

}

//funcao para gerar identificador "randomicamente"
void verificaIdentificador(int aux,int cont)
{
     int anteriores=0;
     
     //gerando numero aleatorioamente com a função rand 
     lutador[cont].identificador=(rand()%aux)+1;
     while(cont>0 && anteriores<cont)
     {   
        //condição caso o numero sorteado seja igual a um já existente
        if(lutador[cont].identificador==lutador[anteriores].identificador)
        {    
            lutador[cont].identificador=(rand()%aux)+1;
            anteriores=-1;// para que volte para o zero
        }
        anteriores++;
     }
}

//funcao para gerar chaves do inicio do torneio
void chaves(int aux)
{
     int cont,random=1,luta[aux],cont2=0;
     
     system("cls");
     for(cont=0;cont<aux;cont++)
     {
        if(lutador[cont].identificador==random )
        {    
            if(lutador[cont].venceu==1)
            {
              if(random%2==0)
                printf("\n Vs ");
              printf("====\n %s ",lutador[cont].nome);
              luta[cont2]=cont;
              cont2++;
              cont=-1;
            }
            random++;
            
         }
     }
     getch();
     if(cont2>1)  
       lutas(aux,luta);
   
}

//funcao para acontecimento de cada luta
void lutas(int aux,int luta[16])
{
    static int numeroLuta=0;
    char continua;
    int cont;
    if((numeroLuta!=2 && aux==4) || (numeroLuta!=3 && aux==8) || (numeroLuta!=6 &&aux==16))
    for(cont=0;cont<aux;cont+=2)
    {  
      do
      {
          system("cls");
          printf("\n%s Vs %s",lutador[luta[cont]].nome,lutador[luta[cont+1]].nome);
          printf("\n %s ",lutador[luta[cont]].nome);
          printf("\n Numero de chute acertados: ");
          scanf("%d",&estatistica[numeroLuta].chutesAcertados[cont]);
          printf(" Numero de chute errados: ");
          scanf("%d",&estatistica[numeroLuta].chutesErrados[cont]);
          printf(" Numero de chute sofridos: ");
          scanf("%d",&estatistica[numeroLuta].chutesSofrido[cont]);
          printf("\n %s ",lutador[luta[cont+1]].nome);
          printf(" Numero de chute errados: ");
          scanf("%d",&estatistica[numeroLuta].chutesErrados[cont+1]);
          system("cls");
          
        
          estatistica[numeroLuta].chutesAcertados[cont+1]=estatistica[numeroLuta].chutesSofrido[cont];
          estatistica[numeroLuta].chutesSofrido[cont+1]=estatistica[numeroLuta].chutesAcertados[cont];
          printf("\n %s ",lutador[luta[cont]].nome);
          printf("\n Numero de chute acertados: %d",estatistica[numeroLuta].chutesAcertados[cont]);
          printf("\n Numero de chute errados: %d",estatistica[numeroLuta].chutesErrados[cont]);
          printf("\n Numero de chute sofrdiso: %d",estatistica[numeroLuta].chutesSofrido[cont]); 
          printf("\n %s ",lutador[luta[cont+1]].nome);
          printf("\n Numero de chute acertados: %d",estatistica[numeroLuta].chutesAcertados[cont+1]);
          printf("\n Numero de chute errados: %d",estatistica[numeroLuta].chutesErrados[cont+1]);
          printf("\n Numero de chute sofrdiso: %d",estatistica[numeroLuta].chutesSofrido[cont+1]); 
          printf("\n Deseja mudar algum dado?\n 1 - Sim\n 2 - Nao");
          
          do
          {
             continua=getch();
          }while(continua !='1' && continua!='2');   
       }while(continua=='1');
       if(estatistica[numeroLuta].chutesAcertados[cont]>estatistica[numeroLuta].chutesSofrido[cont])
       {   
          lutador[cont].venceu=1;
          lutador[cont+1].venceu=0;   
       }
       else
       {   
          lutador[cont].venceu=0;
          lutador[cont+1].venceu=1; 
       }
    }

    numeroLuta++;
    chaves(aux);  
  


}
//funcao para verificar estatisticas
void mostraLutadores(int aux)
{
     int cont;//variavel para contagem
     int opcao;
     
     system("cls");
     //repetição que mostra competidores
     for(cont=0;cont<aux;cont++)
     {
         printf(" %d - %s \n",cont+1,lutador[cont].nome);                   
                        
     }
     // repetição de validação
     do
     {
                  scanf("%d",&opcao);    
     }while(opcao<1 && opcao>aux);
     //mostrar chutes das lutas. caso n tenha lutado uma das lutas aparecerá 0
     for(cont=0;cont<aux/2;cont++)
     {  
        if(estatistica[cont].chutesAcertados[opcao-1]>0)
           printf("luta %d Chutes Acertados  - %d \n",cont+1,estatistica[cont].chutesAcertados[opcao-1]);
           printf("luta %d  Chutes Errados - %d\n",cont+1,estatistica[cont].chutesErrados[opcao-1]);
           printf("luta %d Chutes Sofridos  - %d\n",cont+1,estatistica[cont].chutesSofrido[opcao-1]);
     }
     getch();
     
}
