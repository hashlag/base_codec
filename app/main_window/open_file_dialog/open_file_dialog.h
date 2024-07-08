#ifndef BASE_ENCODER_FILE_CHOOSER_H_
#define BASE_ENCODER_FILE_CHOOSER_H_

#include <gtkmm.h>

class OpenFileDialog final : public Gtk::FileChooserNative {
public:
	OpenFileDialog(const Glib::ustring& title,
								 Gtk::FileChooserAction action,
								 const Glib::ustring& accept_label,
								 const Glib::ustring& cancel_label);
};

#endif //BASE_ENCODER_FILE_CHOOSER_H_
