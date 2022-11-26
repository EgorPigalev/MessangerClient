#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251");
	LPSTR lpszPipiName = "gff";

	BOOL flag_otvet = TRUE;
	char message[SIZE_BUFFER];
	DWORD size_buffer = SIZE_BUFFER;
	DWORD actual_written;
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	DWORD actual_readen;
	BOOL SeccessRead;
	while (TRUE)
	{
		HANDLE hNamePipe = CreateFile(
			lpszPipiName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		BOOL dwMode = PIPE_READMODE_MESSAGE;
		BOOL isSuccess = SetNamedPipeHandleState(hNamePipe, &dwMode, NULL, NULL);
		if (!isSuccess)
		{
			printf("Сервер не отвечает\n");
			flag_otvet = TRUE;
		}
		else
		{
			if (flag_otvet)
			{
				printf("Введите сообщение для сервера:\n");
				gets(message);
				buffer = &message;
				WriteFile(hNamePipe, buffer, size_buffer, &actual_written, NULL);
				flag_otvet = FALSE;
			}
			else
			{
				printf("Сервер пишет: ");
				printf(buffer);
				printf("\n");
				flag_otvet = TRUE;
				if (buffer == NULL)
				{
					printf("Пусто");
				}
			}
		}
		Sleep(100);
		CloseHandle(hNamePipe);
	}
}