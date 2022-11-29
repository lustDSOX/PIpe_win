#include "HeaderN.h"

main() {
	HANDLE hMainPipe = 0;
	LPSTR sNamePipe = L"\\\\.\\pipe\\MainPipe";
	char message[256];
	DWORD size = 256;
	LPWSTR buffer = (CHAR*)calloc(size, sizeof(CHAR));
	BOOL conn;
	float a = 0;
	BOOL answer = TRUE;
	DWORD mode = PIPE_READMODE_MESSAGE;
	BOOL isScan = 0;
	while (TRUE)
	{
		printf("You: ");
		scanf("%s", &message);
		a = atof(message);
		if (a) {
			hMainPipe = CreateFile(sNamePipe, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			conn = SetNamedPipeHandleState(hMainPipe, &mode, NULL, NULL);
			if (conn) {
				sprintf(message, "%f", a);
				WriteFile(hMainPipe, message, 256, NULL, NULL);
				answer = FALSE;
				BOOL read = ReadFile(hMainPipe, buffer, size, NULL, NULL);
				if (read) {
					printf("Server:");
					printf(buffer);
					printf("\n");
					answer = TRUE;
				}
				CloseHandle(hMainPipe);
			}

		}
		else
		{
			printf("uncorrect message or zero\n");
		}
	}
}