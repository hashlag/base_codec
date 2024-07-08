#ifndef BASE_ENCODER_WINDOW_H_
#define BASE_ENCODER_WINDOW_H_

#include <gtkmm.h>

#include "main_window/mode_chooser_block/mode_chooser_block.h"
#include "main_window/open_file_block/open_file_block.h"
#include "main_window/progress_dialog/progress_dialog.h"

class MainWindow final : public Gtk::Window {
public:
	MainWindow(int argc, char** argv);
	~MainWindow() override = default;

private:
	void SetupWindow();
	void SetupWidgets();

	void HandleProcessing();
	void HandleFileSubmit(int);

	Gtk::Grid grid_;
	Gtk::Label title_label_{"Base32 codec"};

	ModeChooserBlock mode_chooser_{"Mode", "Encode", "Decode"};

	OpenFileBlock input_file_{"File to process", Gtk::FILE_CHOOSER_ACTION_OPEN, "...", "Choose", "Open", "Cancel"};
	OpenFileBlock output_file_{"Save result as", Gtk::FILE_CHOOSER_ACTION_SAVE, "...", "Save as", "Save", "Cancel"};

	Gtk::Button submit_button_{"Proceed"};

	ProgressDialog progress_{*this};
};

#endif //BASE_ENCODER_WINDOW_H_
