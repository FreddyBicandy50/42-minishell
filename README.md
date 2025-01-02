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