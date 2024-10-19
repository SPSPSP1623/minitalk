#include "minitalk.h"

int bit_received;

void ft_send_char(int pid, char character)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        bit_received = 0;
        if ((character >> bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        bit--;
        while (bit_received == 0)
            usleep(42);
    }
}

void ft_send_string(int pid, char *string)
{
    int i = 0;

    while (string[i] != '\0')
    {
        ft_send_char(pid, string[i]);
        i++;
    }
    ft_send_char(pid, '\0');
}

void server_signal(int signal)
{
    if (signal == SIGUSR1)
        bit_received = 1;
    else if (signal == SIGUSR2)
    {
        ft_printf("\nString received! :)\n");
        exit(EXIT_SUCCESS);
    }
}

void ft_error(int argc)
{
    if (argc != 3)
    {
        ft_printf("\n\t/!\\ERROR/!\\\n\nUsage: ./client (SERVER_PID) (STRING)\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    int pid;

    ft_error(argc);

    pid = ft_atoi(argv[1]);
    signal(SIGUSR1, &server_signal);
    signal(SIGUSR2, &server_signal);
    ft_send_string(pid, argv[2]);
}
