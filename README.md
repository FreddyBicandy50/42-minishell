ls -FLAG1 "Arg1 quoted test" -FLAG2 arg2"MIXED QUOTED" -Flag3 ARG3 > filename -FLAG | Grep ARG1"arg" | sort -FLAG >> file
//TODO 
    //Redirections , filenames, flags
    //Multi redirecitons
    //here_doc
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
FIXED: STRDUP and > and implemented unmatched quotes, ADDED LOGS,