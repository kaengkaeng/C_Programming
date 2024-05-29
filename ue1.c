#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/*
    Diese Funktion kopiert den Filedeskriptor srcfd nach destfd
*/
int copy(int srcfd, int destfd) {
    char buffer[1024]; // Buffer-Array
    ssize_t nread; // 읽은 데이터의 크기
    ssize_t nwritten; // 작성한 데이터의 총 크기
    ssize_t nwritten_temp; // 각 반복에서 작성한 데이터의 크기

    while (1) {
        nread = read(srcfd, buffer, sizeof(buffer)); // 소스 파일에서 데이터를 읽어 buffer에 저장, 최대 1024 바이트
        if (nread == -1) { // 읽기 실패 시
            return -1; // -1 반환, 함수 종료
        }

        if (nread == 0) { // 파일의 끝에 도달했을 때
            return 0; // 0 반환, 함수 종료
        }

        nwritten = 0;
        while (nwritten < nread) { // 읽은 데이터를 모두 쓸 때까지 반복
            nwritten_temp = write(destfd, buffer + nwritten, nread - nwritten); // 목표 파일에 데이터를 씀
            if (nwritten_temp == -1) { // 쓰기 실패 시
                return -1; // -1 반환, 함수 종료
            }
            nwritten += nwritten_temp; // 작성한 데이터의 총 크기를 갱신
        }
    }
}

int main(int argc, char *argv[]) {
    int error; // 오류 여부를 저장하는 변수, 0이면 오류 없음
    int srcfd; // 소스 파일의 파일 디스크립터
    int ret_main = 0; // main 함수의 반환값, 기본값 0
    char errmsg[] = "Copy Error"; // 오류 메시지

    if (argc == 1) { // 인자가 없을 때, 표준 입력 사용
        error = copy(STDIN_FILENO, STDOUT_FILENO); // 표준 입력(STDIN)과 표준 출력(STDOUT)을 사용하여 복사
        if (error == -1) { // 복사 오류 발생 시
            perror(errmsg); // 오류 메시지 출력
        }
        return error; // 오류 코드 반환
    } else { // 하나 이상의 인자가 있을 때, 파일을 사용
        for (int i = 1; i < argc; i++) { // 각 인자를 처리
            srcfd = open(argv[i], O_RDONLY); // 읽기 전용으로 파일을 엶
            if (srcfd == -1) { // 파일 열기 실패 시
                perror(argv[i]); // 오류 메시지 출력
                ret_main = 1; // main 함수 반환값을 1로 설정 (오류 발생)
                continue; // 다음 파일로 계속 진행
            }

            error = copy(srcfd, STDOUT_FILENO); // 소스 파일에서 표준 출력으로 복사
            if (error == -1) { // 복사 오류 발생 시
                perror(argv[i]); // 오류 메시지 출력
                ret_main = 1; // main 함수 반환값을 1로 설정 (오류 발생)
                close(srcfd); // 파일 디스크립터 닫기
                break; // 루프 종료
            }

            if (close(srcfd) == -1) { // 파일 디스크립터 닫기 오류 발생 시
                perror(argv[i]); // 오류 메시지 출력
                ret_main = 1; // main 함수 반환값을 1로 설정 (오류 발생)
                break; // 루프 종료
            }
        }
    }

    return ret_main; // main 함수의 반환값 반환
}
