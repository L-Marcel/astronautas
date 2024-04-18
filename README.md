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
- Usei minha própria implementação de tipo genêrico `List<Type`;
- Passei raiva removendo vazamentos de memória com o valgrind;
- Passei raiva testando.