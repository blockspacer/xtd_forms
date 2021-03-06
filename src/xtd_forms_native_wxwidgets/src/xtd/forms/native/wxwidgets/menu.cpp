#include "../../../../../include/xtd/forms/native/wxwidgets/wx_menu.h"
#include <xtd/forms/native/menu.h>
#include <wx/menu.h>

using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms::native;

intptr_t menu::create(const std::string& text, const std::vector<intptr_t>& items) {
  //return reinterpret_cast<intptr_t>(new wxMenu());
  std::vector<wx_menu_item> wx_menu_items;
  for (auto item : items)
    wx_menu_items.push_back(*reinterpret_cast<wx_menu_item*>(item));
  return reinterpret_cast<intptr_t>(new wx_menu_item(text, wx_menu_items));
}


void menu::destroy(intptr_t menu) {
  if (!menu) return;
  //delete reinterpret_cast<wxMenu*>(menu);
  delete reinterpret_cast<wx_menu_item*>(menu);
}
