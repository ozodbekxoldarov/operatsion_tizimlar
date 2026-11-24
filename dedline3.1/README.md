# os_t3 Xoldarov Ozodbek

## 3-laboratoriya, 18-variant: belgilar, satrlar va fayllar bilan ishlash

Barcha dasturlar quyidagi buyruq bilan ogohlantirishsiz kompilyatsiya bo'ladi:

gcc -Wall -Wextra -std=c11 v18_m1.c -o v18_m1

## 1-masala: har bir belgini ikki marta takrorlash

Satr o'qiladi va har bir belgi ikki marta yoziladi. Natija uchun xotira
`malloc(2 * strlen(s) + 1)` bilan ajratiladi va oxirida `free` qilinadi.

gcc -Wall -Wextra -std=c11 v18_m1.c -o v18_m1
./v18_m1

Misol: `abc` -> `aabbcc`

## 2-masala: N ta satr ichidan eng uzunini topish

N ta satr dinamik massivga (`char **`) o'qiladi, eng uzun satr topiladi.
Har bir satr va massivning o'zi alohida `free` qilinadi.

gcc -Wall -Wextra -std=c11 v18_m2.c -o v18_m2
./v18_m2

Misol: `olma`, `qovun pishdi`, `nok` -> `qovun pishdi` (12 belgi)

## 3-masala: fayl satrlarini teskari tartibda yozish

`input.txt` faylidagi satrlar `realloc` bilan kengayadigan massivga yuklanadi
va teskari tartibda `reversed_lines.txt` fayliga yoziladi.

gcc -Wall -Wextra -std=c11 v18_m3.c -o v18_m3
./v18_m3

- `input.txt` - kiruvchi fayl (7 qator)
- `reversed_lines.txt` - dastur yaratadigan natija fayli

## Talablar

- `gets` ishlatilmagan, faqat `fgets` (oxiridagi `'\n'` olib tashlanadi)
- `fopen` natijasi NULL ga tekshiriladi, xato `perror` bilan chiqariladi
- har bir ochilgan fayl `fclose` qilinadi
- `malloc` va `realloc` natijasi NULL ga tekshiriladi
- asosiy ish alohida funksiyalarda bajariladi
