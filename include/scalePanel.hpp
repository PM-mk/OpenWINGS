#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "helper.hpp"
#include <wx/dataview.h>
#include <wx/valtext.h>
#include <wx/valnum.h>

namespace ow{
    class ScalePanel : public wxPanel{
        public:
            ScalePanel(wxWindow* parent);
            short value = 0;
            wxString Name = wxEmptyString;
        protected:
        private:
        // handlers:
            void OnAdd(wxCommandEvent& event);
            void OnDelete(wxCommandEvent& event);
            void OnClear(wxCommandEvent& event);
            void OnSetDefault(wxCommandEvent& event);
    };
} // namespace ow