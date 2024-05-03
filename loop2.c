#include <stdio.h>

int sum_up_to_num() {
    int total = 0;
    int i, num;
    printf("0부터 num까지의 덧셈 num은?");
    scanf("%d", &num);

    for (i = 0; i < num + 1; i++)
        total += i;

    printf("0부터 %d까지 덧셈결과: %d \n", num, total);

    return 0;
}

void print_hello() {
    int num; // 초기식
    //num < 3: 조건식 
    // num++; 증감식 

    for (num = 0; num < 3; num++) {
        printf("Hallo \n");
    }
}


//구구단 이중 for 문 
void prod(){
    int cur, is; 

    for(cur=2; cur<10;cur ++){
        for(is =1; is <10; is++){
            printf("%d*%d=%d \n", cur, is, cur*is);
        printf("\n");    
        }
    }
}

int main() {
    sum_up_to_num();
    print_hello();
    prod();
    return 0;
}
