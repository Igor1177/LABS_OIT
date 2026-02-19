#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <math.h>

#define SIZE 5
#define ALPHABET_SIZE 26

void prepareKeyword(char* keyword, char* prepared) {
    int used[26] = { 0 };
    int pos = 0;

    for (int i = 0; i < strlen(keyword); i++) {
        char c = keyword[i];

        if (c >= 'a' && c <= 'z') c -= 32;

        if (c < 'A' || c > 'Z') continue;

        if (c == 'J') c = 'I';

        if (!used[c - 'A']) {
            used[c - 'A'] = 1;
            prepared[pos++] = c;
        }
    }
    prepared[pos] = '\0';
}

void createMatrix(char* keyword, char matrix[SIZE][SIZE]) {
    char preparedKeyword[100];
    prepareKeyword(keyword, preparedKeyword);

    int used[26] = { 0 };
    int pos = 0;

    for (int i = 0; i < strlen(preparedKeyword); i++) {
        char c = preparedKeyword[i];
        used[c - 'A'] = 1;
        matrix[pos / SIZE][pos % SIZE] = c;
        pos++;
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        char letter = c;
        if (letter == 'J') continue;

        if (!used[letter - 'A'] && pos < SIZE * SIZE) {
            matrix[pos / SIZE][pos % SIZE] = letter;
            pos++;
        }
    }
}


void findPosition(char matrix[SIZE][SIZE], char c, int* row, int* col) {
    if (c == 'J') c = 'I';

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == c) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

char* prepareText(char* input) {
    char* result = (char*)malloc(strlen(input) * 2 + 1);
    int pos = 0;

    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];

        if (c >= 'a' && c <= 'z') c -= 32;

        if (c >= 'A' && c <= 'Z') {
            if (c == 'J') c = 'I';
            result[pos++] = c;
        }
    }

    if (pos % 2 != 0) {
        result[pos++] = 'X';
    }

    result[pos] = '\0';
    return result;
}


void encrypt(char* plaintext, char matrix1[SIZE][SIZE], char matrix2[SIZE][SIZE], char* ciphertext, char* des) {
    char* preparedText = prepareText(plaintext);
    int len = strlen(preparedText);
    int pos = 0;

    for (int i = 0; i < len; i += 2) {
        char c1 = preparedText[i];
        char c2 = preparedText[i + 1];

        int r1, c1_pos, r2, c2_pos;
        findPosition(matrix1, c1, &r1, &c1_pos);
        findPosition(matrix2, c2, &r2, &c2_pos);

        if (r1 == r2) {
            des[i] = 1;
            ciphertext[pos++] = matrix1[r1][c2_pos];
            ciphertext[pos++] = matrix2[r2][c1_pos];
        }
        else {
            ciphertext[pos++] = matrix2[r1][c2_pos];
            ciphertext[pos++] = matrix1[r2][c1_pos];
        }


    }

    ciphertext[pos] = '\0';
    free(preparedText);
}

void decrypt(char* ciphertext, char matrix1[SIZE][SIZE], char matrix2[SIZE][SIZE], char* plaintext, char* des) {
    int len = strlen(ciphertext);
    int pos = 0;

    for (int i = 0; i < len; i += 2) {
        char c1 = ciphertext[i];
        char c2 = ciphertext[i + 1];

        int r1, c1_pos, r2, c2_pos;

        if (des[i] == 1) {
            findPosition(matrix1, c1, &r1, &c1_pos);
            findPosition(matrix2, c2, &r2, &c2_pos);
            plaintext[pos++] = matrix1[r1][c2_pos];
            plaintext[pos++] = matrix2[r2][c1_pos];
        }

        else {
            findPosition(matrix2, c1, &r1, &c1_pos);
            findPosition(matrix1, c2, &r2, &c2_pos);
            plaintext[pos++] = matrix1[r1][c2_pos];
            plaintext[pos++] = matrix2[r2][c1_pos];
        }
    }

    plaintext[pos] = '\0';
}

void printMatrix(char matrix[SIZE][SIZE], const char* name) {
    printf("\n%s :\n", name);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c  ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, "ru");


    char keyword1[100], keyword2[100];
    char matrix1[SIZE][SIZE], matrix2[SIZE][SIZE];
    char input[1000];
    char ciphertext[2000];
    char decryptedtext[2000];
    char des[1000] = { 0 };

    printf("Введите первое ключевое слово: ");
    fgets(keyword1, sizeof(keyword1), stdin);
    keyword1[strcspn(keyword1, "\n")] = 0;

    printf("Введите второе ключевое слово : ");
    fgets(keyword2, sizeof(keyword2), stdin);
    keyword2[strcspn(keyword2, "\n")] = 0;

    createMatrix(keyword1, matrix1);
    createMatrix(keyword2, matrix2);

    printf("\n");
    printMatrix(matrix1, "Первая матрица");
    printMatrix(matrix2, "Вторая матрица");

    printf("\nВведите текст для шифрования: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    encrypt(input, matrix1, matrix2, ciphertext, des);

    printf("\n");
    printf("РЕЗУЛЬТАТЫ ШИФРОВАНИЯ:\n");
    printf("  Исходный текст: %s\n", input);
    printf("  Зашифрованный текст: %s\n", ciphertext);


    printf("\nВведите текст для дешифрования: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;
    decrypt(input, matrix1, matrix2, decryptedtext, des);

    printf("\n");
    printf("РЕЗУЛЬТАТЫ ДЕШИФРОВАНИЯ:\n");
    printf("  Зашифрованный текст: %s\n", input);
    printf("  Расшифрованный текст: %s\n", decryptedtext);

    return 0;
}
