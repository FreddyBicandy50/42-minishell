#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void free_split(char **args)
{
  int i;

  i = 0;
  while (args[i] != NULL)
  {
    free(args[i]);
    i++;
  }
  if (args != NULL)
    free(args);
}

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

char *skip_inside(char quote, char *s)
{
  while (*s != '\0' && *s != quote)
    s++;
  if (*s == '\0')
    return (NULL);
  return (s);
}

char *skip_to_c(char *s, char c)
{
  while (*s != '\0' && *s != c)
    s++;
  return (s);
}

char *get_val(char *s)
{
  if (*(s + 1) == 'f')
    return strdup("tls tst $t");
  return strdup("tls tst tt");
}

int main()
{
  char *seg[4];
  seg[0] = (char *)malloc(sizeof(char) * 28);
  seg[0] = "l $f tst $t";
  seg[1] = (char *)malloc(sizeof(char) * 14);
  seg[1] = "g \"$Cfiles\"";
  seg[2] = (char *)malloc(sizeof(char) * 22);
  seg[2] = "s \'no $expand test\'";
  seg[3] = NULL;

  int i;
  char **Exp_seg;
  char *prev;
  char *next;
  char *s;
  char *value;

  s = strdup(" ");
  prev = NULL;
  i = 0;

  while (seg[i])
    i++;
  Exp_seg = malloc(sizeof(char *) * i);
  i = 0;
  while (seg[i])
  {
    next = strdup(seg[i]);
    while (s && i == 0)
    {
      free(s);
      s = strdup(skip_to_c(next, '$'));
      if (*s == '\0' || s == NULL)
        break;
      // int len=skip_to_c(next,'$') - next;
      int len = 8;
      if (*(s + 1) == 'f')
        len = 2;
      value = get_val(s);
      prev = strndup(next, len);
      free(next);
      next = ft_strjoin(prev, value);
      free(prev);
      free(value);
    }
    Exp_seg[i++] = strdup(next);
    free(next);
  }
  if (next)
    free(next);
  if (s)
    free(s);
  free_split(seg);
}