#include <thread>
#include <iostream>
#include "progress_dialog.h"

ProgressDialog::ProgressDialog(Gtk::Window& parent) {
	set_transient_for(parent);
	set_modal(true);
	set_position(Gtk::WIN_POS_CENTER_ON_PARENT);

	set_titlebar(header_);

	label_.set_width_chars(40);
	label_.set_margin_bottom(10);

	box_.set_margin_top(10);
	box_.set_margin_bottom(10);
	box_.set_margin_left(10);
	box_.set_margin_right(10);
	box_.add(label_);
	box_.add(progress_);
	box_.add(close_button_);

	close_button_.set_margin_top(10);
	close_button_.set_halign(Gtk::ALIGN_END);

	close_button_.signal_clicked().connect([this](){
		hide();
	});

	Gtk::Container::add(box_);
}

ProgressDialog::~ProgressDialog() {
	Stop();
}

void ProgressDialog::Run() {
	flag_.store(false);

	show_all();
	close_button_.hide();

	std::thread pulser([this](){
		while (!flag_.load()) {
			progress_.pulse();
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}

		flag_.store(false);
		flag_.notify_all();
	});

	pulser.detach();
}

void ProgressDialog::Stop() {
	if (!flag_.load()) {
		flag_.store(true);
		flag_.wait(true);
		flag_.store(true);
	}
}

void ProgressDialog::StopWithMessage(bool success, const Glib::ustring& message) {
	Stop();

	label_.set_text(message);

	if (success) {
		progress_.set_fraction(1);
		label_.override_color(Gdk::RGBA("black"));
	} else {
		progress_.set_fraction(0);
		label_.override_color(Gdk::RGBA("red"));
	}

	close_button_.show();
}
