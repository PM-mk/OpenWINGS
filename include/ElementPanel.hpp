#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "ScaleDialog.hpp"

namespace ow{
    class ElementPanel : public wxPanel{
        public:
            ElementPanel(wxWindow* parent);
            ~ElementPanel();
            wxListCtrl* pElementList;
            ScaleDialog* pScaleDialog;
        protected:
        private:
        // handlers:
            void OnEditScales(wxCommandEvent& event);

    };
} // namespace ow