#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/artprov.h>
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <map>
#include "ControlPanel.hpp"
#include "helper.hpp"
#include "RelationshipData.hpp"
#include <Eigen/Dense>
#include "mathplot.h"


using Matrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
using Vector = Eigen::Vector<float, Eigen::Dynamic>;

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
            wxCheckBox* pAbsValuesCheckbox;
            wxListView* pWingsList;
            wxListView* pAlmodesList;
            mpWindow* pWingsPlot;
            mpWindow* pAlmodesPlot;
            wxSpinCtrl* pAlmodesTimeCtrl;
            void AddElement(const wxString& item);
            void AddRelation(RelationshipData* pData);
            bool canAddRelation(RelationshipData* pData);
            wxString getRelationText(RelationshipData* pData);
            int getWeight(wxString& label);
            int getInfluence(wxString& label);
            void deleteDependantRelations(wxString label);
        protected:
        private:
            Matrix getMatrix();
            void UpdateCombo(wxComboBox* pCombo, const std::map<int, wxString>& map);
            void runWings(Matrix& matrix);
        // handlers:
            void OnUpdate(wxCommandEvent& event);
            void OnAddElement(wxCommandEvent& event);
            void OnAddRelation(wxCommandEvent& event);
            void OnDeleteRelation(wxCommandEvent& event);
            void OnEnterText(wxCommandEvent& event);
            void OnCalculateWings(wxCommandEvent& event);
            void OnCalculateAlmodes(wxCommandEvent& event);
    };
} // namespace ow