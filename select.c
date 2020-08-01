#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {

    fd_set rfds;
    struct timeval tv;
    int retval;

    /* stdin (fd 0) を監視し、入力があった場合に表示する。*/
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    /* 5 秒間監視する。*/
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    retval = select(1, &rfds, NULL, NULL, &tv);
    /* この時点での tv の値を信頼してはならない。*/

    if (retval == -1) {
        perror("select()");
    } else if (retval) {
        printf("今、データが取得できました。\n");

        /* ファイルディスクリプターの0、つまり標準入力に変化があったかをFD_ISSETで検査する。
            ※実際はバッファリングされているので、ENTERキーを押すまで停まっている
         */
        int ret = FD_ISSET(0, &rfds);
        if (ret != 0) {
            /* ファイルディスクリプターの0、つまり標準入力に変化があった。
             * readしてみる。
             */
            char s[32];
            ssize_t read_len = read(0, s, sizeof(s) - 1);
            if (read_len != -1) {
                s[read_len] = '\0';
                printf("s=[%s]\n", s);
            }
        }
    } else {
        printf("5 秒以内にデータが入力されませんでした。\n");
    }

    return 0;
}