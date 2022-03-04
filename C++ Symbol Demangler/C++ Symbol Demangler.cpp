// C++ Symbol Demangler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>

int
main(int argc, char* argv[])
{
	char buf[10000];
	char buf2[10000];

	while (fgets(buf, sizeof(buf), stdin)) {
		char* p = buf;

		char last = 0;
		while (*p) {
			int l = strcspn(p, " \n\t()\"\'");

			if (last)
				printf("%c", last);
			last = p[l];
			p[l] = 0;

			buf2[0] = 0;
			if (p[0] && !UnDecorateSymbolName(p, buf2, sizeof(buf2), UNDNAME_COMPLETE)) {
				printf("%s", p);
			}
			else
				printf("%s", buf2);
			p += l + 1;
		}
		if (last)
			printf("%c", last);
	}
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
