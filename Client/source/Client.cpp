//#include "ClientNetwork.hpp"
//
//int main()
//{
//     ClientNetwork client;
//     client.connect("localHost", 2525);
//     client.run();
//
//     
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
