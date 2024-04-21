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
#include "RelationshipData.hpp"

namespace ow{
    class IOPanel : public wxPanel{
        public:
            IOPanel(wxWindow* parent);
            wxComboBox* pWeightComboBox;
            wxComboBox* pInfluenceComboBox;
            wxTextCtrl* pElemNameInput;
            wxListBox* pSourceElementsList;
            wxListBox* pTargetElementsList;
            wxListBox* pRelationList;
            void AddElement(const wxString& item);
            void AddRelation(RelationshipData* pData);
            bool canAddRelation(RelationshipData* pData);
            wxString getRelationText(RelationshipData* pData);
            int getWeight(wxString label);
            int getInfluence(wxString label);
        protected:
        private:
            void UpdateCombo(wxComboBox* pCombo, const std::map<int, wxString>& map);
        // handlers:
            void OnUpdate(wxCommandEvent& event);
            void OnAddElement(wxCommandEvent& event);
            void OnAddRelation(wxCommandEvent& event);
            void OnEnterText(wxCommandEvent& event);
    };
} // namespace ow