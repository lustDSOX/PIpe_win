#include "HeaderN.h"

main() {
	HANDLE hMainPipe = {0};
	LPSTR sNamePipe = "\\\\.\\pipe\\MainPipe";

	system("pause");
	hMainPipe = CreateFile(sNamePipe, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	BOOL conn = SetNamedPipeHandleState(sNamePipe, PIPE_READMODE_MESSAGE, NULL, NULL);
	if (conn) {
		printf("Success connerct\n");
		DWORD size = 256;
		while (TRUE) {
			char message[256];
			printf("Print your message");
			gets(message);
			LPWSTR buffer = &message;
			WriteFile(sNamePipe, buffer, size, NULL, NULL);
		}
	}
}