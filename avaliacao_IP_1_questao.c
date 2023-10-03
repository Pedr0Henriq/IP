
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    int numfunc;
    int nivel;
    int departamento;
    int  proximo;
}funcionario;

typedef struct 
{
    int codDpt;
    char nomedpt[100];
    int inicio;
}departamento;

int checar_funcionario(FILE *file,int numero){
    int numero_f,nivel,departamento,proximo;
    char Numero[6],Nivel[5],Departamento[12],Proximo[7];
    file= fopen("Funcionarios.dat","r");
    if(file==NULL){
        printf("Erro ao abrir o arquivo.");
    }
        while(!feof(file)){
            fscanf(file,"%d %d %d %d",&numero_f,&nivel,&departamento,&proximo);
            if(numero_f==numero){
                fclose(file);
                return 1;}
        }
        fclose(file);
        return 0;
}

int checar_quantidade_funcionarios(FILE *file, funcionario func){
    int quantidade_func=0;
    file=fopen("Funcionarios.dat","r");
    if(file==NULL){
        printf("Erro ao abrir o arquivo.");
    }
    while (!feof(file))
    {
    fscanf(file,"%d%d%d%d",&func.numfunc,&func.nivel,&func.departamento,&func.proximo);
    quantidade_func+=1;
    }
    fclose(file);
    return quantidade_func;
    }

    
void adicionar_funcionario(FILE *file, funcionario func){
    int numero,z=0;
    z=checar_quantidade_funcionarios(file,func);
    if(z>20){
        printf("Quantidade maxima de funcionarios atingida.");
    }
    else{
    file = fopen("Funcionarios.dat","a");
    if(file==NULL){
        printf("Erro ao abrir o arquivo.");
    }
    printf("Digite o numero do funcionario: \n");
    scanf("%d",&numero);
    while(checar_funcionario(file,numero)!=0){
    printf("Funcionario ja existe.Digite um novo numero:\n");
    scanf("%d",&numero);}
    func.numfunc=numero;
    printf("Digite o nivel salarial do  funcionario: \n");
    scanf("%d",&func.nivel);
    printf("Digite o departamento do funcionario [0-Vendas, 1-Estoque, 2-Contabilidade, 3-Entrega, 4-RH]: \n");
    scanf("%d",&func.departamento);
    if(func.departamento<=-1 || func.departamento>=5){
        printf("Digite um departamento existente:\n");scanf("%d",&func.departamento);
    }
    printf("Digite o proximo funcionario do departamento: \n");
    scanf("%d",&func.proximo);
    fprintf(file,"\n%d \t%d \t%d \t\t%d",func.numfunc,func.nivel,func.departamento,func.proximo);}
    fclose(file);}

void demitir_funcionario(FILE  *file){
    int numero,remo,numfunc,nivel,Departamento,proximo;
    FILE *file_temp;
    file_temp=fopen("Funcionariostemp.dat","w");
    if(file_temp==NULL){
        printf("Erro ao abrir o arquivo.");}
    file=fopen("Funcionarios.dat","r");
    if(file==NULL){
        printf("Erro ao abrir o arquivo.");}
    printf("Digite o numero do funcionario:\n");
    scanf("%d",&numero);
    while(!feof(file)){
        
        fscanf(file,"%d %d %d %d",&numfunc,&nivel,&Departamento,&proximo);
        if(numfunc!=numero){
        fprintf(file_temp,"%d \t%d \t%d \t\t%d\n",numfunc,nivel,Departamento,proximo);
        }
    }
    fclose(file);
    fclose(file_temp);
    remove("Funcionarios.dat");
    rename("Funcionariostemp.dat","Funcionarios.dat");
    
    }

