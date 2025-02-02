#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
typedef struct s_redir
{
    int type;
    char *filename;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char **var;
    char *command;
    char **arg;
    char *flag;
    int arg_number;
    char *filename;
    t_redir *redirections;
    struct s_cmd *next;
} t_cmd;

t_cmd *struct_create_list()
{
    t_cmd *new_cmd;

    new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    new_cmd->command = NULL;
    new_cmd->arg = NULL;
    new_cmd->flag = NULL;
    new_cmd->arg_number = 0;
    new_cmd->filename = NULL;
    new_cmd->redirections = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}

void struct_addback_list(t_cmd **lst, t_cmd *new)
{
    t_cmd *temp;

    if (!new || !lst)
        return;
    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    temp = *lst;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new;
}

t_cmd *lexical_analysis()
{
    t_cmd *cmd = NULL;

    if (!cmd)
    {
        cmd = struct_create_list();
        cmd->command = "ls";
    }
    else
    {
        = struct_create_list();
        new->command = "grep";
        struct_addback_list(&cmd, new);
    }
    return (cmd);
}

int main()
{
    t_cmd *cmd = NULL;
    cmd = lexical_analysis();
    return (0);
}