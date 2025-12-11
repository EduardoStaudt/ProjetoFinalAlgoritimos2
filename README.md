# Jogo de Memoria com pontuação e ranking salvo em arquivo.

O projeto foi organizado nas seguintes pastas:

- `src/`  
  Contém os arquivos fonte em C:
  - `main.c` → fluxo principal do programa (menu, chamada de jogo e ranking)
  - `game.c` → lógica do jogo da memória (tabuleiro, cartas, jogadas)
  - `ranking.c` → funções do ranking (carregar, salvar, ordenar)
  - `utils.c` → funções de apoio (leitura de inteiros, pausa, etc.)

- `include/`  
  Contém os arquivos de cabeçalho:
  - `game.h` → declaração da struct `Carta` e das funções do jogo
  - `ranking.h` → declaração da struct `Jogador` e das funções do ranking
  - `utils.h` → protótipos das funções auxiliares

- `data/`  
  Pasta usada para arquivos gerados pelo programa:
  - `ranking.txt` → arquivo de texto onde o sistema salva o ranking de jogadores.

- `docs/`  
  Pasta com a documentação do projeto:
    `Documentacao_Projeto.docx`.

- `README.md`  
  Arquivo de resumo do projeto para o repositório.

## Alunos:

- Eduardo Andrei Staudt - RA: 2783045
- Brandon Monteiro Donisthorpe - RA: 2783034
- Henryque Leal de Oliveira Pimenta - RA: 2786532
- Diego Buettgen Assef - RA: 27866516

