# O'zbek klaviatura yordamchisi (C tilida)

Yangi o'zbek alifbosidagi **ğ, ö, ş, ç** harflarini oddiy klaviaturada yozish uchun kichik Windows dasturi.

| Tugmalar | Natija | Shift bilan |
|---|---|---|
| `Alt + g` | ğ | Ğ |
| `Alt + o` | ö | Ö |
| `Alt + s` | ş | Ş |
| `Alt + c` | ç | Ç |

## Kompilyatsiya

```bash
gcc uzbek_klaviatura.c -o uzbek_klaviatura.exe
```

## Terminaldan boshqarish

```bash
uzbek_klaviatura start    # fonda (oynasiz) ishga tushadi
uzbek_klaviatura status   # ishlayaptimi?
uzbek_klaviatura stop     # to'xtaydi
```

`Ctrl + Alt + Q` ham dasturni to'xtatadi.

## Sichqoncha bilan

`uzbek_klaviatura.exe` ustiga **ikki marta bosing**: dastur yoqiladi va xabar oynasi chiqadi. Yana ikki marta bossangiz, dastur o'chadi.

## Qanday ishlaydi

1. `SetWindowsHookEx(WH_KEYBOARD_LL, ...)`: OT har bir tugma bosilishini boshqa dasturlarga yetkazishdan oldin bizning funksiyamizga beradi.
2. Alt bilan `g / o / s / c` bosilsa, asl tugmani to'xtatamiz (`return 1`).
3. Alt vaqtincha "qo'yib yuboriladi" (aks holda harf yozilmaydi), so'ng `SendInput` + `KEYEVENTF_UNICODE` orqali kerakli Unicode harf yuboriladi.
4. `GetMessage` xabarlar sikli dasturni tirik ushlab turadi, hook shu sikl orqali ishlaydi.
5. `start`: dastur `CreateProcess` (`CREATE_NO_WINDOW`) bilan o'zining oynasiz nusxasini ochadi va terminalni bo'shatadi.
6. `stop`: nomli **Event** (`UzbekKlaviaturaStop`) signal beradi. Fondagi nusxa `MsgWaitForMultipleObjects` bilan shu signalni kutib turadi va uni olgach to'xtaydi. Bu jarayonlararo aloqa (IPC) usuli.
7. Nomli **Mutex** (`UzbekKlaviaturaMutex`) dastur ikki marta ishga tushishining oldini oladi, `status` buyrug'i ham shu mutexni tekshiradi.

| Harf | Unicode |
|---|---|
| ğ / Ğ | U+011F / U+011E |
| ö / Ö | U+00F6 / U+00D6 |
| ş / Ş | U+015F / U+015E |
| ç / Ç | U+00E7 / U+00C7 |
