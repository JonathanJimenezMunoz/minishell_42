#!/bin/bash
# valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --log-file=memoria ./minishell 
#{
#    ignore_libreadline_leaks
#    Memcheck:Leak
#    ...
#    obj:*/libreadline.so.*
#}
# Ejecutar minishell y pasarle la línea de comandos
# Comandos varios con pipes
./minishell <<EOF
<p2 head -n 5 | tail -n 3 >adios | echo "hola que tal" >>verdades | <verdades cat
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

# Prueba de comandos varios (Result = 2)
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

# Crea p3
./minishell <<EOF
>p3
EOF

# Crea p4
./minishell <<EOF
<p1 | >p4
EOF

# Crea p5
./minishell <<EOF
<p1 cat | >p5
EOF

# Imprime p1
./minishell <<EOF
<p1 cat
EOF

# Crea p6
./minishell <<EOF
<p1 | cat | >p6
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

# Prueba de un comando con muchos argumentos (Result = 2)
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

# Comprobar que no se ejecuta el primero pero el segundo si ya que existe como cmd (echo, env, pwd)
./minishell <<EOF
export AGUA=p2 | echo $AGUA
EOF

# Comprobar que se ejecuta el primero pero no el segundo, ya que no existe como cmd
./minishell <<EOF
echo $AGUA | exit
EOF

------------------
Probar todos los casos del export 
export agua=1q2321
export 1agua=1q2321
export agua=qqqq
export agua= 1
export agua =sdasd1
export agua = asdasd1
export agua= asdasd1 == qwe3
export
export =
export agua=3 agua2=2
-------------------
# Se ejecutan echo y pwd pero no exit yya que no existe como cmd
./minishell <<EOF
echo $AGUA | pwd >> p8 | cat <p8 > p9 | exit
EOF

# No existe el fichero, ya que la variable de entorno devuelve algo vacio al no existir
./minishell <<EOF
cat <$AGU
EOF

# Comprobar que el cat imprime lo que esta dentro de p2
./minishell <<EOF
export AGUA=p2
cat <$AGUA
EOF

# Comprobar que el echo no imprime nada ya que el unset borro la variable de entorno
./minishell <<EOF
export AGUA=p2
unset AGUA
echo $AGUA
EOF

# Comprobar que el cd y el pwd funcionan
./minishell <<EOF
cd ..
pwd
cd minishell_42
pwd
EOF

# Comprobar que el cd y el pwd funcionan
./minishell <<EOF
cd /home/david/pruebas/minishell
ls
cd
pwd
EOF

# Comprobar que el env y el exit funcionan
./minishell <<EOF
export AGUA=p2
env
exit
EOF

# Comprobar que no sale error: dup2: Bad file descriptor.
./minishell <<EOF
cat < file1 | head -2
EOF

# Comprobar que no hay Segmentation fault
./minishell <<EOF
export david = aaa
EOF

#EL INFAME AWK
./minishell <<EOF
awk 'END {print NR}' p1
EOF

#Bash lo trara como "'cat' < 'p2'", nosotros como ''cat" < "p2''
./minishell <<EOF
""cat" < "p2""
EOF

#Bash lo trata como 'cat' < "p1", igual que nosotros.
./minishell <<EOF
"cat" < "p1"
EOF

#bash: &: command not found
./minishell <<EOF
& @
EOF

#Error: Comillas mal cerradas
./minishell <<EOF
"hola buenas
EOF

./minishell <<EOF
foo
EOF
rm -f file1 file2 file3 file4 adios p3 verdades
