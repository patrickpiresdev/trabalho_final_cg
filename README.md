# Robo (Perdidos no Espaço)

Link para o github: [https://github.com/patrickpiresdev/trabalho_final_cg](https://github.com/patrickpiresdev/trabalho_final_cg)

## Instruções para execução
Para executar o programa, basta seguir os passos abaixo ou assistir o vídeo de demonstração disponível no link [https://youtu.be/Kj6UwRKHefY](https://youtu.be/Kj6UwRKHefY).

Basta executar `./exe/main.exe` estando no diretório onde este `README` se encontra, i.e., na pasta do projeto.

## Instruções para uso

### Instruções gerais para movimentos
Para realizar qualquer movimento, é preciso selecionar o modo de movimento desejado. O que isso significa? Dentro desta aplicação, podemos aplicar diferentes movimentos em diferentes objetos. Para isso, há uma tabela que indica qual modo devemos selecionar para realizar os movimentos desejados.
Exemplo:

Para movimentarmos o braco esquerdo, devemos digitar o número 2, como indica a tabela abaixo.

| codigo | modo de movimento       |
|--------|-------------------------|
|    1   | CAMERA_ROTATION_MODE    |
|    2   | LEFT_ARM_MOVEMENT_MODE  |
|    3   | RIGHT_ARM_MOVEMENT_MODE |
|    4   | HEAD_MOVEMENT_MODE      |
|    5   | TRUNK_MOVEMENT_MODE     |
|    6   | ROBOT_MOVEMENT_MODE     |
|    7   | CAMERA_ZOOM_MODE        |
|    8   | CAMERA_MOVEMENT_MODE    |

Para realizar um movimento após selecionar o modo, consulte abaixo os detalhes de cara modo de movimento.

### CAMERA_ROTATION_MODE
Permite a rotação da camera através das teclas `w`, `s`, `a` e `d`.

### LEFT_ARM_MOVEMENT_MODE
Permite a movimentação geral do braço esquerdo do robô. Para isso, utilize as teclas `w`, `s`, `a` e `d`.

Para retrair e estender o braço, utilize as teclas `z` e `c`.

Para abrir e fechar a pinça, utilize as teclas `q` e `e`.

### RIGHT_ARM_MOVEMENT_MODE
Funciona de maneira análoga ao `LEFT_ARM_MOVEMENT_MODE`, porém para o braço direito.

### HEAD_MOVEMENT_MODE
Permite a movimentação da cabeça do robô. Para isso, utilize as teclas `w`, `s`, `a` e `d`.

### TRUNK_MOVEMENT_MODE
Permite a movimentação do tronco do robô. Para isso, utilize as teclas `a` e `d`.

### ROBOT_MOVEMENT_MODE
Permite a movimentação do robô para frente e para trás. Para isso, utilize as teclas `w`, `s`.

### CAMERA_ZOOM_MODE
Permite o zoom da camera através das teclas `w` e `s`.

### CAMERA_MOVEMENT_MODE
Permite a movimentação da camera através das teclas `w`, `s`, `a` e `d`. Essa movimentação para cima, baixo, esquerda e direita. Para rotacionar a camera, consulte o modo `CAMERA_ROTATION_MODE`.