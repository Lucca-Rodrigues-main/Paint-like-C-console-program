# Paint-like-C-console-program
A console-based Paint-like program using Windows API. Features: 9 colors selection, eraser and clear screen functionality.

## Funcionalidades Implementadas
Este é um simples programa em C que simula um Paint no console do Windows, permitindo desenhar com diferentes cores usando o mouse e teclado.

- **Sistema de Cores**: 9 cores disponíveis para desenho (preto, azul claro, verde claro, vermelho claro, magenta claro, amarelo, ciano claro, marrom e cinza claro)
- **Controles por Teclado**:
  - Teclas numéricas (1-9) selecionam cores diferentes
  - Tecla 'E' ativa o modo borracha (branco)
  - Tecla 'C' limpa a tela inteira
- **Desenho com Mouse**: Clique e arraste com botão esquerdo para desenhar

## Como Funciona

O programa utiliza funções da API do Windows para:
- Manipular atributos de texto do console (`SetConsoleTextAttribute`)
- Capturar posição do mouse (`GetCursorPos`, `ScreenToClient`)
- Ler estado do teclado (`GetKeyState`, `GetAsyncKeyState`)

## Utilização

1) Use teclas 1-9 para selecionar cores
2) Clique e arraste para desenhar
3) Pressione ESC para sair

![meugif](https://github.com/user-attachments/assets/3411af2e-17f9-4e80-9b5c-ca2fd48f5b29)
