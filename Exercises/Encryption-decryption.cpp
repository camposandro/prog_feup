#include <iostream>
#include <cmath>
using namespace std;

/**
funcao: encripta digitos de um numero
encriptacao:
- 1ºdig troca com 3ºdig
- 2ºdig troca com 4ºdig
retorna: valor cifrado
**/
int cipher(int num)
{
	// reverses number
	int ciphered = 0;
	int i = 3;
	while (num != 0)
	{
		int lastdig = num % 10;
		lastdig = (lastdig + 8) % 10; // digit encryption
		num /= 10;
		ciphered += lastdig * pow(10, i);
		i--;
	}
	//-----------------------
	return ciphered;
}

/**
funcao: desencripta digitos de um numero
desencriptacao:
- 1ºdig troca com 3ºdig
- 2ºdig troca com 4ºdig
retorna: valor decifrado
**/
int decipher(int num)
{
	// number inversion
	int deciphered = 0;
	int i = 3;
	while (num != 0)
	{
		// digit decryption
		/* Para desencriptar ter em atencao que o resto da divisao
		por 10 nos indica o valor do ultimo digito do numero que corresponde
		ao digito inicial + 8;
		Como os algarismos variam apenas entre 0 e 9 entao ao adicionar 8 estes
		variarao apenas entre 8 e 17 o que correspondera a valores % 10 de:
		8,9,0,1,2,3,4,5,6,7.
		*/
		int lastdig = num % 10;

		if (lastdig == 8 || lastdig == 9)
			lastdig -= 8;
		else if (lastdig >= 0 && lastdig <= 7)
			lastdig += 2;

		num /= 10;
		deciphered += lastdig * pow(10, i);
		i--;
	}
	//-----------------------
	return deciphered;
}

void menu()
{
	cout << "***********************\n";
	cout << "*ENCRYPTION/DECRYPTION*\n";
	cout << "***********************\n\n";
	cout << "For encryption press 0\n";
	cout << "For decryption press 1\n\n";

	int choice;
	cin >> choice;

	int num;
	cout << "Insert number: ";
	cin >> num;

	if (!choice)
		cout << cipher(num) << endl;
	else if (choice == 1)
		cout << decipher(num) << endl;
}

int main()
{
	menu();
	return 0;
}
