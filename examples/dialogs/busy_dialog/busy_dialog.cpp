#include <thread>
#include <xtd/xtd.forms>

using namespace xtd::forms;

class form1 : public form {
public:
  form1() {
    text("Busy dialog example");
    
    button1.auto_size(true);
    button1.location({10, 10});
    button1.parent(*this);
    button1.text("Do something...");
    button1.click += [] {
      busy_dialog dialog;
      dialog.icon(xtd::drawing::system_icons::exclamation({64, 64}));
      dialog.text("Application busy");
      dialog.description("Please wait while do something...");
      dialog.back_color(xtd::drawing::color::red);
      dialog.fore_color(xtd::drawing::color::white);
      dialog.transparency(0.75);
      dialog.show();
      for (auto count = 0; count < 500; ++count) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        application::yield();
      }
    };
  }
  
private:
  button button1;
};

int main() {
  xtd::forms::application::run(form1());
}
