#include "app-base.hpp"
#include "tokenizer.hpp"

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

void CreateConsole() {
	if (::AllocConsole())
	{
		int hCrt = ::_open_osfhandle((intptr_t) ::GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		FILE *hf = ::_fdopen(hCrt, "w");
		*stdout = *hf;
		::setvbuf(stdout, NULL, _IONBF, 0);

		hCrt = ::_open_osfhandle((intptr_t) ::GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
		hf = ::_fdopen(hCrt, "w");
		*stderr = *hf;
		::setvbuf(stderr, NULL, _IONBF, 0);
	}
}

// program entry
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CreateConsole();

	std::cout << "Hello World!" << std::endl;

	auto app = bf::MakeApplication();

	bf::string command_line(lpCmdLine);
	bf::Tokenizer t(command_line);

	while (t.NextToken()) {
		app->AppendCommand(t.GetToken());
	}

	const int width = 1280;
	const int height = 720;

	// todo : error catch
	app->Initialize(width, height);
	app->MainLoop();

	delete app;

	// Exit program
	exit(EXIT_SUCCESS);
}