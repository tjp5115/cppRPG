// ssGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cmain.h"

int main(int argc, char* argv[])
{
	Cmain *main = new Cmain(500,600);
	
	main->GameLoop();

	return 0;
}
