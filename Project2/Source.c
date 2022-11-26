#include "Header.h"


main() {
	system("chcp 1251>nul");
	HANDLE hMainPipe;
	LPSTR sNamePipe = L"\\\\.\\pipe\\MainPipe";
	hMainPipe = CreateNamedPipe(sNamePipe, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES, 256, 256, INFINITE, NULL);
	while (TRUE)
	{
		BOOL conn = ConnectNamedPipe(hMainPipe, NULL);
		if (conn) {
			printf("Success connerct\n");
			DWORD size = 256;
			LPWSTR buffer = (CHAR*)calloc(size, sizeof(CHAR));
			BOOL sRead = ReadFile(sNamePipe, buffer, size, NULL, NULL);
			if (!sRead) {
				printf("Read Error");
			}
			printf(buffer);
		}
	}
}