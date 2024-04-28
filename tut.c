#include <stdio.h>

/*29042024, tut 2*/ 
int main(void) {
    char op;
    int num1, num2;
    float result = 0;

    printf("Was moechten Sie berechnen? Waehlen Sie '+,-,*,/' ");
    scanf(" %c", &op); // 공백을 추가하여 버퍼를 비웁니다.

    printf("Schreiben sie zwei Zahlen: ");
    scanf("%d %d", &num1, &num2); // 쉼표를 제거합니다.

    switch (op) {
        case '+':
            result = num1 + num2;
            printf("Summe: %f\n", result); // 결과를 출력할 때 %f를 사용합니다.
            break;
        case '-':
            result = num1 - num2;
            printf("Differenz: %f\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Produkt: %f\n", result);
            break;
        case '/':
            if (num2 != 0) {
                result = (float)num1 / num2; // 나눗셈 결과를 float로 변환합니다.
                printf("Quotient: %f\n", result);
            } else {
                printf("Error: Division by zero.\n");
            }
            break;
        default:
            printf("Ungueltige Operation.\n");
    }

    return 0;
}
