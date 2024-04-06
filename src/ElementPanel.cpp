#include "ElementPanel.hpp"
using namespace ow;

ElementPanel::ElementPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer;
	pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* pMainNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	wxPanel* pElementPanel = new wxPanel(pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pElementSizer;
	pElementSizer = new wxBoxSizer(wxVERTICAL);
	pElementList = new wxListCtrl(pElementPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_ASCENDING);
	pElementList->InsertColumn(0, wxT("Weight value"), 0, 0);
	pElementList->InsertColumn(1, wxT("Weight"), 0, 50);
	pElementList->InsertColumn(2, wxT("Name"), 0, pElementList->GetSize().x-135-50);

	pElementSizer->Add(pElementList, 1, wxALL|wxEXPAND, 5);
	wxButton* pBtnEditScale = new wxButton(pElementPanel, wxID_EDIT, wxT("Edit Scales"), wxDefaultPosition, wxDefaultSize, 0);
	pElementSizer->Add(pBtnEditScale, 0, wxALIGN_RIGHT|wxALL, 5);
	pElementPanel->SetSizer(pElementSizer);
	pElementPanel->Layout();
	pElementSizer->Fit(pElementPanel);
	pMainNotebook->AddPage(pElementPanel, wxT("Elements"), true);

    // send events
    Bind(wxEVT_BUTTON, &ElementPanel::OnEditScales, this, wxID_EDIT);

	// finish frame
	pMainSizer->Add(pMainNotebook, 1, wxEXPAND | wxALL, 5);
	this->SetSizer(pMainSizer);
	this->Layout();

}

void ElementPanel::OnEditScales(wxCommandEvent& event){
	ScaleDialog* pScaleDialog = new ScaleDialog(this->GetGrandParent());
	pScaleDialog->ShowModal();
}
