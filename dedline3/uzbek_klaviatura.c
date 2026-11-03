/*
 * Yangi o'zbek alifbosi harflari uchun klaviatura yordamchisi.
 *
 *   Alt + g  ->  ğ      Alt + Shift + g  ->  Ğ
 *   Alt + o  ->  ö      Alt + Shift + o  ->  Ö
 *   Alt + s  ->  ş      Alt + Shift + s  ->  Ş
 *   Alt + c  ->  ç      Alt + Shift + c  ->  Ç
 *
 * Terminaldan boshqarish:
 *   uzbek_klaviatura start   -> fonda ishga tushadi
 *   uzbek_klaviatura stop    -> to'xtaydi
 *   uzbek_klaviatura status  -> ishlayaptimi yoki yo'qmi
 *   (Ctrl + Alt + Q ham to'xtatadi)
 *
 * Kompilyatsiya:  gcc uzbek_klaviatura.c -o uzbek_klaviatura.exe
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define MUTEX_NOMI "UzbekKlaviaturaMutex"   /* "dastur ishlayapti" belgisi */
#define EVENT_NOMI "UzbekKlaviaturaStop"    /* "to'xta" signali */

static HHOOK hook;
static int alt_bosilgan = 0;  /* foydalanuvchi Alt'ni ushlab turibdimi */
static int alt_qoyildi  = 0;  /* tizimga Alt'ni "qo'yib yubordik" deb aytdikmi */

/* Bitta oddiy tugma hodisasini yuborish */
static void tugma(WORD vk, DWORD flags)
{
    INPUT in = {0};
    in.type = INPUT_KEYBOARD;
    in.ki.wVk = vk;
    in.ki.dwFlags = flags;
    SendInput(1, &in, sizeof(INPUT));
}

