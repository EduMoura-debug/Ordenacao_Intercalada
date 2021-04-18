#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

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
    int blocos = 16, pos1 = 1;
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
        pos1++;
   }
    free(e);
    fclose(f);

    /* Estava tentando fazer um for para não precisar escrever tudo isso,
       tinha algum erro lógico e devia estar errando em alguma parte da 
       lógica. Contudo o código funciona
    */

    printf("\n1: Intercalando 8 vezes\n\n");
            
    printf("\nIntercala: 1.dat com 2.dat \n");
    printf("Arquivo Intercalado: 17.dat \n");
    intercala("1.dat", "2.dat", "17.dat");
    
    printf("\nIntercala: 3.dat com 4.dat \n");
    printf("Arquivo Intercalado: 18.dat \n");
    intercala("3.dat", "4.dat", "18.dat");

    printf("\nIntercala: 5.dat com 6.dat \n");
    printf("Arquivo Intercalado: dat.19 \n");
    intercala("5.dat", "6.dat", "19.dat");

    printf("\nIntercala: 7.dat com 8.dat \n");
    printf("Arquivo Intercalado: 20.dat \n");
    intercala("7.dat", "8.dat", "20.dat");

    printf("\nIntercala: 9.dat com 10.dat \n");
    printf("Arquivo Intercalado: 21.dat \n");
    intercala("9.dat", "10.dat", "21.dat");        
    
    printf("\nIntercala: 11.dat com 12.dat \n");
    printf("Arquivo Intercalado: 22.dat \n");
    intercala("11.dat", "12.dat", "22.dat");

    printf("\nIntercala: 13.dat com 14.dat \n");
    printf("Arquivo Intercalado: 23.dat \n");
    intercala("13.dat", "14.dat", "23.dat");

    printf("\nIntercala: 15.dat com 16.dat \n");
    printf("Arquivo Intercalado: 24.dat \n");
    intercala("15.dat", "16.dat", "24.dat");

    // Fim do intercalamento de 8 blocos

    printf("\n2: Intercalando 4 vezes\n\n");
            
    printf("\nIntercala: 17.dat com 18.dat \n");
    printf("Arquivo Intercalado: 25.dat \n");
    intercala("17.dat", "18.dat", "25.dat");
    
    printf("\nIntercala: 19.dat com 20.dat \n");
    printf("Arquivo Intercalado: 26.dat \n");
    intercala("19.dat", "20.dat", "26.dat");

    printf("\nIntercala: 21.dat com 22.dat \n");
    printf("Arquivo Intercalado: 27.dat \n");
    intercala("21.dat", "22.dat", "27.dat");

    printf("\nIntercala: 23.dat com 24.dat \n");
    printf("Arquivo Intercalado: 28.dat \n");
    intercala("23.dat", "24.dat", "28.dat");

    // Fim do intercalamento de 4 blocos

    printf("\n3: Intercalando 2 vezes\n\n");
            
    printf("\nIntercala: 25.dat com 26.dat \n");
    printf("Arquivo Intercalado: 29.dat \n");
    intercala("25.dat", "26.dat", "29.dat");
    
    printf("\nIntercala: 27.dat com 28.dat \n");
    printf("Arquivo Intercalado: 30.dat \n");
    intercala("27.dat", "28.dat", "30.dat");

    // Fim do intercalamento de 2 blocos

    printf("\n4: Intercalando 1 vezes\n\n");
            
    printf("\nIntercala: 29.dat com 30.dat \n");
    printf("Arquivo Intercalado: 31.dat \n");
    intercala("29.dat", "30.dat", "31.dat");
    
    // Fim do intercalamento de 1 blocos
    
    printf("Arquivo_Intercalado.dat Criado\n");
    rename("31.dat", "Arquivo_Intercalado");
    
    return 0;
}