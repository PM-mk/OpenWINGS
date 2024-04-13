#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/notebook.h>
#include "ControlPanel.hpp"
#include "ElementPanel.hpp"
#include "ScalePanel.hpp"

namespace ow{
    class ScaleDialog : public wxDialog{
        public:
            ScaleDialog(wxWindow* parent);
            ScalePanel* pWeightEditPanel;
            ScalePanel* pInfluenceEditPanel;
            void LoadScales();

        protected:
        private:
            // handlers:
            void OnClose(wxCommandEvent& event);
    };
} // namespace ow