/* Unicode belgini yozish (ğ, ş kabi harflar ASCII'da yo'q) */
static void belgi_yoz(wchar_t ch)
{
    INPUT in[2] = {0};
    in[0].type = in[1].type = INPUT_KEYBOARD;
    in[0].ki.wScan = in[1].ki.wScan = ch;
    in[0].ki.dwFlags = KEYEVENTF_UNICODE;
    in[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    SendInput(2, in, sizeof(INPUT));
}

/* Tugma kodiga mos o'zbek harfini qaytaradi, mos bo'lmasa 0 */
static wchar_t harf(DWORD vk, int katta)
{
    switch (vk) {
    case 'G': return katta ? 0x011E : 0x011F;  /* Ğ ğ */
    case 'O': return katta ? 0x00D6 : 0x00F6;  /* Ö ö */
    case 'S': return katta ? 0x015E : 0x015F;  /* Ş ş */
    case 'C': return katta ? 0x00C7 : 0x00E7;  /* Ç ç */
    }
    return 0;
}

/* OT har bir tugma bosilishini dasturlarga yetkazishdan oldin shu funksiyaga beradi */
static LRESULT CALLBACK klaviatura_hook(int code, WPARAM wp, LPARAM lp)
{
    KBDLLHOOKSTRUCT *k = (KBDLLHOOKSTRUCT *)lp;

    /* O'zimiz yuborgan (injected) hodisalarni o'tkazib yuboramiz */
    if (code == HC_ACTION && !(k->flags & LLKHF_INJECTED)) {
        int bosildi = (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN);
        DWORD vk = k->vkCode;

        if (vk == VK_LMENU || vk == VK_RMENU || vk == VK_MENU) {
            alt_bosilgan = bosildi;
            /* Alt'ni allaqachon qo'yib yuborgan bo'lsak, haqiqiy qo'yishni yutamiz */
            if (!bosildi && alt_qoyildi) {
                alt_qoyildi = 0;
                return 1;
            }
        } else if (bosildi && alt_bosilgan) {
            int ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;

            if (ctrl && vk == 'Q') {           /* Ctrl+Alt+Q -> chiqish */
                PostQuitMessage(0);
                return 1;
            }
            if (!ctrl) {
                int shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
                int caps  = (GetKeyState(VK_CAPITAL) & 1) != 0;
                wchar_t ch = harf(vk, shift ^ caps);

                if (ch) {
                    if (!alt_qoyildi) {
                        /* Alt bosilgan holatda harf yozilmaydi, shuning uchun
                           Alt'ni vaqtincha qo'yib yuboramiz. 0xE8 - bo'sh tugma,
                           u dasturlarda menyu ochilib ketishining oldini oladi. */
                        tugma(0xE8, 0);
                        tugma(0xE8, KEYEVENTF_KEYUP);
                        tugma(VK_MENU, KEYEVENTF_KEYUP);
                        alt_qoyildi = 1;
                    }
                    belgi_yoz(ch);
                    return 1;                  /* asl tugmani to'xtatamiz */
                }
            }
        }
    }
    return CallNextHookEx(hook, code, wp, lp);
}

/* Dastur hozir ishlayaptimi? (mutex mavjudligiga qarab) */
static int ishlayaptimi(void)
{
    HANDLE m = OpenMutexA(SYNCHRONIZE, FALSE, MUTEX_NOMI);
    if (m) { CloseHandle(m); return 1; }
    return 0;
}

/* Fondagi asosiy ish: hook o'rnatib, "stop" signalini kutadi */
static int fonda_ishlash(void)
{
    MSG msg;
    HANDLE mutex, stop;

    mutex = CreateMutexA(NULL, TRUE, MUTEX_NOMI);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        return 0;                              /* allaqachon ishlayapti */
    stop = CreateEventA(NULL, FALSE, FALSE, EVENT_NOMI);

    hook = SetWindowsHookExW(WH_KEYBOARD_LL, klaviatura_hook, GetModuleHandleW(NULL), 0);
    if (!hook)
        return 1;

    /* Ham Windows xabarlarini, ham "stop" signalini kutamiz */
    for (;;) {
        DWORD r = MsgWaitForMultipleObjects(1, &stop, FALSE, INFINITE, QS_ALLINPUT);
        if (r == WAIT_OBJECT_0)
            break;                             /* "stop" buyrug'i keldi */
        while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                goto tugadi;                   /* Ctrl+Alt+Q */
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
tugadi:
    UnhookWindowsHookEx(hook);
    CloseHandle(stop);
    CloseHandle(mutex);
    return 0;
}

/* O'zini yangi, oynasiz jarayon sifatida "run" argumenti bilan ishga tushiradi */
static int boshlash(void)
{
    char yol[MAX_PATH], buyruq[MAX_PATH + 16];
    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi;

    si.cb = sizeof(si);

    if (ishlayaptimi()) {
        printf("Dastur allaqachon ishlayapti.\n");
        return 0;
    }
    GetModuleFileNameA(NULL, yol, MAX_PATH);
    snprintf(buyruq, sizeof(buyruq), "\"%s\" run", yol);

    if (!CreateProcessA(NULL, buyruq, NULL, NULL, FALSE,
                        CREATE_NO_WINDOW | DETACHED_PROCESS, NULL, NULL, &si, &pi)) {
        printf("Xato: ishga tushirib bo'lmadi.\n");
        return 1;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    printf("Ishga tushdi. Alt + g/o/s/c -> ğ ö ş ç\n");
    return 0;
}

/* Ishlayotgan nusxaga "to'xta" signalini yuboradi */
static int toxtatish(void)
{
    HANDLE stop = OpenEventA(EVENT_MODIFY_STATE, FALSE, EVENT_NOMI);
    if (!stop) {
        printf("Dastur ishlamayapti.\n");
        return 0;
    }
    SetEvent(stop);
    CloseHandle(stop);
    printf("To'xtatildi.\n");
    return 0;
}

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);               /* ğ ş harflari terminalda to'g'ri chiqishi uchun */

    if (argc < 2) {
        printf("Foydalanish: uzbek_klaviatura start | stop | status\n");
        return 0;
    }
    if (strcmp(argv[1], "start") == 0)  return boshlash();
    if (strcmp(argv[1], "stop") == 0)   return toxtatish();
    if (strcmp(argv[1], "run") == 0)    return fonda_ishlash();   /* ichki buyruq */
    if (strcmp(argv[1], "status") == 0) {
        printf(ishlayaptimi() ? "Ishlayapti.\n" : "Ishlamayapti.\n");
        return 0;
    }
    printf("Noma'lum buyruq: %s\n", argv[1]);
    return 1;
}
