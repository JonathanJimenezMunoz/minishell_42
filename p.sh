#!/bin/bash

# Comprobar que el env y el exit funcionan
# Comprobar que imprime file4
./minishell <<EOF
< file3 << here_doc cat
file4
here_doc
EOF
