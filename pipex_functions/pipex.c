
#include "../Includes/pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_arg arg;

    argc -= 1;
    arg.ac = argc;
    arg.av = argv;
    arg.env = envp;
    if (parse_pipex(arg) == false)
        return (1);
    return (0);
}
