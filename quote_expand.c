#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct s_env
{
    char            *variable_name;
    char            *value;
    int             exit_code;
    bool            exit_status; 
    struct s_env    *next;
}                    t_env;

int isquote(char c)
{
    return (c == '`' || c == '\'' || c == '\"');
}
char    *dequotencpy(int start, int end, char *s)
{
    int        i;
    int        j;
    char    *dest;
    char    in_quote;

    i = -1;
    j = 0;
    in_quote = '\0';
    dest = malloc(sizeof(char) * (end - start + 1));
    while (++i < (end - start) && s[start + i])
    {
        // if(in_quote=='\"')
        
        if (in_quote != '\0' && s[start + i] == in_quote)
            in_quote = '\0';
        else if (in_quote == '\0' && isquote(s[start + i]))
            in_quote = s[start + i];
        else
            dest[j++] = s[start + i];
    }
    dest[j] = '\0';
    return (dest);
}

int main() {
  t_env env[4];
  seg[0] = (char *)malloc(sizeof(char) * 28);
  seg[0] = "l $f tst $t";
  seg[1] = (char *)malloc(sizeof(char) * 14);
  seg[1] = "g \"$Cfiles\"";
  seg[2] = (char *)malloc(sizeof(char) * 22);
  seg[2] = "s \'no $expand test\'";
  seg[3] = NULL;  
  char *input=strdup("ls\"ts $v \'exp\'\"cmd");
  char *res;
  
  
  res=dequotencpy(0,strlen(input),input);
  
  
  return 0;
}
