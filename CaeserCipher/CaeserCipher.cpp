// CaeserCipher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>

void reverse(std::string& alphabet, int start, int end)
{
	while (start < end)
		std::swap(alphabet[start++], alphabet[end--]);
}

std::string rotate(std::string alphabet, int shift, bool cipher = true)
{
	shift %= alphabet.size();
	if (cipher) shift = 26 - shift; // encrypt or decrypt
	reverse(alphabet, 0, alphabet.size() - 1);
	reverse(alphabet, 0, shift - 1);
	reverse(alphabet, shift, alphabet.size() - 1);
	return alphabet;
}

std::string encrypt(std::string alphabet, std::string text, int shift)
{
	std::string cipher = rotate(alphabet, shift);
	std::string encryption = "";
	for (auto c : text)
		encryption += (c % 'a' <= 25) ? cipher[c % 'a'] : ' ';
	return encryption;
}

std::string decrypt(std::string alphabet, std::string text, int shift)
{
	std::string cipher = rotate(alphabet, shift, false);
	std::string decryption = "";
	for (auto c : text)
		decryption += (c % 'a' <= 25) ? cipher[c % 'a'] : ' ';
	return decryption;
}

std::string makeLower(std::string text)
{
	for (auto c : text)
		c = tolower(c);
	return text;
}

void displayError()
{
	std::cout << "Unrecognized Command";
}

int main()
{
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	while (1)
	{
		std::cout << "Encrypt (E) or Decrypt (D)?" << std::endl;
		std::string c;
		std::cin >> c;

		if (c.size() == 1 && (c[0] == tolower('E') || c[0] == tolower('D')))
		{
			int shift;
			std::cout << "Choose shift: " << std::endl;
			std::cin >> shift;
			
			std::cin.ignore();
			std::cout << "Input plaintext: " << std::endl;
			std::string text;
			std::getline(std::cin, text);

			std::cout << (c[0] == tolower('E')
				? encrypt(alphabet, text, shift)
				: decrypt(alphabet, text, shift));
		}
		else
			displayError();

		std::cout << std::endl << std::endl;

	}
    return 0;
}

