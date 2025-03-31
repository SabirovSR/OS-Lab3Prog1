#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
        NULL,                                   // Имя модуля (используем командную строку)
        _tcsdup(TEXT("notepad.exe")),    // Командная строка
        NULL,                                   // Атрибуты безопасности процесса
        NULL,                                   // Атрибуты безопасности потока
        FALSE,                                  // Наследование дескрипторов
        0,                                      // Флаги создания
        NULL,                                   // Окружение
        NULL,                                   // Текущий каталог
        &si,                                    // STARTUPINFO
        &pi))                                   // PROCESS_INFORMATION
    {
        printf("CreateProcess failed\n");
        return 1;
    }

    printf("Notepad started. PID: %lu\n", pi.dwProcessId);

    // Ожидаем завершения процесса
    if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED)
    {
        printf("WaitForSingleObject failed\n");
        return 1;
    }

    printf("Notepad has been closed\n");

    // Закрываем дескрипторыша
    if (!CloseHandle(pi.hProcess))
        printf("CloseHandle hProcess failed\n");
    if (!CloseHandle(pi.hThread))
        printf("CloseHandle hThread failed\n");

    return 0;
}