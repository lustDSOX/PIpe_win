#include "HeaderN.h"

main() {
	HANDLE hMainPipe = 0;
	LPSTR sNamePipe = L"\\\\.\\pipe\\MainPipe";
	char message[256];
	DWORD size = 256;
	LPWSTR buffer = (CHAR*)calloc(size, sizeof(CHAR));
	BOOL conn;
	BOOL answer = TRUE;
	DWORD mode = PIPE_READMODE_MESSAGE;
	while (TRUE)
	{
		hMainPipe = CreateFile(sNamePipe, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		conn = SetNamedPipeHandleState(hMainPipe, &mode, NULL, NULL);
		if (conn) {
			if (answer) {
				printf("You: ");
				gets(message);
				WriteFile(hMainPipe, message, 256, NULL, NULL);
				answer = FALSE;
			}

			BOOL read = ReadFile(hMainPipe, buffer, size, NULL, NULL);
			if (read) {
				printf("Server:");
				printf(buffer);
				printf("\n");
				answer = TRUE;
			}
		}
		CloseHandle(hMainPipe);
	}
}