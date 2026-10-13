# os_t1 Xoldarov Ozodbek

## 1-topshiriq, A qism — kompilyatsiya bosqichlari

gcc -E hello.c -o hello.i
gcc -S hello.i -o hello.s
gcc -c hello.s -o hello.o
gcc hello.o -o hello
./hello

## 1-topshiriq, B qism — kalkulyatorlar

# 1-masala (oddiy kalkulyator)
gcc kalkulyator1.c -o kalkulyator1
./kalkulyator1

# 2-masala (funksiya pointerli kalkulyator)
gcc kalkulyator2.c -o kalkulyator2 -lm
./kalkulyator2
