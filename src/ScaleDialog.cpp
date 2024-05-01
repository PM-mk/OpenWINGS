#include "ScaleDialog.hpp"
using namespace ow;

ScaleDialog::ScaleDialog(wxWindow* parent) :
    wxDialog(parent, wxID_EDIT, "Scale Editor", wxDefaultPosition, wxSize(-1, 300), wxDEFAULT_DIALOG_STYLE){

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
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
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetParent());
	this->pWeightEditPanel->Update(pControl->weightsMap);
	this->pInfluenceEditPanel->Update(pControl->influencesMap);
}

void ScaleDialog::OnClose(wxCommandEvent& event){
	if (event.GetId() == wxID_OK){
		ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetParent());
		// save scale maps to memory
		this->pWeightEditPanel->Save(pControl->weightsMap);
		this->pInfluenceEditPanel->Save(pControl->influencesMap);
		// update combo boxes
		wxCommandEvent event = wxCommandEvent(wxEVT_BUTTON, ID_UPDATE_ITEMS);
		wxPostEvent(pControl->pIOPanel, event);
	}
	this->EndModal(1);
}