#ifndef BASE_ENCODER_MODE_CHOOSER_H_
#define BASE_ENCODER_MODE_CHOOSER_H_

#include <gtkmm.h>

class ModeChooserBlock final : public Gtk::Frame {
public:
	ModeChooserBlock(const Glib::ustring& frame_title_,
									 const Glib::ustring& encode_radio_text,
									 const Glib::ustring& decode_radio_text);

	~ModeChooserBlock() override = default;

	bool ModeEncode() const;
	bool ModeDecode() const;

private:
	Gtk::Box box_;
	Gtk::RadioButtonGroup radio_group_;
	Gtk::RadioButton mode_encode_radio_;
	Gtk::RadioButton mode_decode_radio_;
};

#endif //BASE_ENCODER_MODE_CHOOSER_H_
