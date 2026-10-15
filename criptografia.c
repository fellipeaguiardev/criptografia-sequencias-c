#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char palavra[50];
    int shift;
    int tipo;
    int letras;
} Criptografia;

void gerar_pa(int *seq, int n, int a1, int r) {
    for (int i = 0; i < n; i++) {
        seq[i] = a1 + (i * r);
    }
}

void gerar_pg(int *seq, int n, int a1, int q) {
    seq[0] = a1;
    for (int i = 1; i < n; i++) {
        seq[i] = seq[i - 1] * q;
    }
}

void gerar_fibonacci(int *seq, int n) {
    if (n > 0) seq[0] = 1;
    if (n > 1) seq[1] = 1;
    for (int i = 2; i < n; i++) {
        seq[i] = seq[i - 1] + seq[i - 2];
    }
}

void gerar_primos(int *seq, int n) {
    int count = 0, num = 2;
    while (count < n) {
        int primo = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                primo = 0;
                break;
            }
        }
        if (primo) {
            seq[count] = num;
            count++;
        }
        num++;
    }
}

int escolherSequencia(int *seq, int n) {
    int opcao, a1, razao;

    printf("\nEscolha a sequencia numerica para a Camada 2:\n");
    printf("1 - Progressao Aritmetica (PA)\n");
    printf("2 - Progressao Geometrica (PG)\n");
    printf("3 - Fibonacci\n");
    printf("4 - Numeros Primos\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("Digite o primeiro termo (a1) e a razao (r) da PA: ");
        scanf("%d %d", &a1, &razao);
        gerar_pa(seq, n, a1, razao);
    } else if (opcao == 2) {
        printf("Digite o primeiro termo (a1) e a razao (q) da PG: ");
        scanf("%d %d", &a1, &razao);
        gerar_pg(seq, n, a1, razao);
    } else if (opcao == 3) {
        gerar_fibonacci(seq, n);
    } else if (opcao == 4) {
        gerar_primos(seq, n);
    } else {
        printf("Opcao invalida. Usando Fibonacci como padrao.\n");
        opcao = 3;
        gerar_fibonacci(seq, n);
    }

    return opcao;
}

void criptografar(char *palavra, int *seq, int shift) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (isalpha(palavra[i])) {
            char base = islower(palavra[i]) ? 'a' : 'A';
            int deslocamento = (shift + seq[i]) % 26;
            if (deslocamento < 0) deslocamento += 26;
            palavra[i] = ((palavra[i] - base + deslocamento) % 26) + base;
        }
    }
}

void salvarResultado(const char *arquivo, Criptografia c) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fprintf(fp, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
            c.palavra, c.shift, c.tipo, c.letras);
    fclose(fp);
    printf("Resultado gravado em %s\n", arquivo);
}

void registrarLog(const char *arquivo, Criptografia c) {
    FILE *fp = fopen(arquivo, "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }
    fprintf(fp, "Criptografia realizada -> Palavra: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
            c.palavra, c.shift, c.tipo, c.letras);
    fclose(fp);
    printf("Execucao registrada em %s\n", arquivo);
}

void lerArquivo(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Nenhum dado salvo ainda.\n");
        return;
    }
    char linha[200];
    printf("\n--- %s ---\n", arquivo);
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }
    fclose(fp);
}

void novaCriptografia(const char *arqResultado, const char *arqLog) {
    Criptografia c;
    int sequencia[15];

    do {
        printf("\nDigite a palavra secreta (ate 15 letras, sem acentos): ");
        scanf("%s", c.palavra);
        c.letras = strlen(c.palavra);
        if (c.letras > 15) {
            printf("A palavra deve ter no maximo 15 letras!\n");
        }
    } while (c.letras > 15);

    printf("Digite o valor de SHIFT fixo (Cifra de Cesar): ");
    scanf("%d", &c.shift);

    c.tipo = escolherSequencia(sequencia, c.letras);

    printf("\nSequencia gerada: ");
    for (int i = 0; i < c.letras; i++) {
        printf("%d ", sequencia[i]);
    }

    criptografar(c.palavra, sequencia, c.shift);
    printf("\nPalavra criptografada: %s\n\n", c.palavra);

    salvarResultado(arqResultado, c);
    registrarLog(arqLog, c);
}

int main() {
    const char *arqResultado = "resultado_criptografia.txt";
    const char *arqLog = "log_execucao.txt";
    int opcao;

    do {
        printf("\n--- SISTEMA DE CRIPTOGRAFIA ---\n");
        printf("1 - Nova criptografia\n");
        printf("2 - Ver resultado\n");
        printf("3 - Ver log de execucao\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: novaCriptografia(arqResultado, arqLog); break;
            case 2: lerArquivo(arqResultado); break;
            case 3: lerArquivo(arqLog); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
