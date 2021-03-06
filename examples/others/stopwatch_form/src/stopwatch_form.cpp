#include <chrono>
#include <xtd/xtd.forms>

using namespace std;
using namespace xtd;
using namespace xtd::forms;

class stop_watch_form : public form {
public:
  stop_watch_form() {
    text("Stopwatch");
    start_position(form_start_position::center_screen);
    client_size({275, 120});
    form_border_style(forms::form_border_style::fixed_single);
    maximize_box(false);
    
    watch_panel.parent(*this);
    watch_panel.border_style(forms::border_style::fixed_3d);
    watch_panel.bounds({20, 10, 235, 50});
    watch_panel.back_color(drawing::color::average(drawing::color::black, drawing::color::lime, 0.25));
    watch_panel.fore_color(drawing::color::lime);

    watch.parent(watch_panel);
    watch.location({10, 7});
    watch.size({214, 32});
    watch.text("00:00:00.000");
    
    start_stop.parent(*this);
    start_stop.location({10, 80});
    start_stop.text("Start");
    start_stop.click += {*this, &stop_watch_form::on_start_stop_click};
    
    pause_resume.parent(*this);
    pause_resume.location({100, 80});
    pause_resume.text("Pause");
    pause_resume.enabled(false);
    pause_resume.click += {*this, &stop_watch_form::on_pause_resume_click};
    
    reset.parent(*this);
    reset.location({190, 80});
    reset.text("Reset");
    reset.enabled(false);
    reset.click += {*this, &stop_watch_form::on_reset_click};
    
    timer_chrono.interval(11);
    timer_chrono.tick +=  {*this, &stop_watch_form::on_timer_tick};
  }
  
private:
  void on_start_stop_click(control& sender, const event_args& e) {
    running = !running;
    if (running)
      start = chrono::high_resolution_clock::now();
    else
      duration += chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
    timer_chrono.enabled(running);
    start_stop.text(timer_chrono.enabled() ? "Stop" :  "Start");
    pause_resume.enabled(timer_chrono.enabled());
    reset.enabled(!timer_chrono.enabled() || !running);
  };
  
  void on_pause_resume_click(control& sender, const event_args& e) {
    timer_chrono.enabled(!timer_chrono.enabled());
    pause_resume.text(timer_chrono.enabled() ? "Pause" :  "Resume");
    start_stop.enabled(timer_chrono.enabled());
    reset.enabled(!timer_chrono.enabled() || !running);
  };
  
  void on_reset_click(control& sender, const event_args& e) {
    timer_chrono.enabled(false);
    running = false;
    duration = chrono::milliseconds(0);
    start_stop.enabled(true);
    pause_resume.enabled(false);
    reset.enabled(false);
    watch.text("00:00:00.000");
    start_stop.text("Start");
    pause_resume.text("Pause");
  };

  void on_timer_tick(component& sender, const event_args& e) {
    chrono::milliseconds elapsed_time = duration;
    if (running) elapsed_time += chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start);
    watch.text(strings::format("{0:H}:{0:M}:{0:S}.{1:D3}", elapsed_time, elapsed_time.count() % 1000));
  };

  chrono::high_resolution_clock::time_point start;
  chrono::milliseconds duration {0};
  bool running = false;
  
  panel watch_panel;
  lcd_label watch;
  button start_stop;
  button pause_resume;
  button reset;
  timer timer_chrono;
};

auto main()->int {
  xtd::forms::application::run(stop_watch_form());
}
