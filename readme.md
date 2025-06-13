# Lógica Super Trunfo

Repositório para a entrega do trabalho "Lógica Super Trunfo em C", desenvolvido para a disciplina de Introdução à Programação de Computadores.

## Compilação e execução

A seguir, são apresentados alguns exemplos de como realizar o processo de compilação e linkagem utilizando os pacotes `gcc` e `cmake`.

### Compilação com gcc

Execução no terminal:

```sh
gcc -o card src/card.c src/main.c src/prompt.c -I include -Wall -std=c99
```

### Compilação com cmake

Execução no terminal:

```sh
cmake . && make
```

### Execução

Após o processo de compilação/link execute a aplicação com:

```sh
./card
```