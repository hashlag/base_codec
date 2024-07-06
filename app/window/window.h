#ifndef BASE_ENCODER_WINDOW_H_
#define BASE_ENCODER_WINDOW_H_

#include <gtkmm.h>

class MainWindow final : public Gtk::Window {
public:
	MainWindow();
	~MainWindow() override = default;

	void Show();

private:
	void SetupWindow();
	void SetupWidgets();

	Gtk::Grid grid_;
	Gtk::Label title_label_{"Base32 codec"};

	Gtk::Frame mode_frame_{"Mode"};
	Gtk::Box mode_chooser_box_;
	Gtk::RadioButtonGroup mode_chooser_group_;
	Gtk::RadioButton mode_encode_radio_{mode_chooser_group_, "Encode"};
	Gtk::RadioButton mode_decode_radio_{mode_chooser_group_, "Decode"};
};

#endif //BASE_ENCODER_WINDOW_H_
