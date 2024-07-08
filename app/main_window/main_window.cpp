#include <iostream>
#include <thread>

#include "main_window.h"
#include "base32/base32.h"

MainWindow::MainWindow(int argc, char** argv) {
	SetupWindow();
	SetupWidgets();

	if (argc > 1) {
		input_file_.SetFilename(std::string(argv[1]));
	}
}

void MainWindow::SetupWindow() {
	set_title("Base32 Codec");
	set_position(Gtk::WIN_POS_CENTER);
	set_resizable(false);
	set_default_size(600, 380);
}

void MainWindow::SetupWidgets() {
	auto title_label_font = title_label_.get_pango_context()->get_font_description();
	title_label_font.set_size(15 * PANGO_SCALE);
	title_label_font.set_weight(Pango::WEIGHT_SEMIBOLD);

	title_label_.set_halign(Gtk::ALIGN_START);
	title_label_.set_margin_bottom(20);
	title_label_.override_font(title_label_font);

	mode_chooser_.set_margin_top(5);

	input_file_.AddOnChangeCallback(sigc::mem_fun(
		*this,
		&MainWindow::HandleFileSubmit
	));

	output_file_.AddOnChangeCallback(sigc::mem_fun(
		*this,
		&MainWindow::HandleFileSubmit
	));

	submit_button_.set_margin_top(20);
	submit_button_.set_margin_bottom(10);
	submit_button_.set_sensitive(false);

	submit_button_.signal_clicked().connect(sigc::mem_fun(
		*this,
		&MainWindow::HandleProcessing
	));

	grid_.attach(title_label_, 0, 0);
	grid_.attach(input_file_, 0, 1);
	grid_.attach(output_file_, 0, 2);
	grid_.attach(mode_chooser_, 0, 3);
	grid_.attach(submit_button_, 0, 4);

	grid_.set_halign(Gtk::ALIGN_CENTER);
	grid_.set_valign(Gtk::ALIGN_CENTER);

	Gtk::Container::add(grid_);
}

void MainWindow::HandleProcessing() {
	progress_.Run();

	std::thread worker([this](bool encode, const Glib::ustring& in, const Glib::ustring& out) {
		try {
			if (encode) {
				base32::EncodeFile(in, out);
			} else {
				base32::DecodeFile(in, out);
			}
		} catch (const std::exception& e) {
			progress_.StopWithMessage(false, std::format(
				"Failed: {}",
				e.what()
			));

			return;
		}

		progress_.StopWithMessage(true, "Done");

	}, mode_chooser_.ModeEncode(), input_file_.GetFilename(), output_file_.GetFilename());

	worker.detach();
}

void MainWindow::HandleFileSubmit(int) {
	if (!input_file_.GetFilename().empty() && !output_file_.GetFilename().empty()) {
		submit_button_.set_sensitive(true);
	}
}
