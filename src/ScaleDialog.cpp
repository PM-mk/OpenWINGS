#include "ScaleDialog.hpp"
using namespace ow;

ScaleDialog::ScaleDialog(wxWindow* parent) :
    wxDialog(parent, wxID_EDIT, "Scale Editor", wxDefaultPosition, wxSize(-1, 300), wxDEFAULT_DIALOG_STYLE){

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	wxNotebook* pEditNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	pWeightEditPanel = new ScalePanel(pEditNotebook);
	pEditNotebook->AddPage(pWeightEditPanel, wxT("Weight"), false);

	pInfluenceEditPanel = new ScalePanel(pEditNotebook);
	pEditNotebook->AddPage(pInfluenceEditPanel, wxT("Influence"), false);

	bSizer5->Add(pEditNotebook, 1, wxEXPAND | wxALL, 5);

	wxStdDialogButtonSizer* m_sdbSizer1 = new wxStdDialogButtonSizer();
	wxButton* pBtnOK = new wxButton(this, wxID_OK);
	m_sdbSizer1->AddButton(pBtnOK);
	wxButton* pBtnCancel = new wxButton(this, wxID_CANCEL);
	m_sdbSizer1->AddButton(pBtnCancel);
	m_sdbSizer1->Realize();

	bSizer5->Add(m_sdbSizer1, 0, wxALL|wxEXPAND, 5);

    Bind(wxEVT_BUTTON, &ScaleDialog::OnClose, this, wxID_OK);
    Bind(wxEVT_BUTTON, &ScaleDialog::OnClose, this, wxID_CANCEL);

	this->SetSizer(bSizer5);
	this->Layout();
	this->CenterOnParent(wxBOTH);
}

void ow::ScaleDialog::LoadScales(){
	this->pWeightEditPanel->Update(dynamic_cast<ControlPanel*>(this->GetParent())->weightsMap);
	this->pInfluenceEditPanel->Update(dynamic_cast<ControlPanel*>(this->GetParent())->influencesMap);
}

void ScaleDialog::OnClose(wxCommandEvent& event){
	if (event.GetId() == wxID_OK){
		// dump list ctrl values into user scale maps
		// manually fire update events for combo boxes
		// 		controlpanel->maincontrol->get 1st page of notebook->combo1 and combo2
	}
	this->EndModal(wxID_OK);
}