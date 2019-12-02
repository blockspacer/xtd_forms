#include <xtd/xtd.forms>

using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms;

int main() {
  form form_main;
  form_main.text("Manual tests");
  form_main.start_position(form_start_position::manual);
  form_main.location({300, 200});
  form_main.client_size({518, 203});

  lcd_label label;
  label.parent(form_main);
  label.dock(dock_style::fill);
  label.style(lcd_style::seven_segments);
  //label.digit_spacing(8);
  //label.show_background_digit(false);
  label.back_color(color::average(color::lime, color::black, (double)16 / 255));
  label.fore_color(color::lime);

  int counter = 0;
  label.text(strings::format("{,5:F1}", double(counter++) / 10));
  timer timer;
  timer.tick += [&] {
    label.text(strings::format("{,5:F1}", double(counter++) / 10));
  };
  timer.interval(100);
  timer.enabled(true);

  application::run(form_main);
}
