# Sistema de Criptografia com Sequências Numéricas

Atividade Avaliativa 02 — Algoritmo e Pensamento Computacional
Prof. Francisco de Assis Cavallaro

## Integrantes

- Fellipe da Eira Aguiar
- Guilherme Lucas Correa
- João Vitor Candido Cassiano
- Julio Cesar Ferreira do Nascimento
- Leonardo Vinicius de Farias

## Descrição

Programa em C que criptografa uma palavra de até 15 letras usando duas camadas de deslocamento no alfabeto:

- **Camada 1 — Cifra de César:** todas as letras são deslocadas pelo mesmo valor fixo (SHIFT).
- **Camada 2 — Sequência numérica:** cada letra recebe um deslocamento extra igual ao termo da sequência na mesma posição.

O deslocamento final de cada letra é calculado por:

```
deslocamento_total = (shift_fixo + sequencia[i]) % 26
```

O operador `% 26` faz o alfabeto dar a volta, de modo que depois do `z` vem novamente o `a`. Letras maiúsculas e minúsculas são mantidas, e caracteres que não são letras não são alterados.

Ao final, a palavra criptografada é exibida na tela e gravada no arquivo `resultado_criptografia.txt`. Cada criptografia também é registrada no arquivo `log_execucao.txt`, que acumula o histórico de todas as execuções.

O programa funciona por um menu com as opções: nova criptografia, ver o resultado salvo, ver o log de execução e sair.

## Como compilar e rodar

Precisa de um compilador C (GCC, Clang ou o MinGW no Windows).

```bash
gcc criptografia.c -o criptografia
./criptografia          # no Windows: criptografia.exe
```

Os arquivos `resultado_criptografia.txt` e `log_execucao.txt` são criados na pasta de onde o programa for executado.

## Sequências implementadas

| Opção | Sequência | Função | Termos |
|-------|-----------|--------|--------|
| 1 | Progressão Aritmética (PA) | `gerar_pa` | aₙ = a₁ + (n−1)·r |
| 2 | Progressão Geométrica (PG) | `gerar_pg` | aₙ = a₁·qⁿ⁻¹ |
| 3 | Fibonacci | `gerar_fibonacci` | 1, 1, 2, 3, 5, 8, 13... |
| 4 | Números Primos | `gerar_primos` | 2, 3, 5, 7, 11, 13... |

Na PA e na PG, o primeiro termo e a razão são informados pelo usuário. Se for escolhida uma opção inválida, o programa usa Fibonacci.

## Estrutura do código

**Struct `Criptografia`**

Agrupa os dados de cada execução: a palavra, o SHIFT, o tipo de sequência e a quantidade de letras.

**Funções de geração das sequências**

- `gerar_pa(seq, n, a1, r)` — preenche o vetor somando a razão `r` a cada termo.
- `gerar_pg(seq, n, a1, q)` — preenche o vetor multiplicando cada termo pela razão `q`.
- `gerar_fibonacci(seq, n)` — começa com 1 e 1, e cada termo seguinte é a soma dos dois anteriores.
- `gerar_primos(seq, n)` — testa os números a partir de 2 e guarda os que só são divisíveis por 1 e por eles mesmos, verificando divisores até a raiz quadrada do número.
- `escolherSequencia(seq, n)` — mostra as opções, lê a escolha do usuário e chama a função correspondente.

**Função de criptografia**

- `criptografar(palavra, seq, shift)` — percorre a palavra letra por letra e aplica o deslocamento total de cada posição.

**Funções de arquivo**

- `salvarResultado(arquivo, c)` — abre o arquivo no modo `"w"` (escrita) e grava o resultado da criptografia, substituindo o anterior.
- `registrarLog(arquivo, c)` — abre o arquivo no modo `"a"` (append) e acrescenta uma linha ao log, mantendo os registros anteriores.
- `lerArquivo(arquivo)` — abre o arquivo no modo `"r"` (leitura) e mostra o conteúdo linha por linha com `fgets`.

**Funções do menu**

- `novaCriptografia(arqResultado, arqLog)` — lê a palavra (repetindo se tiver mais de 15 letras) e o SHIFT, gera a sequência, criptografa, mostra o resultado e grava os dois arquivos.
- `main` — exibe o menu em um laço `do-while` e usa `switch` para chamar a função de cada opção.

**Conceitos utilizados:** struct, vetores, ponteiros, funções, estruturas de repetição e de decisão, menu interativo, tabela ASCII e manipulação de arquivos (escrita, append e leitura).

## Exemplo de execução

**Entrada**

```
Palavra: coracao
SHIFT: 3
Sequência: Fibonacci
```

**Cálculo**

| Letra | Termo | Deslocamento total | Resultado |
|-------|-------|--------------------|-----------|
| c | 1 | 3 + 1 = 4 | g |
| o | 1 | 3 + 1 = 4 | s |
| r | 2 | 3 + 2 = 5 | w |
| a | 3 | 3 + 3 = 6 | g |
| c | 5 | 3 + 5 = 8 | k |
| a | 8 | 3 + 8 = 11 | l |
| o | 13 | 3 + 13 = 16 | e |

**Saída**

```
Palavra criptografada: gswgkle
```

**Arquivo `resultado_criptografia.txt`**

```
Palavra codificada: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7
```

**Arquivo `log_execucao.txt`** (após duas execuções)

```
Criptografia realizada -> Palavra: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7
Criptografia realizada -> Palavra: Gjkoona | SHIFT: 5 | Tipo: 1 | Letras: 7
```

## Comparação entre as sequências

Palavra `coracao` com SHIFT 3:

| Sequência | Resultado |
|-----------|-----------|
| Somente César | frudfdr |
| PA (a₁=1, r=1) | gtxhkjy |
| PG (a₁=1, q=2) | gtylvjd |
| Fibonacci | gswgkle |
| Números Primos | huzkqqi |

Usando somente a Cifra de César, letras iguais sempre geram a mesma letra cifrada: os dois `c` viram `f`, os dois `a` viram `d` e os dois `o` viram `r`. Isso deixa o padrão da palavra visível e facilita a quebra da cifra.

Com a segunda camada, cada posição recebe um deslocamento diferente, e letras iguais passam a gerar letras diferentes. Entre as sequências, Fibonacci é a mais previsível no início, pois os dois primeiros termos são iguais (1 e 1). PA, PG e Primos geraram deslocamentos diferentes em todas as posições.

Mesmo com as duas camadas, a cifra não é considerada segura: conhecendo o algoritmo e a sequência usada, basta testar os 25 valores possíveis de SHIFT para descobrir a palavra original.
