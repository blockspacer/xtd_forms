#include <stdexcept>
#include <xtd/drawing/system_colors.hpp>
#include <xtd/forms/native/application.hpp>
#include <xtd/forms/native/checked_list_box.hpp>
#include "wx_checked_list_box.hpp"

using namespace std;
using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms::native;

void checked_list_box::begin_update(intptr_t control) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->Freeze();
}

void checked_list_box::check_state(intptr_t control, size_t index, int check_state) {
  if (control == 0) return;
  static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->Check(index, check_state != 0);
}

int checked_list_box::check_state(intptr_t control, size_t index) {
  if (control == 0) return false;
  return static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->IsChecked(index);
}

void checked_list_box::delete_item(intptr_t control, size_t index) {
  if (control == 0) return;
  static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->Delete(index);
}

void checked_list_box::end_update(intptr_t control) {
  if (control == 0) return;
  reinterpret_cast<control_handler*>(control)->control()->Thaw();
}

void checked_list_box::insert_item(intptr_t control, size_t index, const string& value, bool checked) {
  if (control == 0) return;
  size_t real_index = -1;
  if (!static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->IsSorted())
    real_index = static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->Insert(value, index);
  else
    real_index = static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->Append(value);
  static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->Check(real_index, checked);
}

size_t checked_list_box::selected_index(intptr_t control) {
  if (control == 0) return -1;
  if (static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->HasMultipleSelection()) {
    vector<size_t> indices = selected_indices(control);
    if (indices.empty()) return -1;
    return indices[0];
  }
  return static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->GetSelection();
}

void checked_list_box::selected_index(intptr_t control, size_t index) {
  if (control == 0) return;
  return static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->SetSelection(index);
}

vector<size_t> checked_list_box::selected_indices(intptr_t control) {
  if (control == 0) return {};
  vector<size_t> indices;
  wxArrayInt wx_indices;
  static_cast<wxCheckListBox*>(reinterpret_cast<control_handler*>(control)->control())->GetSelections(wx_indices);
  for (int index : wx_indices)
    indices.push_back(index);
  return indices;
    
}