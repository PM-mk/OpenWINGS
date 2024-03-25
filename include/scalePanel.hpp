#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "helper.hpp"
#include <wx/dataview.h>

namespace ow{
    class ScalePanel : public wxPanel{
        public:
            ScalePanel(wxWindow* parent);
        protected:
        private:
        // handlers:
            void OnSetScale(wxCommandEvent& event);
    };
} // namespace ow