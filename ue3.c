#define _POSIX_C_SOURCE 199309L // POSIX 타이머 함수를 사용하기 위한 매크로

#include <stdlib.h> // 일반적인 유틸리티 함수를 제공하는 헤더 파일
#include <stdio.h> // 표준 입출력 함수를 제공하는 헤더 파일
#include <unistd.h> // POSIX 시스템 호출 및 상수를 제공하는 헤더 파일
#include <signal.h> // 시그널 관련 함수와 매크로를 제공하는 헤더 파일
#include <time.h> // 시간 관련 함수를 제공하는 헤더 파일

void my_signal_handler(int my_signal_number)
{
    if(my_signal_number == 2) // SIGINT에 대한 신호 핸들러
    {
        char msg[] = "Böse Nachricht mit SIGINT\n"; // SIGINT에 대한 메시지
        if (write(1, msg, 28) == -1) // write 함수 호출 오류 확인
        {
            perror("Error writing to stdout"); // 오류 메시지 출력
        }
    }
    else // SIGTERM에 대한 신호 핸들러
    {
        char msg[] = "Böse Nachricht mit SIGTERM\n"; // SIGTERM에 대한 메시지
        if (write(1, msg, 28) == -1) // write 함수 호출 오류 확인
        {
            perror("Error writing to stdout"); // 오류 메시지 출력
        }
    }
}

int main(void)
{
    struct sigaction sa_register = { // 시그널 핸들러를 등록하기 위한 구조체 초기화
        .sa_handler = &my_signal_handler, // 핸들러 함수 지정
        .sa_flags = 0, // 플래그 설정
    };
    sigemptyset(&sa_register.sa_mask); // 시그널 집합 초기화
    
    int err = sigaction(SIGINT, &sa_register, NULL); // SIGINT에 대한 시그널 핸들러 등록
    if (err == -1) // 오류 처리
    {
        perror("Error registering signal handler for SIGINT"); // 오류 메시지 출력
    }

    err = sigaction(SIGTERM, &sa_register, NULL); // SIGTERM에 대한 시그널 핸들러 등록
    if (err == -1) // 오류 처리
    {
        perror("Error registering signal handler for SIGTERM"); // 오류 메시지 출력
    }
    
    int my_pid = getpid(); // 현재 프로세스의 PID 획득
    if (my_pid == -1) // 오류 처리
    {
        perror("Error getting PID"); // 오류 메시지 출력
    }
    printf("%d\n", my_pid); // PID 출력
    
    struct timespec remaining, request = {2, 500}; // nanosleep 함수에 사용할 시간 지정
    int response; // nanosleep 함수의 반환값을 저장할 변수
    
    while(1)
    {
        response = nanosleep(&request, &remaining); // 지정된 시간만큼 스레드를 재우고 재움 상태에서 깨어난 경우 남은 시간을 remaining에 저장
        if (response == -1) // 오류 처리
        {
            perror("Error during nanosleep"); // 오류 메시지 출력
        }
        else // 정상적인 반환일 경우
        {
            printf("Endlosschleife\n"); // 무한 루프 메시지 출력
        }
    }
}
