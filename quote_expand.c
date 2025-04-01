#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void    free_split(char **args)
{
    int    i;

    i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    if (args != NULL)
        free(args);
}

int isquote(char c)
{
    return (c == '`' || c == '\'' || c == '\"');
}

char    *ft_strjoin(char *s1, char *s2, size_t next)
{
    size_t    s1_len;
    size_t    s2_len;
    size_t    i;
    char    *join;

    s1_len = strlen(s1);
    s2_len = strlen(s2);
    join = (char *)malloc((s1_len + s2_len + 1)+next);
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
    join[i]='\0';
    return (join);
}

char **expansion(char **seg)
{
  free(seg);
  seg=malloc(sizeof(char*)*2);
  seg[0]=strdup("test ~/fbi/");
  seg[1]=NULL;
  return (seg);
}

int expansion_quotes(int index,char *s,char **dest)
{
  char  quotes;
  char  *prev;
  char  *next;
  char  **quoted_str;
  
  
  quotes=s[index++];
  s+=index;
  next=strdup(s);
  index=0;
  
  while(next[index]!=quotes)
    index++;
  
  
  quoted_str=malloc(sizeof(char*)*2);
  quoted_str[0]=strndup(s,index);
  quoted_str[1]=NULL;
  
  quoted_str=expansion(quoted_str);
  prev=strdup(*dest);
  
  free(*dest);
  *dest=ft_strjoin(prev,quoted_str[0],strlen(next+index+1));

  free_split(quoted_str);
  free(next);
  free(prev);
  
  return (index);
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
        if(in_quote=='\"')
        {
          dest[j]='\0'; 
          i+=expansion_quotes((start+i)-1,s,&dest);
          j=strlen(dest);
        }
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
  char *input=strdup("ls\"ts 'tst' $v\"cmd test");
  char *res;
  
  
  res=dequotencpy(0,strlen(input),input);
  
  
  return 0;
}