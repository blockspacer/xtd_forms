#pragma once
#include <stdexcept>
#include <xtd/forms/create_params.hpp>
#include <wx/textctrl.h>
#include "control_handler.hpp"

namespace xtd {
  namespace forms {
    namespace native {
      class wx_text_box : public control_handler {
      public:
        wx_text_box(const forms::create_params& create_params) {
          if (!create_params.parent()) throw std::invalid_argument("control must have a parent");
          this->control_handler::create<wxTextCtrl>(reinterpret_cast<control_handler*>(create_params.parent())->control(), wxID_ANY, create_params.caption().wstr(), wxPoint(create_params.x(), create_params.y()), wxSize(create_params.width(), create_params.height()), style_to_wx_style(create_params.style(), create_params.ex_style()));
        }
        
        static long style_to_wx_style(size_t style, size_t ex_style) {
          long wx_style = 0;
          
          if ((style & WS_BORDER) == WS_BORDER) wx_style |= wxBORDER_DEFAULT;
          else if ((ex_style & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE) wx_style |= wxBORDER_THEME;
          else wx_style |= wxBORDER_NONE;

          return wx_style;
        }
      };
    }
  }
}