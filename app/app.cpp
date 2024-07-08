#include <gtkmm.h>

#include "main_window/main_window.h"

int main(int argc, char** argv) {
	auto app = Gtk::Application::create();

	MainWindow w(argc, argv);
	w.show_all();

	return app->run(w);
}