void mudar_dpt(FILE *file){
    int numero,numfunc,nivel,Departamento,proximo,novo_dpt;
    FILE *file_dpt;
    printf("Digite o numero do funcionario: \n"); scanf("%d",&numero);
file=fopen("Funcionarios.dat","r");
file_dpt=fopen("Atualizar_dpt.dat","w");
while(!feof(file)){
fscanf(file,"%d %d %d %d",&numfunc,&nivel,&Departamento,&proximo);
if(numfunc!=numero){
    fprintf(file_dpt,"%d \t%d \t%d \t\t%d\n",numfunc,nivel,Departamento,proximo);
}
else{
    printf("Digite o departamento do funcionario [0-Vendas, 1-Estoque, 2-Contabilidade, 3-Entrega, 4-RH]: \n");
    scanf("%d",&novo_dpt);
    fprintf(file_dpt,"%d \t%d \t%d \t\t%d\n",numfunc,nivel,novo_dpt,proximo);
}
}
fclose(file);
fclose(file_dpt);
remove("Funcionarios.dat");
rename("Atualizar_dpt.dat","Funcionarios.dat");
}


void consulta_dpt(FILE *file){
    int dpt,numfunc,nivel,Departamento,proximo,k=0;
    file=fopen("Funcionarios.dat","r");
    printf("Digite o departamento [0-Vendas, 1-Estoque, 2-Contabilidade, 3-Entrega, 4-RH]: \n");
    scanf("%d",&dpt);
    while(dpt<0 || dpt>4){
        printf("Digite um departamento existente [0-Vendas, 1-Estoque, 2-Contabilidade, 3-Entrega, 4-RH]: \n"); scanf("%d",&dpt);
    }
    while(!feof(file)){
        fscanf(file,"%d %d %d %d",&numfunc,&nivel,&Departamento,&proximo);
        if(dpt==Departamento){
            printf("Numero = %d \tNivel =%d \tDepartamento [0-Vendas, 1-Estoque, 2-Contabilidade, 3-Entrega, 4-RH] = %d \tProximo = %d\n",numfunc,nivel,Departamento,proximo);
            k+=1;
        }
    }
    if(k==0){
        printf("Nao existe funcionario nesse departamento.");
    }
    fclose(file);
}


void consulta_func(FILE *file){
    int numero,numfunc,nivel,Departamento,proximo;
    file=fopen("Funcionarios.dat","r");
    printf("Digite o numero do funcionario: \n"); scanf("%d",&numero);
    while(checar_funcionario(file,numero)!=1){
        printf("Digite um funcionario existente: \n"); scanf("%d",&numero);
    }
    while (!feof(file))
    {
        fscanf(file,"%d %d %d %d",&numfunc,&nivel,&Departamento,&proximo);
        if(numero==numfunc){
            printf("Numero = %d \tNivel =%d \tDepartamento [0-Vendas, 1-Estoque, 2-Contabilidade, 3-Entrega, 4-RH] = %d \tProximo = %d\n",numfunc,nivel,Departamento,proximo);
        }
    }
    fclose(file);
}

int main(int argc, char *argv[]){
    FILE *file,*arq;
    funcionario func;
    int operacao;
   file=fopen("Funcionarios.dat","r");
   if(file==NULL){
    printf("Erro ao abrir o arquivo.");
   }
   arq=fopen("Departamento.dat","r");
   if(arq==NULL){
    printf("Erro ao abrir o arquivo.");
   }
   fclose(file);
   fclose(arq);
   printf("Digite a operacao que quer fazer:\n0-FIM\n1- Admissao de funcionario\n2- Demissao de funcionario\n3- Mudanca de departamento\n4- Consulta de departamento\n5-Consulta funcionario\n");
    scanf("%d",&operacao);
    switch (operacao)
    {
    case 0:
        system("exit");
        break;
    case 1:
            adicionar_funcionario(file,func);
        break;
    case 2:
        demitir_funcionario(file);
        break;
    case 3:
        mudar_dpt(file);
        break;
    case 4:
       consulta_dpt(file);
        break;
    case 5:
        consulta_func(file);
        break;
    default:
    printf("Digite uma operacao valida!");
        break;
    }
    return 0;
}