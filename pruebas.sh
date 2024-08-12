#!/bin/bash

# Ejecutar minishell y pasarle la línea de comandos
# Comandos varios con pipes
./minishell <<EOF
<p5 head -n 5 | tail -n 3 >adios | echo "hola que tal" >>verdades | <verdades cat
EOF

# Sin existir file 1 ni file 2. Comprobar que se redirige al file 2 el ls, pero se crean ambos
./minishell <<EOF
ls | cat -e > file1 >> file2
EOF

# Sin existir file 3 ni file 4. Comprobar que se redirige al file 4 el ls, pero se crean ambos
./minishell <<EOF
ls | cat -e >> file3 > file4
EOF

# Comprobar que imprime lo de file2
./minishell <<EOF
< file1 < file2 cat
EOF

# Comprobar que imprime file4
./minishell <<EOF
< file3 << here_doc cat
file4
here_doc
EOF

# Prueba de comandos varios
./minishell <<EOF
cat < "Makefile" | grep libft > outfile | wc -l < outfile
EOF

# Comprobar que la minishell sigue activa y que solo se imprime una vez el error el que hay una pipe vacia
./minishell <<EOF
cat < "Makefile" | | | grep libft > outfile | wc -l < outfile
EOF

# No hace nada
./minishell <<EOF
<p1
EOF

# No hace nada
./minishell <<EOF
>p3
EOF

# No hace nada
./minishell <<EOF
<p1 | >p3
EOF

# No hace nada
./minishell <<EOF
<p1 cat | >p3
EOF

# Imprime p1
./minishell <<EOF
<p1 cat
EOF

# No hace nada
./minishell <<EOF
<p1 | cat | >p3
EOF

# Error > |
./minishell <<EOF
<p1 cat >p3 > | echo hola >p3
EOF

# Error > > >
./minishell <<EOF
<p1 cat >p3 > > >  | echo hola >p3
EOF

# Error por empezar en |
./minishell <<EOF
| <p1 cat >p3
EOF

# Error por terminar en |
./minishell <<EOF
<p1 cat >p3 |
EOF

# Prueba de un comando con muchos argumentos
./minishell <<EOF
find . -type f -name "*.txt" | wc -l
EOF

# No necesitamos interpretar * pero no peta
./minishell <<EOF
cat p*
EOF

# No necesitamos interpretar \ pero no peta
./minishell <<EOF
cat \p1
EOF

# No hace nada
./minishell <<EOF

EOF

# Crea variable de entorno AGUA=p4 y la imprime
./minishell <<EOF
export AGUA=p4 | echo $AGUA
EOF

./minishell <<EOF
echo $AGUA | exit
EOF

./minishell <<EOF
cat <$AGU
EOF

./minishell <<EOF
cat <$AGUA
EOF

# Comprobar que no sale error: dup2: Bad file descriptor.
./minishell <<EOF
cat <p4 | head -2
EOF

# Comprobar que no hay Segmentation fault
./minishell <<EOF
export david = aaa
EOF

#EL INFAME AWK
./minishell <<EOF
awk 'END {print NR}' p4
EOF

#Bash lo trara como "'cat' < 'p3'", nosotros como ''cat" < "p3''
./minishell <<EOF
""cat" < "p3""
EOF

#Bash lo trata como 'cat' < "p3", igual que nosotros.
./minishell <<EOF
"cat" < "p3"
EOF

rm -f file1 file2 file3 file4
