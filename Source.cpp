#include <stdio.h>
#include <iostream>

/*
 * ������� �� �������� ������ ��� ���������� �������, �������� ������ ������ ������.
*/

int main() {
	const int stringSize = 100;
	
	char str[stringSize];
	char reversString[stringSize];
	char result[stringSize];
	
	printf("Enter string: ");
	fgets(str, sizeof(str), stdin);

	int len = 0;
	__asm {
		lea ebx, str
		mov ecx, len

		cmp byte ptr[ebx][0], 0
		je TO_EXIT

		STR_LENGTH : ; ������� ���������� �������� � str
					 inc ecx
					 mov ah, [ebx][ecx]

					 cmp ah, 0; �������� �� ������ ������
					 jne STR_LENGTH

					 sub ecx, 1; ���������� 0, �.�.��� ��������� ������
					 mov esi, 0
					 lea edx, reversString 
					 mov ah, ' '; ��� ���������� ����� �������

		REMOVE_SPACES :
		mov al, [ebx][ecx]
			cmp ah, al; �������� �� "������"
			je ZERO_SYMBOL
			mov[edx][esi], al; ������ �������, ���� �� ������
			add esi, 1

			ZERO_SYMBOL:
		loop REMOVE_SPACES

			mov al, [ebx][ecx]; ��������� ��� ������� � �������� 0
			cmp ah, al
			je NEXT
			mov[edx][esi], al
			add esi, 1

			NEXT:
		mov byte ptr[edx][esi], 0
			mov ecx, 0; ���������� ������
			lea eax, result
			mov byte ptr[eax][0], 0
			cmp BYTE PTR[edx][0], 0
			je EXIT
			NEW_STR_LENGTH : ; ������� �������� ���������� ������
			inc ecx
			mov ah, [edx][ecx]
			cmp byte ptr[edx][ecx], 0; �������� �� ����� �������
			jne NEW_STR_LENGTH
			sub ecx, 1
			mov esi, 0
			lea eax, result; result � ������� eax

			INVERT :
		mov bl, [edx][ecx]
			mov[eax][esi], bl
			add esi, 1
			loop INVERT

			mov bl, [edx][ecx]; ����������� �� ��, ��� � � �����, �� ��� ������� � ������� 0
			mov[eax][esi], bl
			add esi, 1
			cmp byte ptr[eax][0], 0
			je EXIT
			mov byte ptr[eax][esi], 0
			jmp EXIT

			TO_EXIT :
			lea eax, result
			mov byte ptr[result][0], 0
			lea eax, reversString
			mov byte ptr[reversString][0], 0

			EXIT :
	}
	
	printf("Result: %s",result);
	return 0;
}