#ifndef BASE_ENCODER_OPEN_FILE_BLOCK_H_
#define BASE_ENCODER_OPEN_FILE_BLOCK_H_

#include <gtkmm.h>

#include "main_window/open_file_dialog/open_file_dialog.h"

class OpenFileBlock final : public Gtk::Frame {
public:
	OpenFileBlock(const Glib::ustring& frame_title,
								Gtk::FileChooserAction action,
								const Glib::ustring& dialog_button_label,
								const Glib::ustring& dialog_title,
								const Glib::ustring& accept_label,
								const Glib::ustring& cancel_label);

	void SetFilename(const std::string& name);
	Glib::ustring GetFilename() const;

	template<typename Fn>
	void AddOnChangeCallback(Fn&& fn) {
		dialog_.signal_response().connect(
			std::forward<Fn>(fn)
		);
	};

private:
	Gtk::Box box_;
	Gtk::Label filename_label{"---"};
	Gtk::Button dialog_button_;
	OpenFileDialog dialog_;
};

#endif //BASE_ENCODER_OPEN_FILE_BLOCK_H_
