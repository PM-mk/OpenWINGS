#include "ElementPanel.hpp"
using namespace ow;

ElementPanel::ElementPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer;
	pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* pMainNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	wxPanel* pElementPanel = new wxPanel(pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pElementSizer;
	pElementSizer = new wxBoxSizer(wxVERTICAL);
	pElementList = new wxListView(pElementPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_ASCENDING);
	pElementList->InsertColumn(0, wxT("Weight"), 0, 50);
	pElementList->InsertColumn(1, wxT("Name"), 0, pElementList->GetSize().x-135-50);

	pElementSizer->Add(pElementList, 1, wxALL|wxEXPAND, 5);
	wxButton* pBtnEditScale = new wxButton(pElementPanel, wxID_EDIT, wxT("Edit Scales"), wxDefaultPosition, wxDefaultSize, 0);
	pElementSizer->Add(pBtnEditScale, 0, wxALIGN_RIGHT|wxALL, 5);
	pElementPanel->SetSizer(pElementSizer);
	pElementPanel->Layout();
	pElementSizer->Fit(pElementPanel);
	pMainNotebook->AddPage(pElementPanel, wxT("Elements"), true);

    // send events
    Bind(wxEVT_BUTTON, &ElementPanel::OnEditScales, this, wxID_EDIT);
    Bind(wxEVT_BUTTON, &ElementPanel::OnAdd, this, ID_NEW_ELEMENT);

	// finish frame
	pMainSizer->Add(pMainNotebook, 1, wxEXPAND | wxALL, 5);
	this->SetSizer(pMainSizer);
	this->Layout();
}

bool ElementPanel::canAddElement(const wxString& label){
	return ow::findRecord(this->pElementList, 1, label) == -1;
}

void ElementPanel::OnEditScales(wxCommandEvent& event){
	ScaleDialog* pScaleDialog = new ScaleDialog(this->GetGrandParent());
	pScaleDialog->LoadScales();
	// load scales from map here
	pScaleDialog->ShowModal();
}

void ElementPanel::OnAdd(wxCommandEvent &event){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
    long ndx = this->pElementList->InsertItem(0, pControl->pIOPanel->pWeightComboBox->GetValue());
    this->pElementList->SetItem(ndx, 1, pControl->pIOPanel->pElemNameInput->GetValue());
}