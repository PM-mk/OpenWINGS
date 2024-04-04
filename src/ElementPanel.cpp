#include "ElementPanel.hpp"
using namespace ow;

ElementPanel::ElementPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer;
	pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* pMainNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	wxPanel* pElementPanel = new wxPanel(pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pElementSizer;
	pElementSizer = new wxBoxSizer(wxVERTICAL);
	wxListCtrl* pElementList = new wxListCtrl(pElementPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_SORT_ASCENDING);
	pElementSizer->Add(pElementList, 1, wxALL|wxEXPAND, 5);
	pElementPanel->SetSizer(pElementSizer);
	pElementPanel->Layout();
	pElementSizer->Fit(pElementPanel);
	pMainNotebook->AddPage(pElementPanel, wxT("Elements"), true);

	wxPanel* pWeightPanel = new wxPanel(pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pWeightSizer;
	pWeightSizer = new wxBoxSizer(wxVERTICAL);
	wxListCtrl* pWeightList = new wxListCtrl(pWeightPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_SORT_ASCENDING);
	pWeightSizer->Add(pWeightList, 1, wxALL|wxEXPAND, 5);
	wxButton* pBtnEditScale = new wxButton(pWeightPanel, wxID_EDIT, wxT("Edit Scales"), wxDefaultPosition, wxDefaultSize, 0);
	pWeightSizer->Add(pBtnEditScale, 0, wxALIGN_RIGHT|wxALL, 5);
	pWeightPanel->SetSizer(pWeightSizer);
	pWeightPanel->Layout();
	pWeightSizer->Fit(pWeightPanel);
	pMainNotebook->AddPage(pWeightPanel, wxT("Weight"), false);

	wxPanel* pInfluencePanel = new wxPanel(pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pInfluenceSizer;
	pInfluenceSizer = new wxBoxSizer(wxVERTICAL);
	wxListCtrl* pInfluenceList = new wxListCtrl(pInfluencePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST|wxLC_SORT_ASCENDING);
	pInfluenceSizer->Add(pInfluenceList, 1, wxALL|wxEXPAND, 5);
	wxButton* pBtnEditScale1 = new wxButton(pInfluencePanel, wxID_EDIT, wxT("Edit Scales"), wxDefaultPosition, wxDefaultSize, 0);
	pInfluenceSizer->Add(pBtnEditScale1, 0, wxALIGN_RIGHT|wxALL, 5);
	pInfluencePanel->SetSizer(pInfluenceSizer);
	pInfluencePanel->Layout();
	pInfluenceSizer->Fit(pInfluencePanel);
	pMainNotebook->AddPage(pInfluencePanel, wxT("Influence"), false);

    // send events
    Bind(wxEVT_BUTTON, &ElementPanel::OnEditScales, this, wxID_EDIT);

	// finish frame
	pMainSizer->Add(pMainNotebook, 1, wxEXPAND | wxALL, 5);
	this->SetSizer(pMainSizer);
	this->Layout();

}

void ElementPanel::OnEditScales(wxCommandEvent& event){
	ScaleDialog* pScaleDialog = new ScaleDialog(this);
	pScaleDialog->ShowModal();
}
