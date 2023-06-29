#include "Console.h"

void Console::SetPosition(int row, int col)
{
	COORD position;
	position.X = col;
	position.Y = row;
	SetConsoleCursorPosition(descriptor, position);
}

void Console::SetForeground(Colors color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(descriptor, &info);

	WORD colorCurrent = info.wAttributes;
	WORD colorNew = ((colorCurrent >> 4) << 4) | (unsigned char)color;
	
	SetConsoleTextAttribute(descriptor, colorNew);
}

void Console::SetBackground(Colors color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(descriptor, &info);

	WORD colorCurrent = info.wAttributes;
	WORD colorNew = (colorCurrent & 0b1111) | ((unsigned char)color << 4);

	SetConsoleTextAttribute(descriptor, colorNew);
}

void Console::SetColors(Colors back, Colors fore)
{
	SetBackground(back);
	SetForeground(fore);
}

void Console::Write(std::string message)
{
	std::cout << message;
}

void Console::Write(const char* message)
{
	std::cout << message;
}

void Console::Write(char cmessage)
{
	std::cout << cmessage;
}

void Console::WriteLine(std::string message)
{
	Write(message + "\n");
}

void Console::WriteLine(const char* message)
{
	Write(message);
	std::cout << "\n";
}

void Console::WriteLine(char cmessage)
{
	Write(cmessage);
	std::cout << "\n";
}

void Console::WritePosition(int row, int col, std::string message)
{
	SetPosition(row, col);
	Write(message);
}

void Console::WritePosition(int row, int col, const char* message)
{
	SetPosition(row, col);
	Write(message);
}

void Console::WritePosition(int row, int col, char cmessage)
{
	SetPosition(row, col);
	Write(cmessage);
}

void Console::CursorVisible(bool visible)
{
	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(descriptor, &info);
	info.bVisible = visible;
	SetConsoleCursorInfo(descriptor, &info);
}

int Console::ReadKey()
{
	/*int key = _getch();
	if (key < 0)
		key = _getch();
	return key;*/
	return _getch();
}

void Console::Clear()
{
	system("cls");
}
