#PAA-Damas e Vovô
Primeiro trabalho da disciplina de Projeto e Análise de Algoritmos (2025.1)</br>
O comando para a execução é: 

    ./tp -i <entrada.txt> -o <1 para forca bruta|2 para backtracking> -s <saida.txt>

O programa irá imprimir a maior quantidade de peças que podem ser "comidas" por tabuleiro no arquivo informado após "-s", separando por linha a resposta de cada tabuleiro informado.</br>

A entrada contém vários casos de teste. A primeira linha de um caso de teste contém dois inteiros N e M indicando respectivamente o número de linhas e o número de colunas do tabuleiro
(3 ≤ N ≤ 20, 3 ≤ M ≤ 20 e N × M ≤ 200). O quadrado mais à esquerda do tabuleiro na borda
mais próxima ao jogador é uma casa. A segunda linha contém a descrição do estado do jogo.
Cada descrição consiste de (N × M)/2 inteiros, separados por um espaço, correspondendo às
casas do tabuleiro, que são numeradas de 1 a (N × M)/2, da esquerda para a direita, da borda
mais próxima ao jogador à borda mais próxima ao seu oponente. Na descrição do estado do jogo, 0
representa uma casa vazia, 1 representa uma casa com uma de suas peças, e 2 representa uma casa
com uma peça de seu oponente. Há no máximo (N × M)/4 peças de cada jogador no tabuleiro. O
final da entrada é indicado por N = M = 0.
</br>Exemplo de entrada:</br>
3 3</br>
2 1 2 0 1</br>
5 3</br>
1 0 2 1 0 2 0 0</br>
8 8</br>
2 2 2 2 0 0 0 0 2 2 2 2 0 0 0 0 2 2 2 2 0 0 0 0 2 2 2 2 0 1 0 0</br>
0 0</br>

</br>Exemplo de Saída:</br>
1</br>
2</br>
7</br>
