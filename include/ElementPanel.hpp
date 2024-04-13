#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include "wx/notebook.h"
#include "wx/listctrl.h"
#include "ControlPanel.hpp"
#include "ScaleDialog.hpp"

namespace ow{
    class ElementPanel : public wxPanel{
        public:
            ElementPanel(wxWindow* parent);
            wxListCtrl* pElementList;
        protected:
        private:
        // handlers:
            void OnEditScales(wxCommandEvent& event);

    };
} // namespace ow