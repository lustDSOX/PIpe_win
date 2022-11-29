#include "Header.h"


main() {
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	system("chcp 1251>nul");
	HANDLE hMainPipe;
	LPSTR sNamePipe = L"\\\\.\\pipe\\MainPipe";
	DWORD size = 256;
	LPWSTR buffer = (CHAR*)calloc(size, sizeof(CHAR));
	char message[256];
	BOOL conn;
	BOOL createdP = FALSE;
	DWORD realReading;
	BOOL text = FALSE;
	BOOL sRead;
	BOOL b;

	while (TRUE)
	{
		hMainPipe = CreateNamedPipe(sNamePipe, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES, 256, 256, INFINITE, NULL);
		if (!createdP)
		{
			//b = CreateProcessA("..\\x64\\Debug\\nono.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
			createdP = TRUE;
		}
		conn = ConnectNamedPipe(hMainPipe, NULL);
		if (conn) {
			sRead = ReadFile(hMainPipe, buffer, size, &realReading, NULL);
			text = FALSE;
			if (sRead) {
				printf("Client: ");
				printf(buffer);

				float f = atof(buffer);
				f *= f;
				sprintf(message, "%f", f);
				printf("\nYou: %s\n", message);
				WriteFile(hMainPipe, message, 256, NULL, NULL);
			}
		}
		else {
			printf("client disconnect\n");
		}
		CloseHandle(hMainPipe);
	}
}