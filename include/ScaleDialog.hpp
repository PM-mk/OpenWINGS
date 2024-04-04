#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/notebook.h>
#include "ScalePanel.hpp"

namespace ow{
    class ScaleDialog : public wxDialog{
        public:
            ScaleDialog(wxWindow* parent);
        protected:
        private:
            // handlers:
            void OnOK(wxCommandEvent& event);
            void OnCancel(wxCommandEvent& event);

    };
} // namespace ow
