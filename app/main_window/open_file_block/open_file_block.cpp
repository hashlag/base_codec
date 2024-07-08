#include "open_file_block.h"

OpenFileBlock::OpenFileBlock(
	const Glib::ustring& frame_title,
	Gtk::FileChooserAction action,
	const Glib::ustring& dialog_button_label,
	const Glib::ustring& dialog_title,
	const Glib::ustring& accept_label,
	const Glib::ustring& cancel_label)

	: Gtk::Frame(frame_title),
		dialog_button_(dialog_button_label),
		dialog_(dialog_title, action, accept_label, cancel_label) {

	filename_label.set_max_width_chars(60);
	filename_label.set_width_chars(60);
	filename_label.set_ellipsize(Pango::ELLIPSIZE_MIDDLE);
	filename_label.set_halign(Gtk::ALIGN_START);
	filename_label.set_margin_bottom(10);

	box_.add(filename_label);
	box_.add(dialog_button_);

	box_.set_margin_right(10);
	box_.set_margin_left(10);
	box_.set_margin_top(10);
	box_.set_margin_bottom(10);

	box_.set_hexpand(true);
	box_.set_halign(Gtk::ALIGN_END);

	dialog_button_.set_halign(Gtk::ALIGN_END);
	dialog_button_.set_margin_left(10);

	dialog_button_.signal_clicked().connect([this](){
		dialog_.show();
	});

	dialog_.signal_response().connect([this](int){
		if (!dialog_.get_filename().empty()) {
			filename_label.set_text(dialog_.get_filename());
		}
	});

	Gtk::Container::add(box_);
}

Glib::ustring OpenFileBlock::GetFilename() const {
	return dialog_.get_filename();
}

void OpenFileBlock::SetFilename(const std::string& name) {
	if (name.empty()) {
		return;
	}

	dialog_.set_filename(name);
	filename_label.set_text(name);
}
