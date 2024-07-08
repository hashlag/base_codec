#ifndef BASE_ENCODER_PROGRESS_DIALOG_H_
#define BASE_ENCODER_PROGRESS_DIALOG_H_

#include <gtkmm.h>

#include <atomic>

class ProgressDialog final : public Gtk::Window {
public:
	explicit ProgressDialog(Gtk::Window& parent);
	~ProgressDialog() override;

	void Run();

	void Stop();
	void StopWithMessage(bool success, const Glib::ustring& message);

private:
	std::atomic_bool flag_;

	Gtk::VBox box_;
	Gtk::HeaderBar header_;
	Gtk::Label label_{"Processing... Please wait."};
	Gtk::ProgressBar progress_;
	Gtk::Button close_button_{"OK"};
};

#endif //BASE_ENCODER_PROGRESS_DIALOG_H_
