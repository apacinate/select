#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
int main (void)
{
pid_t pid;
int i;
/* create new process */ //新規プロセス作成
pid = fork ();
if (pid == -1)
return -1;
else if (pid != 0)
exit (EXIT_SUCCESS);
/* create new session and process group */
if (setsid () == -1)
return -1;
/* set the working directory to the root directory */
if (chdir ("/") == -1)
return -1;
/* close all open files--NR_OPEN is overkill, but works */
for (i = 0; i < INR_OPEN_MAX; i++)
close (i);
/* redirect fd's 0,1,2 to /dev/null */ //fd の0、1、2 を/dev/null とする
open ("/dev/null", O_RDWR); /* stdin */
dup (0); /* stdout */
dup (0); /* stderror */
//セッションとプロセスグループの新規作成
//カレントディレクトリをルートディレクリへ移動
//全ファイルをクローズ。NR_OPEN 個もクローズする必要はないが不都合もない。

/* do its daemon thing... */ //デーモンとしての処理
return 0;
}