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
        NULL,                                   // ��� ������ (���������� ��������� ������)
        _tcsdup(TEXT("notepad.exe")),    // ��������� ������
        NULL,                                   // �������� ������������ ��������
        NULL,                                   // �������� ������������ ������
        FALSE,                                  // ������������ ������������
        0,                                      // ����� ��������
        NULL,                                   // ���������
        NULL,                                   // ������� �������
        &si,                                    // STARTUPINFO
        &pi))                                   // PROCESS_INFORMATION
    {
        printf("CreateProcess failed\n");
        return 1;
    }

    printf("Notepad started. PID: %lu\n", pi.dwProcessId);

    // ������� ���������� ��������
    if (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_FAILED)
    {
        printf("WaitForSingleObject failed\n");
        return 1;
    }

    printf("Notepad has been closed\n");

    // ��������� �������������
    if (!CloseHandle(pi.hProcess))
        printf("CloseHandle hProcess failed\n");
    if (!CloseHandle(pi.hThread))
        printf("CloseHandle hThread failed\n");

    return 0;
}