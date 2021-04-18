#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <math.h>

#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};


int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}


int intercala(char *a1, char *a2, char *aSaida)
{   
    FILE *a, *b, *saida;
    Endereco ea, eb;
	a = fopen(a1, "r");
    b = fopen(a2, "r");
    saida = fopen(aSaida, "w");

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    while (!feof(a) && !feof(b))
    {
        if (compara(&ea, &eb) < 0)
        {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }
        else
        {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while (!feof(a))
    {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }
    while (!feof(b))
    {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);
}


int main(int argc, char**argv)
{
	FILE *f, *saida;
    Endereco *e;

	f = fopen("cep.dat","r"); 
    fseek(f,0,SEEK_END);
    long tamanhoArquivo = ftell(f);  
    int blocos = 16, posicao = 1;
    long qtdReg = tamanhoArquivo/sizeof(Endereco);
    long regbloco = qtdReg / blocos;
	

    printf("\n\n");
    printf("Tamanho do Arquivo: %ld\n", tamanhoArquivo);
	printf("Tamanho do Registro: %ld\n", sizeof(Endereco));
	printf("Tamanho do Arquivo em Registros: %ld\n", qtdReg);
    printf("Registros por Bloco: %ld\n", regbloco);
    printf("\n\n");
	
    e = (Endereco *) malloc(regbloco*sizeof(Endereco));
	rewind(f);

	int i = 1;
    while(i <= blocos)
	{	
		if (fread(e, sizeof(Endereco), regbloco, f) == regbloco)
        {
            printf("Lido %d = OK\n", i);
        }
        qsort(e, regbloco, sizeof(Endereco), compara);
        printf("Ordenado %d = OK\n", i);

        char cep[15];
        sprintf(cep,"%d.dat", i);

        saida = fopen(cep, "w");
        fwrite(e, sizeof(Endereco), regbloco, saida);
        fclose(saida);
		printf("Escrito %d = OK\n", i);
		i++;
        printf("\n\n");
        posicao++;
   }
    free(e);
    fclose(f);

    int pos = 1 , aux;

    for (int count = 1; count <= 4; count++)
    {
        printf("\n%d:\n\n", count);
        aux = posicao;
        blocos = blocos / 2;
        for (int i = 1; i <= blocos; i++)
        {
            char cep1[15], cep2[15], cepsaida[15];
            sprintf(cep1,"%d.dat", pos++);
            sprintf(cep2,"%d.dat", pos++);
            sprintf(cepsaida,"%d.dat", posicao++);
            printf("\nIntercala: %s + %s\n", cep1, cep2);
            printf("Arquivo Intercalado: %s \n", cepsaida);
          
            intercala(cep1, cep2, cepsaida);
            
            if (i == blocos)
            {
                pos = aux;
            }
        }
        printf("\n\n");
    }
    
    printf("Arquivo_Intercalado.dat Criado\n");
    rename("31.dat", "Arquivo_Intercalado");
    
    return 0;
}