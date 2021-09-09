# Tic-Tac-Toe

<center>
<img src="https://super.abril.com.br/wp-content/uploads/2018/07/jogo_da_velha_-_tic_tac_toe.png" alt="Jogo da Velha" style="zoom:5%;width:50%;" />
<center>
  
O projeto a ser desenvolvido, consiste na criação do jogo da velha. Neste caso, o jogo será feito por dois usuários artificiais (ou seja duas threads) no mesmo jogo da velha. 

Cada usuário deve operar o jogo no mesmo tabuleiro do jogo da velha 3 por 3. Assim, o recurso compartilhado será tabuleiro do jogo da velha, logo os jogadores devem esperar a sua vez de jogar e obedecer a regras do jogo.

## Implementação👨‍💻

### Minimax🎮:

Em teoria da decisão, o minimax é um método para minimizar a possível perda máxima. Pode ser considerado como a maximização do ganho mínimo. Começa-se com dois jogadores 0-0 da teoria dos jogos, cobrindo ambos os casos em que os jogadores tomam caminhos alternados ou simultaneamente.

### Semáforo🚦: 

Semáforos são mecanismos que resolvem o problema de exclusão mútua. Um semáforo pode ser visto como um objeto que pode sofrer dois tipos de operação sobre ele: trancando e destrancando a execução de instruções (operações UP e DOWN, P e V). As operações sobre um semáforo são atômicas.

Semáforos são implementados no sistema operacional e são considerados uma forma de IPC (semáforos também podem ser usados para sincronização tão bem como para obtenção de exclusão mútua). Da mesma maneira que SO's diferentes implementam versões diferentes de memória compartilhada e filas de mensagens, há várias implementações de semáforos. O POSIX.1b implementa semáforos com identificadores e sem identificadores. O System V também implementa semáforos e são estes os que vão ser usados neste experimento.

### Multithreading🖥️:

Na arquitetura de computador, multithreading é a capacidade de uma unidade de processamento central de fornecer vários threads de execução simultaneamente, com suporte do sistema operacional. Essa abordagem difere do multiprocessamento.
