ls -FLAG1 "Arg1 quoted test" -FLAG2 arg2"MIXED QUOTED" -Flag3 ARG3 > filename -FLAG | Grep ARG1"arg" | sort -FLAG >> file
//TODO fix the flags 
	// Make sure you recieve the cmd well
    // copy the flags 
    // Jump to arguments and do the same
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