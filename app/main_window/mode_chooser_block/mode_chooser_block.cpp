#include "mode_chooser_block.h"

ModeChooserBlock::ModeChooserBlock(
	const Glib::ustring& frame_title_,
	const Glib::ustring& encode_radio_text,
	const Glib::ustring& decode_radio_text
)
	: Gtk::Frame(frame_title_),
		mode_encode_radio_(radio_group_, encode_radio_text),
		mode_decode_radio_(radio_group_, decode_radio_text) {

	mode_encode_radio_.set_halign(Gtk::ALIGN_START);
	mode_decode_radio_.set_halign(Gtk::ALIGN_END);

	box_.set_hexpand(true);
	box_.set_halign(Gtk::ALIGN_CENTER);

	box_.add(mode_encode_radio_);
	box_.add(mode_decode_radio_);

	box_.set_margin_right(10);
	box_.set_margin_left(10);
	box_.set_margin_top(10);
	box_.set_margin_bottom(10);

	Gtk::Container::add(box_);
}

bool ModeChooserBlock::ModeEncode() const {
	return mode_encode_radio_.get_active();
}

bool ModeChooserBlock::ModeDecode() const {
	return mode_decode_radio_.get_active();
}

