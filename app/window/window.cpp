#include "window.h"

MainWindow::MainWindow() {
	SetupWindow();
	SetupWidgets();
}

void MainWindow::SetupWindow() {
	set_title("Base32 Codec");
	set_position(Gtk::WIN_POS_CENTER);
	set_default_size(600, 350);
}

void MainWindow::SetupWidgets() {
	auto title_label_font = title_label_.get_pango_context()->get_font_description();
	title_label_font.set_size(15 * PANGO_SCALE);
	title_label_font.set_weight(Pango::WEIGHT_SEMIBOLD);

	title_label_.set_halign(Gtk::ALIGN_START);
	title_label_.set_margin_bottom(20);
	title_label_.override_font(title_label_font);

	mode_chooser_box_.add(mode_encode_radio_);
	mode_chooser_box_.add(mode_decode_radio_);
	mode_frame_.add(mode_chooser_box_);

	grid_.attach(title_label_, 0, 0, 5);
	grid_.attach(mode_frame_, 0, 1);
	grid_.set_halign(Gtk::ALIGN_CENTER);
	grid_.set_valign(Gtk::ALIGN_CENTER);
}

void MainWindow::Show() {
	add(grid_);
	show_all();
}
