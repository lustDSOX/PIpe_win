#include "HeaderN.h"

main() {
	HANDLE hMainPipe = 0;
	LPSTR sNamePipe = L"\\\\.\\pipe\\MainPipe";
	char message[256];
	DWORD size = 256;
	LPWSTR buffer = (CHAR*)calloc(size, sizeof(CHAR));
	system("pause");
	hMainPipe = CreateFile(sNamePipe,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	BOOL conn = SetNamedPipeHandleState(hMainPipe, PIPE_READMODE_MESSAGE, NULL, NULL);

	if (conn) {
		printf("Success connerct\n");
		system("pause");
	}
}