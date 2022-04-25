//#include "servernetwork.hpp"
//
//#include <iostream>
//
//int main()
//{
//     ServerNetwork server;
//
//     if(!server.init(2525))
//         return EXIT_FAILURE;
//
//     server.run(); 
//
//     return EXIT_SUCCESS;
//}

#include <FL/Fl.h>
#include <FL/Fl_Window.h>
#include <FL/Fl_Button.h>

void button_callback(Fl_Widget* o, void*)
{
	Fl_Button* button = (Fl_Button*)o;
	button->label("Pressed!");
	button->redraw();
}

int main()
{
	Fl_Window window(300, 200, "Test");

	window.begin();
	Fl_Button button(10, 150, 100, 30, "Press me");
	window.end();

	button.callback(button_callback);

	window.show();
	return Fl::run();
}