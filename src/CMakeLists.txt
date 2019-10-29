cmake_minimum_required(VERSION 3.3)

# Solution
project(src)

# Projects
add_subdirectory(xtd_forms_native)

if (APPLE)
  option(XTD_COCOA "Use Apple AppKit libraries as native drawing and forms libraries (not implemented yet)" OFF)
  if (XTD_COCOA)
    add_subdirectory(xtd_forms_native_cocoa)
    set(XTD_FORMS_NATIVE_LIBRARY xtd.forms.native.cocoa)
  endif ()
endif ()

option(XTD_FLTK "Use FLTK as native drawing and forms libraries (not implemented yet)" OFF)
if (XTD_FLTK)
  add_subdirectory(xtd_forms_native_fltk)
  set(XTD_FORMS_NATIVE_LIBRARY xtd.forms.native.fltk)
endif ()

option(XTD_GTK "Use Gtk+3 as native drawing and forms libraries (not implemented yet)" OFF)
if (XTD_GTK)
  add_subdirectory(xtd_forms_native_gtk3)
  set(XTD_FORMS_NATIVE_LIBRARY xtd.forms.native.gtk3)
endif ()

option(XTD_QT5 "Use Qt as native drawing and forms libraries (not implemented yet)" OFF)
if (XTD_QT5)
  add_subdirectory(xtd_forms_native_qt5)
  set(XTD_FORMS_NATIVE_LIBRARY xtd.forms.native.fltk)
endif ()

if (MSVC)
  option(XTD_WIN32 "Use Microsoft Win32 api as native drawing and forms libraries (not implemented yet)" OFF)
  if (XTD_WIN32)
    add_subdirectory(xtd_forms_native_win32)
    set(XTD_FORMS_NATIVE_LIBRARY xtd.forms.native.win32)
  endif ()
endif ()

option(XTD_WXWIDGETS "Use wxWidgets as native drawing and forms libraries" ON)
if (XTD_WXWIDGETS)
  add_subdirectory(xtd_forms_native_wxwidgets)
  set(XTD_FORMS_NATIVE_LIBRARY xtd.forms.native.wxwidgets)
endif ()

if (IS_MAIN_PROJECT)
  add_subdirectory(xtd_delegates)
  add_subdirectory(xtd_diagnostics)
  add_subdirectory(xtd_core)
  add_subdirectory(xtd_drawing)
  add_subdirectory(xtd_io)
  add_subdirectory(xtd_strings)
  add_subdirectory(xtd_tunit)
endif ()

add_subdirectory(xtd_forms)