// TODO HERE_DOC 

# Apr 6/2025

   i want to handle SHLVL in env //shell level;
   
# Apr 3/2025
   
   fixed invalid read / seg faul in expanding invalid variable at the command tokenization level

# Apr 2/2025
   
   fixed norm
   fixed expansion and did it in new way much better
   
# Mar 29/2025
   added  $_ variable case
   doing the double/single quote thingy
   
# Mar 29/2025

   implemented expansion with norm
   added hepler_expander
   fixed norm errors
   fixed exit codes 

# Mar 16/2025
   
   in main.c => 
               added global variable (g_signal)
               in tokenization did save_env
   int minishell.h =>
               added struct of env
               added expension function
               save_envp

# Mar 10/2025
   
   fixed redirection error while sending empty value after redirection

# Feb 22/2025
   
   more consise logs
   Fixed <> causing memorie leaks <fbicandy>
   new struct implementation

# Feb 15/2025

   done merging

# Feb 5/2025

   done redirections with some pending fixes

//TODO 

    //Redirections , filenames, flags
    //Multi redirecitons
    //here_doc

# Feb 2/2025

   done redirections with some pending fixes

# Feb 1/2025

   fixed the cmd list appending to the first node only

# Feb 1/2025

   orginized all files

# Jan 31/2025

   Done commends, flags,args

# Jan 29/2025

   Comments rethinking...
   functions renaming...
   code refining...
   
# Jan 27/2025

    BUG FIXED 
    we have an error in get_next_command 
        case command quote and args

### TODO::catch flags after the redirections

# Jan 2/2025

    BUG FIXED 
    we have an error in get_next_command 
        case command quote and args
        "l"s "Fredy"
        out ls F

## Dec/30/2024

FIXED: 

    dequote and copy in get next flags (GNF)
    Fix the condition of spacing example    ls "-la her"
            dont send i + 2 find another solution also keeps spaces

FIXED: 
    dequote and copy in get_next_command
    memory leaks

## Dec/29/2024
   
   FIXED: STRDUP and > and implemented unmatched quotes, ADDED LOGS,Builtin
