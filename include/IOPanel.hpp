#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/listctrl.h>
#include <map>
#include "ControlPanel.hpp"
#include "helper.hpp"

namespace ow{
    class IOPanel : public wxPanel{
        public:
            IOPanel(wxWindow* parent);
            wxComboBox* pWeightComboBox;
            wxComboBox* pInfluenceComboBox;
            wxTextCtrl* pElemNameInput;
            wxListBox* pSourceElementsList;
            wxListBox* pTargetElementsList;
            void AddElement(wxString item);
        protected:
        private:
            void UpdateCombo(wxComboBox* pCombo, const std::map<int, wxString>& map);
        // handlers:
            void OnUpdate(wxCommandEvent& event);
            void OnAddElement(wxCommandEvent& event);
            void OnEnterText(wxCommandEvent& event);
    };
} // namespace ow