#include <gtkmm.h>
#include <iostream>
#include <array>
#include <thread>
#include <future>
#include <base32/base32.h>
#include <cstring>

#include "window/window.h"

//class MyWin : public Gtk::Window {
//public:
//	MyWin() {
//		l_.set_label("hello");
//		b_.set_label("wow!");
//
//		b_.set_margin_bottom(10);
//		b_.set_margin_top(10);
//		b_.set_margin_left(10);
//
////		box_.add(l_);
////		box_.add(b_);
////		box_.add(bar_);
//
//		box_.attach(l_, 0, 0);
//		box_.attach(b_, 0, 1);
//		box_.attach(bar_, 0, 2, 5);
////    box_.add(f_);
//
////		box_.set_valign(Gtk::ALIGN_CENTER);
////		box_.set_halign(Gtk::ALIGN_CENTER);
//
//		set_default_size(600, 250);
//	}
//
//	void init() {
//		add(box_);
//	}
//
//	~MyWin() override = default;
//
//protected:
//	Gtk::Grid box_;
//	Gtk::Label l_;
//	Gtk::Button b_;
//	Gtk::ProgressBar bar_;
//	bool pulled = false;
//};
//
//std::string decode_(const char* data) {
//	std::string result;
//
//	base32::Decode(
//		data,
//		data + std::strlen(data),
//		std::back_inserter(result)
//	);
//
//	return result;
//}

int main(int argc, char** argv) {
	auto app = Gtk::Application::create(argc, argv);

	MainWindow w;
	w.Show();

	return app->run(w);
}
