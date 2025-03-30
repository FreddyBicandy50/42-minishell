#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
    char            *variable_name;
    char            *value;
}    t_env;

char *ft_strjoin(char *s1, char *s2)
{
  size_t s1_len;
  size_t s2_len;
  size_t i;
  char *join;

  s1_len = strlen(s1);
  s2_len = strlen(s2);
  join = (char *)malloc(s1_len + s2_len + 1);
  if (!join || !s1 || !s2)
    return (NULL);
  i = 0;
  while (*s1 != '\0')
  {
    join[i] = *s1;
    s1++;
    i++;
  }
  while (*s2 != '\0')
  {
    join[i] = *s2;
    s2++;
    i++;
  }
  join[i] = '\0';
  return (join);
}

int ft_isalnum(int c)
{
    return ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9'));
}

char *get_env_value(t_env *env[3], char *variable_key)
{
  int i=0;
    while (i<3)
    {
        if (strcmp(env[i]->variable_name, variable_key) == 0)
            return (strdup(env[i]->value));
        i++;
    }
    return (NULL);
}

char *expand(t_env *envp[3],char *key)
{
  char *expanded;
  char *rawvar;
  char *value;
  int   i;
  
  if(*key!='$')
    return NULL;
  key++;
  if(*key>='0' && *key<='9')
  {
    key++;
    return (strdup(key));
  }
  
  i=0;
  while(key[i]!='\0' && ft_isalnum(key[i]))
    i++;
  rawvar=strndup(key,i);
  value=get_env_value(envp,rawvar);
  key+=i;
  expanded=ft_strjoin(value,key);
  free(value);
  free(rawvar);

  return (expanded);
}

int main(void)
{
    t_env *envp[3];
    envp[0] = (t_env *)malloc(sizeof(t_env));
    envp[0]->variable_name = (char *)malloc(sizeof(char) * 5);
    strcpy(envp[0]->variable_name, "HOME");
    envp[0]->value = (char *)malloc(sizeof(char) * 16);
    strcpy(envp[0]->value,"/fbi/"); 
    
    envp[1] = (t_env *)malloc(sizeof(t_env));
    envp[1]->variable_name = (char *)malloc(sizeof(char) * 4);
    strcpy(envp[1]->variable_name, "VAR");
    envp[1]->value = (char *)malloc(sizeof(char) * 8);
    strcpy(envp[1]->value,"testing"); 
    
    
    envp[2] = (t_env *)malloc(sizeof(t_env));
    envp[2]->variable_name = (char *)malloc(sizeof(char) * 5);
    strcpy(envp[2]->variable_name, "TERM");
    envp[2]->value = (char *)malloc(sizeof(char) * 15);
    strcpy(envp[2]->value,"xterm-256color"); 
    
    
    char *key=strdup("$1var$HOME$TERM");
    char *prev=strdup("ls -la ");
    char *value=expand(envp,key);
   
    free(key);
    key=strdup("$HOME$TERM");
    free(prev);
    prev=strdup("ls -la var");
    free(value);
    value=expand(envp,key);
    
    
    char *res=ft_strjoin(prev,value);
    free(value);
    free(key);
    free(prev);
    
    free(envp[0]->variable_name);
    free(envp[0]->value);
    free(envp[0]);
        
    free(envp[1]->variable_name);
    free(envp[1]->value);
    free(envp[1]);
    
    free(envp[2]->variable_name);
    free(envp[2]->value);
    free(envp[2]);
    return 0;
}