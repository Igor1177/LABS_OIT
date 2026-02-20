#include <stdio.h>
#include <locale.h>
#include <string.h>

int main() {
    setlocale(LC_ALL, "Russian");

    float number = -763.200345f;
    printf("Исходное число: %f\n\n", number);

    printf("1. Переводим целую часть в двоичную:\n");
    int num = 763;
    char num_2cc[100] = "";
    int idx = 0;
    int temp = num;

    while (temp > 0) {
        num_2cc[idx] = (temp % 2) + '0';
        temp = temp / 2;
        idx++;
    }
    for (int i = 0; i < idx / 2; i++) {
        char t = num_2cc[i];
        num_2cc[i] = num_2cc[idx - 1 - i];
        num_2cc[idx - 1 - i] = t;
    }

    printf("   763 = %s\n\n", num_2cc);

    printf("   Переводим дробную часть в двоичную:\n");
    double dr_num = 0.200345;
    char dr_num_2cc[100] = "";
    idx = 0;

    for (int i = 0; i < 30; i++) {
        dr_num = dr_num * 2;
        if (dr_num >= 1.0) {
            dr_num_2cc[idx] = '1';
            dr_num = dr_num - 1.0;
        }
        else {
            dr_num_2cc[idx] = '0';
        }
        idx++;
    }

    printf("   0.200345 = 0.%s\n\n", dr_num_2cc);

    printf("   Полное двоичное представление:\n");
    printf("   %s.%s\n\n", num_2cc, dr_num_2cc);

    printf("2. Находим экспоненту (для 4-байтного формата):\n");

    int exp = 0;
    int int_len = strlen(num_2cc);

    printf("   Длина целой части: %d\n", int_len);

    exp = int_len - 1;
    printf("   Экспонента: %d\n", exp);
    printf("   Экспонента со смещением: %d + 127 = %d\n", exp, exp + 127);

    printf("\n3. Нормализованная форма:\n");
    printf("   1.");


    for (int i = 1; i < int_len; i++) {
        printf("%c", num_2cc[i]);
    }
    printf("%s", dr_num_2cc);
    printf(" * 2^%d\n\n", exp);

    printf("\n4. Мантисса (23 бита для 4-байтного формата):\n");

    char mantissa[24] = "";
    int m_idx = 0;


    for (int i = 1; i < int_len && m_idx < 23; i++) {
        mantissa[m_idx] = num_2cc[i];
        m_idx++;
    }

    for (int i = 0; i < 30 && m_idx < 23; i++) {
        mantissa[m_idx] = dr_num_2cc[i];
        m_idx++;
    }

    while (m_idx < 23) {
        mantissa[m_idx] = '0';
        m_idx++;
    }
    mantissa[23] = '\0';

    printf("   %s\n", mantissa);
    printf("   (23 бита)\n");

    printf("\n5. Итоговое представление числа (4 байта):\n");
    printf("   1");

    for (int i = 7; i >= 0; i--) {
        printf("%d", (exp + 127 >> i) & 1);
    }


    printf("%s", mantissa);

    printf("\n   1(знак) + 8(экспонента) + 23(мантисса) = 32 бита = 4 байта\n");


    return 0;
}
