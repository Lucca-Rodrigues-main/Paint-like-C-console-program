// Definir cores para facilitar
#define		preto            0
#define		azul             1
#define		verde            2
#define		ciano            3
#define		vermelho         4
#define		magenta          5
#define		marrom           6
#define		cinza_claro      7
#define		cinza_escuro     8
#define		azul_claro       9
#define		verde_claro     10
#define		ciano_claro     11
#define		vermelho_claro  12
#define		magenta_claro   13
#define		amarelo         14
#define		branco          15

#include <stdio.h>
#include <windows.h>

// Preenche o buffer com uma cor de fundo e texto especificada
void LimpaTela(int texto, int fundo);
// Funcao para posicionar o cursor em uma coordenada (X, Y)
void cursor(short x, short y);
// Funcao para mudar a cor do bloco de caractere
void cortexto(int cor);

int main ()
{
    // Maximizar a janela do console
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    // Preencher o buffer em branco
    LimpaTela(preto, branco);

    int mudacor = 0; // Cor inicial preta
    short posx, posy;
    POINT posicao; // Estrutura para armazenar a posicao do mouse em pixels

    do{
        // Verifica se a posicao do mouse foi obtida com sucesso
        if (GetCursorPos(&posicao)) {

            // Bloco para selecionar a cor com as teclas numericas
            if(GetKeyState('1') < 0){
                mudacor = 0; // Preto
            } else if(GetKeyState('2') < 0){
                mudacor = 9; // Azul Claro
            } else if(GetKeyState('3') < 0){
                mudacor = 10; // Verde Claro
            } else if(GetKeyState('4') < 0){
                mudacor = 12; // Vermelho Claro
            } else if(GetKeyState('5') < 0){
                mudacor = 13; // Magenta Claro
            } else if(GetKeyState('6') < 0){
                mudacor = 14; // Amarelo
            } else if(GetKeyState('7') < 0){
                mudacor = 11; // Ciano Claro
            } else if(GetKeyState('8') < 0){
                mudacor = 6;  // Marrom
            } else if(GetKeyState('9') < 0){
                mudacor = 7;  // Cinza Claro
            } else if(GetKeyState('E') < 0){ // Tecla 'E' de Eraser (Borracha)
                mudacor = 15; // Branco
            } else if(GetKeyState('C') < 0){ // Tecla 'C' de Clear (Limpar)
                LimpaTela(preto, branco); // Limpa a tela para branco
            }

            // Verifica se o botao esquerdo do mouse esta pressionado
            if (GetAsyncKeyState(VK_LBUTTON) < 0) {

                // Logica de calculo da posicao do mouse
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_SCREEN_BUFFER_INFO csbi;
                RECT rect;

                // Converte as coordenadas do mouse da tela para a area cliente da janela do console
                ScreenToClient(consoleWindow, &posicao);

                // Obtem informa  es do buffer (tamanho em caracteres)
                GetConsoleScreenBufferInfo(hConsole, &csbi);
                // Obtem informa  es da janela (tamanho em pixels)
                GetClientRect(consoleWindow, &rect);

                // Calcula o tamanho de uma celula de caractere em pixels
                int colunasDaJanela = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                int linhasDaJanela  = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                int charLargura_px = (rect.right - rect.left) / colunasDaJanela;
                int charAltura_px  = (rect.bottom - rect.top) / linhasDaJanela;

                // Evita divisao por zero se a janela estiver minimizada
                if (charLargura_px > 0 && charAltura_px > 0)
                {
                    // Converte a posi  o do mouse em pixels para coordenadas de caracteres (coluna, linha)
                    posx = posicao.x / charLargura_px;
                    posy = posicao.y / charAltura_px;

                    // Garante que a posicao calculada esta dentro dos limites do buffer
                    if (posx >= 0 && posx < csbi.dwSize.X && posy >= 0 && posy < csbi.dwSize.Y)
                    {
                        cursor(posx, posy);       // Move o cursor para a posicao
                        cortexto(mudacor);        // Define a cor de desenho
                        printf(" ");              // Desenha o bloco de cor
                        cursor(0, 0);             // Esconde o cursor no canto para nao piscar
                    }
                }
            }
        }
    } while(GetKeyState(VK_ESCAPE) >= 0); // O loop continua enquanto ESC n o for pressionado

    return (0);
}

void LimpaTela(int texto, int fundo)
{
    WORD wColor = ((fundo & 0x0F) << 4) + (texto & 0x0F);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    SetConsoleTextAttribute(hStdOut, wColor);
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}

void cursor(short x, short y)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(hStdOut, coord);
    return;
}

void cortexto(int cor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor | (cor << 4));
}
