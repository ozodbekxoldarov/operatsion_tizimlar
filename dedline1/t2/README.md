## 2-topshiriq — katta sonlar yig'indisi

gcc katta_sonlar.c -o katta_sonlar
./katta_sonlar

# Valgrind tekshiruvi
valgrind --leak-check=full ./katta_sonlar
