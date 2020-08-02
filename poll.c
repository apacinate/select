#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>
#define TIMEOUT 5 /* poll timeout, in seconds */ //pollタイムアウト秒数
int main (void)
{
struct pollfd fds[2];
int ret;
/* watch stdin for input */ //stdinからの入力を調べる
fds[0].fd = STDIN_FILENO;
fds[0].events = POLLIN;
/* watch stdout for ability to write (almost always true) */ //stdoutが書き込み可能かを調べ
fds[1].fd = STDOUT_FILENO; る（ほぼ常に真）
fds[1].events = POLLOUT;
/* All set, block! */ //準備完了、待ち合わせ開始!
ret = poll (fds, 2, TIMEOUT * 1000);
if (ret == -1) {

perror ("poll");
return 1;
}
if (!ret) {
printf ("%d seconds elapsed.\n", TIMEOUT);
return 0;
}
if (fds[0].revents & POLLIN)
printf ("stdin is readable\n");
if (fds[1].revents & POLLOUT)
printf ("stdout is writable\n");
return 0;
}