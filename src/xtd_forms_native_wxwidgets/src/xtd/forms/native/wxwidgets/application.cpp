#if !defined(_WIN32)
#include <unistd.h>
#endif
#include <xtd/environment.h>
#include <xtd/forms/native/application.h>
#include <xtd/forms/window_messages.h>
#include "../../../../../include/xtd/forms/native/wxwidgets/control_handler.h"
#include "../../../../../include/xtd/forms/native/wxwidgets/wx_application.h"
#include <wx/aboutdlg.h>
#include <wx/sysopt.h>

#if defined(__WXMSW__)
#include "DarkMode.h"
extern int __xtd_win32_enable_dark_mode__;
#elif defined(__WXGTK__)
bool __xtd_gtk_is_dark_mode__ = false;
#undef interface_
#include <gtk/gtk.h>
#elif defined(__WXOSX__)
void __xtd_osx_enable_dark_mode__();
void __xtd_osx_enable_light_mode__();
#endif

using namespace std;
using namespace xtd;
using namespace xtd::forms::native;

event<wx_application, delegate<bool(intptr_t, int32_t, intptr_t, intptr_t, intptr_t)>> wx_application::message_filter_proc;

namespace {
bool restart_asked = false;
}

bool application::allow_quit() {
  initialize(); // Must be first
  return true;
}

void application::cleanup() {
  if (wxTheApp) {
    wxTheApp->OnExit();
    wxEntryCleanup();
    delete wxTheApp;
    wxApp::SetInstance(nullptr);
  }
}

void application::do_events() {
  initialize(); // Must be first
  
  wxTheApp->ProcessPendingEvents();
}

void application::do_idle() {
  wxWakeUpIdle();
}

void application::enable_dark_mode() {
#if defined(__WXMSW__)
  __xtd_win32_enable_dark_mode__ = 1;
  initialize();
#elif defined(__WXGTK__)
  __xtd_gtk_is_dark_mode__ = true;
  initialize();
#elif defined(__WXOSX__)
  initialize();
  __xtd_osx_enable_dark_mode__();
#endif
}

void application::enable_light_mode() {
#if defined(__WXMSW__)
  __xtd_win32_enable_dark_mode__ = 0;
  initialize();
#elif defined(__WXGTK__)
  __xtd_gtk_is_dark_mode__ = false;
  initialize();
#elif defined(__WXOSX__)
  initialize();
  __xtd_osx_enable_light_mode__();
#endif
}

void application::enable_visual_style() {
  initialize(); // Must be first
  wxTheApp->SetUseBestVisual(true);
}

void application::exit() {
  if (wxTheApp)
    wxTheApp->ExitMainLoop();
}

void application::initialize() {
  if (wxTheApp) return;
  wxDISABLE_DEBUG_SUPPORT();
  wxSystemOptions::SetOption("osx.openfiledialog.always-show-types", 1);
  wxApp::SetInstance(new wx_application());
  int argc = 0;
  wxEntryStart(argc, (wxChar**)nullptr);
  wxTheApp->CallOnInit();
  wxTheApp->SetExitOnFrameDelete(false);
#if defined(__WXMSW__)
  if (!__xtd_win32_enable_light_mode__) InitDarkMode();
#elif defined(__WXGTK__)
  g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", __xtd_gtk_is_dark_mode__, nullptr);
//  g_object_set(gtk_settings_get_default(), "gtk-button-images", true, nullptr);
#elif defined(__WXOSX__)
  wxMenuBar* menubar = new wxMenuBar();
  menubar->Bind(wxEVT_MENU, [&](wxCommandEvent& event) {
    if (event.GetId() == wxID_EXIT) {
      auto can_quit = true;
      for (auto window : wxTopLevelWindows)
        if (!(can_quit = window->Close())) break;
      if (can_quit) wxTheApp->ExitMainLoop();
    }
    else event.Skip();
  });
  wxMenuBar::MacSetCommonMenuBar(menubar);
#endif
}

void application::register_message_filter(const delegate<bool(intptr_t, int32_t, intptr_t, intptr_t, intptr_t)>& message_filter_proc) {
  initialize(); // Must be first
  static_cast<wx_application*>(wxTheApp)->message_filter_proc += message_filter_proc;
}

void application::register_wnd_proc(const delegate<intptr_t(intptr_t, int32_t, intptr_t, intptr_t, intptr_t)>& wnd_proc) {
  initialize(); // Must be first
  static_cast<wx_application*>(wxTheApp)->wnd_proc += wnd_proc;
}

void application::restart() {
  restart_asked = true;
}

void application::run() {
  initialize(); { // Must be first
    class uninitializer {
    public:
      ~uninitializer() { cleanup(); }
    } uninitializer;
    static_cast<wx_application*>(wxTheApp)->send_message(0, WM_ACTIVATEAPP, true, 0, 0);
    wxTheApp->OnRun();
    static_cast<wx_application*>(wxTheApp)->send_message(0, WM_ACTIVATEAPP, false, 0, 0);
    static_cast<wx_application*>(wxTheApp)->send_message(0, WM_QUIT, 0, 0, 0);
  }
  if (restart_asked) {
    std::vector<string> command_line_args = environment::get_command_line_args();
    char** argv = new char* [command_line_args.size() + 1];
    for (size_t index = 0; index < command_line_args.size(); index++)
      argv[index] = command_line_args[index].data();
    argv[command_line_args.size()] = 0;
    execv(argv[0], argv);
    delete[] argv;
    _Exit(0);
  }
}

void application::use_wait_cursor(bool use_wait_cursor) {
  if (use_wait_cursor) wxBeginBusyCursor();
  else wxEndBusyCursor();
}
