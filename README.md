# Pre-requisitos para compilar
- `conio.h` (WINDOWS)
- `ncruses.h` (LINUX)

# Comandos
- `make run` → executa;
- `make dev` → compila e executa;
- `make compile` → compila.

# Valgrind
Se você tiver instalado `valgrind`, uma biblioteca para detectar vazamento de memória, deixei um comando pronto para ela:

- `make valgrind` → executa, compila e gera um relatório `valgrind.txt`. 

# Astronuatas predefinidos
Como desta vez não vão ter dados persistentes, testar esse sistema na memória é bem ruim. Então deixei `seeded` como parametro para ser passado nos comandos: `run`, `dev` e `valgrind`. Mas isso só criará astronautas, não voos!

Ex: `make dev seeded`

# Observações
- Só realizei testes completos no `Ubuntu`;
- Usei minha própria implementação de tipo genêrico `List<Type>`;
- Passei raiva removendo vazamentos de memória com o `valgrind`;
- Passei raiva testando, acho que por mais de `3 horas`;
- Mas `consegui`.

# Relatório de memória do último teste
```log
==93570== HEAP SUMMARY:
==93570==     in use at exit: 0 bytes in 0 blocks
==93570==   total heap usage: 10,447 allocs, 10,447 frees, 191,332 bytes allocated
==93570== 
==93570== All heap blocks were freed -- no leaks are possible
==93570== 
==93570== For lists of detected and suppressed errors, rerun with: -s
==93570== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```