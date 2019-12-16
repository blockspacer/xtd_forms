#pragma once
#include <stdexcept>
#include <xtd/forms/create_params.hpp>
#include <xtd/forms/native/choice.hpp>
#include <wx/choice.h>
#include "control_handler.hpp"

namespace xtd {
  namespace forms {
    namespace native {
      class wx_choice : public control_handler {
      public:
        wx_choice(const forms::create_params& create_params) {
          if (!create_params.parent()) throw std::invalid_argument("control must have a parent");
#if defined(__WXMSW__)
          int32_t height = 23;
#elif defined(__WXGTK__)
          int32_t height = 32;
#else
          int32_t height = 23;
#endif
          this->control_handler::create<wxChoice>(reinterpret_cast<control_handler*>(create_params.parent())->container(), wxID_ANY, wxPoint(create_params.x(), create_params.y()), wxSize(create_params.width(), height), 0, nullptr, style_to_wx_style(create_params.style(), create_params.ex_style()));
        }
        
        static long style_to_wx_style(size_t style, size_t ex_style) {
          long wx_style = 0;

          // Do not use wxwidgets sort
          //if ((style & CBS_SORT) == CBS_SORT) wx_style |= wxCB_SORT;
          
          return wx_style;
        }
      };
    }
  }
}