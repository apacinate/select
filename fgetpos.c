/* header files */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* main */
int main(void) {
    FILE *fp;
    fpos_t pos_first, pos_writed;
    char *filename = "fgetpos.c";

    /* ファイルのオープン */
    if ((fp = fopen(filename, "w+")) == NULL) {
        fprintf(stderr, "%sのオープンに失敗: %s\n",
                filename, strerror(errno));
        return EXIT_FAILURE;
    }

    /* file position indicator の値を取得 */
    fgetpos(fp, &pos_first);
    printf("file position indicator: %ld\n", (long)pos_first);

    /* ファイルに Snoopy を書き込む */
    fputs("Snoopy",fp);

    /* Snoopy 書込み後の file position indicator の値を取得 */
    fgetpos(fp, &pos_writed);
    printf("file position indicator: %ld\n", (long)pos_writed);

    /* file position indicator の値を元に戻す */
    if (fsetpos(fp, &pos_first) == 0) {
        printf("元に戻した file position indicator: %ld\n", (long)pos_first);
    } else {
        fprintf(stderr, "file position indicator の設定に失敗.\n");
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}