#include "minitalk.h"

void receive_signal(int signal, siginfo_t *info, void *context)
{
    static unsigned char byte = 0;
    static int bit_count = 7;

    (void)context;
    byte <<= 1;
    bit_count--;
    if (signal == SIGUSR1)
        byte |= 1;
    if (bit_count < 0)
    {
        if (byte == '\0')
            kill(info->si_pid, SIGUSR2);
        else
        {
            ft_printf("%c", byte);
            kill(info->si_pid, SIGUSR1);
        }
        byte = 0; 
        bit_count = 7;
    }
    else
        kill(info->si_pid, SIGUSR1);
}

int main(void)
{
    int                 pid;
    struct sigaction    sa;

    pid = getpid();
    ft_printf("Server PID is: %d\n", pid);
    sa.sa_sigaction = receive_signal;
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
}
