#include "stdafx.h"
#include <iostream>
#include "Cmain.h"


int main(int argc, char* argv[])
{

	Cmain *cmain = new Cmain(800, 600);

	cmain->GameLoop();

	return EXIT_SUCCESS;
}

