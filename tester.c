#include <stdio.h>
#include <string.h>
#include <unistd.h>



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
  return strdup("Tools Test");
}

int main() {
char *seg[4];
seg[0]=(char *) malloc(sizeof(char) * 28);
seg[0]="l $folder";
seg[1]=(char *) malloc(sizeof(char) * 14);
seg[1]="g \"$Cfiles\"";
seg[2]=(char *) malloc(sizeof(char) * 22);
seg[2]="s \'no $expand test\'";
seg[3]=NULL;
  
  int j;
  int i;
  char **Exp_seg;
  char *prev;
  char *next;
  char *s;
  char *value;
  
  s=strdup(" ");
  prev=NULL;
  i=0;
  
  while(seg[i])
    i++;
  Exp_seg=malloc(sizeof(char *) * i);
  i=0;
  while(seg[i])
  {
    next=strdup(seg[i]);
    while(*s!='\0' && s!=NULL)
    {
      free(s);
      s=strdup(skip_to_c(next,'$'));
      if(*s=='\0' || *s==NULL) continue;
      value=get_val(s);
      printf("%d",skip_to_c(next,'$') - next);
      //CONTINUE HERE
      // prev=strndup(next,(next - s));
      // free(next);
      // next=strcat(next,prev);
    }
    
    free(next);
    i++;
  }
}