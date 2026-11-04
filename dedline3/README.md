# O'zbek klaviatura yordamchisi

Yangi o'zbek alifbosidagi **ğ, ö, ş, ç** harflarini oddiy klaviaturada yozish uchun C tilida yozilgan kichik Windows dasturi.

> Operatsion tizimlar fanidan 3-amaliy topshiriq.
> Bajardi: Xoldarov Ozodbek (SRM002-2). Tekshirdi: Bekimmetova Durdona.

---

## Mundarija

1. [Dastur nima qiladi](#1-dastur-nima-qiladi)
2. [Nima kerak bo'ladi](#2-nima-kerak-boladi)
3. [O'rnatish](#3-ornatish)
4. [Ishlatish](#4-ishlatish)
5. [Muammo bo'lsa](#5-muammo-bolsa)
6. [Dastur qanday ishlaydi](#6-dastur-qanday-ishlaydi)
7. [Fayllar](#7-fayllar)

---

## 1. Dastur nima qiladi

Yangi o'zbek alifbosida **sh, o', g', ch** o'rniga **ş, ö, ğ, ç** harflari kiritildi. Oddiy klaviaturada bu harflar yo'q. Dastur ularni **Alt** tugmasi bilan yozish imkonini beradi:

| Bosing | Chiqadi | Shift bilan |
|:---:|:---:|:---:|
| `Alt` + `g` | **ğ** | **Ğ** |
| `Alt` + `o` | **ö** | **Ö** |
| `Alt` + `s` | **ş** | **Ş** |
| `Alt` + `c` | **ç** | **Ç** |

- Word, Notepad, brauzer, Telegram va boshqa **hamma dasturda** ishlaydi.
- **CapsLock** yoqilgan bo'lsa ham katta harf chiqadi.
- Fonda ishlaydi, ekranda oynasi ko'rinmaydi.

---

## 2. Nima kerak bo'ladi

- **Windows 10 yoki 11**
- **gcc** kompilyatori (MinGW), faqat kodni o'zingiz kompilyatsiya qilmoqchi bo'lsangiz kerak

gcc o'rnatilganini tekshirish uchun terminalga (cmd yoki PowerShell) yozing:

```bash
gcc --version
```

Versiya raqami chiqsa, hammasi joyida. Chiqmasa, [MinGW-w64](https://www.mingw-w64.org/) ni o'rnating.

---

## 3. O'rnatish

### 1-qadam. Kodni yuklab olish

**A usul: git bilan**

```bash
git clone https://github.com/ozodbekxoldarov/operatsion_tizimlar.git
cd operatsion_tizimlar/dedline3
```

**B usul: git'siz**

1. Shu sahifada `uzbek_klaviatura.c` faylini oching.
2. Yuqori o'ng burchakdagi **Download raw file** (yuklab olish) tugmasini bosing.
3. Faylni o'zingizga qulay papkaga saqlang va terminalda shu papkaga kiring.

### 2-qadam. Kompilyatsiya qilish

```bash
gcc uzbek_klaviatura.c -o uzbek_klaviatura.exe
```

Papkada `uzbek_klaviatura.exe` fayli paydo bo'ladi. O'rnatish shu bilan tugadi.

---

## 4. Ishlatish

Dasturni ikki usulda boshqarish mumkin.

### A usul: sichqoncha bilan (eng oson)

| Harakat | Natija |
|---|---|
| `uzbek_klaviatura.exe` ga **ikki marta bosing** | Dastur yoqiladi, "Dastur ishga tushdi" oynasi chiqadi |
| Yana **ikki marta bosing** | Dastur o'chadi, "Dastur to'xtatildi" oynasi chiqadi |

> Bosganda qora oyna bir lahza ko'rinib yo'qoladi, bu normal holat.

### B usul: terminal orqali

Terminalda `uzbek_klaviatura.exe` turgan papkaga kiring:

```bash
uzbek_klaviatura start
```
Dastur fonda ishga tushadi.

```bash
uzbek_klaviatura status
```
Dastur ishlayaptimi yoki yo'qmi, ko'rsatadi.

```bash
uzbek_klaviatura stop
```
Dasturni to'xtatadi.

> **PowerShell'da** buyruq oldiga `.\` qo'shing, masalan: `.\uzbek_klaviatura start`

### Klaviaturadan o'chirish

Dastur qanday yoqilgan bo'lishidan qat'i nazar, **`Ctrl` + `Alt` + `Q`** uni to'xtatadi.

### Sinab ko'rish

1. Dasturni yoqing.
2. Notepad'ni oching.
3. `Alt` ni ushlab turib `g` ni bosing, **ğ** chiqishi kerak.
4. `Shift` + `Alt` + `s` ni bosing, **Ş** chiqishi kerak.

### Kompyuter yoqilganda avtomatik ishga tushirish (ixtiyoriy)

1. `Win` + `R` bosing, `shell:startup` deb yozib, Enter bosing.
2. Ochilgan papkaga `uzbek_klaviatura.exe` ning **yorlig'ini** (shortcut) qo'ying. Buning uchun `.exe` ustida o'ng tugmani bosib, *Show more options → Create shortcut* ni tanlang va hosil bo'lgan yorliqni shu papkaga ko'chiring.

Bunda yorliq ham ikki marta bosish kabi ishlaydi: kompyuter yoqilganda dastur ishga tushadi va xabar oynasi chiqadi.

---

## 5. Muammo bo'lsa

| Muammo | Yechim |
|---|---|
| Klaviatura g'alati ishlay boshladi | `Ctrl` + `Alt` + `Q` bosing, keyin `Alt` ni bir marta bosib qo'yib yuboring |
| `Ctrl` + `Alt` + `Q` ham yordam bermadi | **Task Manager** (`Ctrl` + `Shift` + `Esc`) → `uzbek_klaviatura.exe` → **End task** |
| `'gcc' is not recognized` xatosi | gcc o'rnatilmagan yoki PATH'ga qo'shilmagan (2-bo'limga qarang) |
| `'uzbek_klaviatura' is not recognized` xatosi | Terminal boshqa papkada turibdi. `cd` bilan `.exe` turgan papkaga kiring. PowerShell'da `.\` qo'shing |
| Kompilyatsiya paytida `Permission denied` xatosi | Dastur ishlab turibdi. Avval `uzbek_klaviatura stop` bering |
| Antivirus ogohlantirish berdi | Dastur klaviaturani kuzatgani uchun ba'zi antiviruslar shubhalanadi. Kod ochiq, uni o'zingiz tekshirib ko'rishingiz mumkin |
| Ba'zi dasturlarda ishlamayapti | Administrator huquqida ishlayotgan dasturlarda ishlamaydi. U yerda ham kerak bo'lsa, `uzbek_klaviatura.exe` ni ham administrator sifatida ishga tushiring |

> Eslatma: dastur yoqilganda `Alt` + `g / o / s / c` yorliqlari boshqa dasturlarda ishlamaydi, chunki dastur ularni o'ziga oladi.

---

## 6. Dastur qanday ishlaydi

Tugma bosilganda Windows uni darhol dasturga yubormaydi, avval **"navbatchi"** (hook) dan o'tkazadi. Bizning dastur shu navbatchi vazifasini bajaradi:

```
 Tugma bosildi
      │
      ▼
 Bizning hook funksiyamiz ──── Alt + g/o/s/c emasmi? ───► odatdagidek o'tkazib yuboradi
      │
      │ Alt + g/o/s/c
      ▼
 1. Asl tugmani to'xtatadi
 2. Tizimga "Alt qo'yildi" deydi (aks holda harf yozilmaydi)
 3. Unicode harfni (ğ, ö, ş, ç) yuboradi
```

### Ishlatilgan operatsion tizim mexanizmlari

| Mexanizm | Funksiya | Vazifasi |
|---|---|---|
| Klaviatura hook | `SetWindowsHookEx(WH_KEYBOARD_LL)` | Har bir tugma bosilishini ushlab olish |
| Kiritishni imitatsiya qilish | `SendInput` + `KEYEVENTF_UNICODE` | ğ, ş kabi harflarni yozish (ular ASCII'da yo'q) |
| Xabarlar sikli | `MsgWaitForMultipleObjects`, `PeekMessage` | Dasturni tirik saqlash, hook shu sikl orqali ishlaydi |
| Jarayon yaratish | `CreateProcess` + `CREATE_NO_WINDOW` | `start` buyrug'i oynasiz fon jarayonini ochadi |
| Nomli Event (IPC) | `CreateEvent`, `SetEvent` | `stop` buyrug'i fondagi jarayonga "to'xta" signalini beradi |
| Nomli Mutex | `CreateMutex`, `OpenMutex` | Dastur ikki marta ishga tushmasligi va `status` uchun |

### Unicode kodlari

| Harf | Kichik | Katta |
|:---:|:---:|:---:|
| ğ / Ğ | U+011F | U+011E |
| ö / Ö | U+00F6 | U+00D6 |
| ş / Ş | U+015F | U+015E |
| ç / Ç | U+00E7 | U+00C7 |

---

## 7. Fayllar

| Fayl | Tavsif |
|---|---|
| `uzbek_klaviatura.c` | Dasturning to'liq kodi (bitta fayl, izohlari o'zbek tilida) |
| `README.md` | Shu qo'llanma |
| `.gitignore` | Kompilyatsiya qilingan `.exe` fayl GitHub'ga yuklanmasligi uchun |
