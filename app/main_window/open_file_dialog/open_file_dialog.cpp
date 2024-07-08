#include "open_file_dialog.h"

OpenFileDialog::OpenFileDialog(
	const Glib::ustring& title,
	Gtk::FileChooserAction action,
	const Glib::ustring& accept_label,
	const Glib::ustring& cancel_label)

	: Gtk::FileChooserNative(title,
													 action,
													 accept_label,
													 cancel_label) {};
