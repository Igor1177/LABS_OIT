#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "ru");
    char a[100], b[100], res[200];
    int i, j, k, carry;
    int temp_res[200] = { 0 };

    printf("Первое число (четверичная система): ");
    scanf("%s", a);
    int len_a = strlen(a);

    for (i = 0; i < len_a; i++)
    {
        if (a[i] < '0' || a[i] > '3')
        {
            printf("Ошибка: число должно содержать только цифры 0-3\n");
            return 1;
        }
    }

    printf("Второе число (четверичная система): ");
    scanf("%s", b);

    int len_b = strlen(b);

    for (i = 0; i < len_b; i++)
    {
        if (b[i] < '0' || b[i] > '3')
        {
            printf("Ошибка: число должно содержать только цифры 0-3\n");
            return 1;
        }
    }

    for (i = len_a - 1; i >= 0; i--)
    {
        carry = 0;
        int digit_a = a[i] - '0';
        int pos1 = len_a - 1 - i;

        for (j = len_b - 1; j >= 0; j--)
        {
            int digit_b = b[j] - '0';
            int pos2 = len_b - 1 - j;

            int product = digit_a * digit_b + carry + temp_res[pos1 + pos2];

            temp_res[pos1 + pos2] = product % 4;
            carry = product / 4;
        }

        if (carry > 0)
        {
            temp_res[pos1 + len_b] += carry;
        }
    }

    int max_pos = len_a + len_b;
    while (max_pos > 0 && temp_res[max_pos] == 0)
    {
        max_pos--;
    }

    int res_pos = 0;
    for (i = max_pos; i >= 0; i--)
    {
        res[res_pos++] = temp_res[i] + '0';
    }
    res[res_pos] = '\0';

    int start = 0;
    while (res[start] == '0' && res[start + 1] != '\0')
    {
        start++;
    }

    printf("Результат умножения: ");
    for (i = start; res[i]; i++)
    {
        printf("%c", res[i]);
    }
    printf(" (четверичная система)\n");

    return 0;
}
