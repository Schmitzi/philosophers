#include "philo.h"

int arg_checker(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (*argv[i] == ' ')
            {
                i++;
                continue;
            }
        if (*argv[i] < '0' || *argv[i] > '9')
        {
            return (ft_error("Out of range"), 1);
        }
        i++;
    }
    argv++;
    return (0);
}
