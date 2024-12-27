//Gabriel Silva Taveira 201800085
//Trabalho de esteganografia
//Insere o caminho da imagem seguido do caminho de um txt que contem a mensagem. O código irá gerar uma nova imagem com a mensagem embutida. Para
//visualiza-la basta abrir a imagem com o editor de texto e a mensagem estará no final do arquivo

#include <stdio.h>
#include <stdlib.h>
#define MAX 999

int main() {
    int tamExtensions = 10, i = 0, k = 0, tamExtensionsTxt = 2; //variaveis de tamanho da string extensões e contador
    char caminho[MAX]; //string que armazena os caminhos inseridos
    char extensions[10][10] = {".jpg", ".jpg\"", ".jpeg", ".jpeg\"", ".png", ".png\"", ".gif", ".gif\"", ".bmp", ".bmp\""};//string de extensões pra comparação
    char extensionsTxt[2][5] = {".txt", ".txt\""};
    char comando[MAX] = "copy /b "; //string para concatenar o comando

    printf("Insira o caminho da imagem:\n");
    fgets(caminho, MAX, stdin);
    caminho[strlen(caminho) - 1] = '\0';

    //compara se o comando dado possui uma imagem
    while (1) {
        for (i = 0; i < tamExtensions; i++) {
            if (strstr(caminho, extensions[i]) == NULL) {
                k++; //se não achar uma ocorrencia da extensão
            }
        }
        if (k == i) { //todas as posições do loop nulas
            printf("Insira um caminho ou imagem valida\n");
            setbuf(stdin, NULL);
            fgets(caminho, MAX, stdin);
            caminho[strlen(caminho) - 1] = '\0';
            k = 0;
        } else {
            k = 0;
            break;
        }
    }

    strcat(comando, caminho);
    strcat(comando, "+");

    printf("Insira o caminho de um arquivo txt que contenha a mensagem:\n");
    fgets(caminho, MAX, stdin);
    caminho[strlen(caminho) - 1] = '\0';

    //compara se o caminho dado é de um arquivo de extensão txt
    while (1) {
        for (i = 0; i < tamExtensionsTxt; i++) {
            if (strstr(caminho, extensionsTxt[i]) == NULL) {
                k++; //se não achar uma ocorrencia da extensão
            }
        }
        if (k == i) {
            printf("Insira um caminho ou arquivo valido\n");
            setbuf(stdin, NULL);
            fgets(caminho, MAX, stdin);
            caminho[strlen(caminho) - 1] = '\0';
            k = 0;
        } else {
            break;
        }
    }

    strcat(comando, caminho);
    printf("%s", comando);
    strcat(comando, " imgnew.jpg");
    system(comando);

    return 0;
}
