#include "IOPanel.hpp"
using namespace ow;

IOPanel::IOPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer;
	pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* pNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	wxPanel* pInputPanel = new wxPanel(pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pMainInputSizer;
	pMainInputSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pElemEditSizer;
	pElemEditSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* pElemLabel1 = new wxStaticText(pInputPanel, wxID_ANY, wxT("Weight"), wxDefaultPosition, wxDefaultSize, 0);
	pElemLabel1->Wrap(-1);
	pElemEditSizer->Add(pElemLabel1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	pWeightComboBox = new wxComboBox(pInputPanel, wxID_ANY, wxT("Weight..."), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	pElemEditSizer->Add(pWeightComboBox, 0, wxALL, 5);

	wxStaticText* pElemLabel2 = new wxStaticText(pInputPanel, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
	pElemLabel2->Wrap(-1);
	pElemEditSizer->Add(pElemLabel2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	pElemNameInput = new wxTextCtrl(pInputPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	pElemEditSizer->Add(pElemNameInput, 1, wxALL, 5);

	wxButton* pBtnAddElement = new wxButton(pInputPanel, ID_NEW_ELEMENT, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	pElemEditSizer->Add(pBtnAddElement, 0, wxALL, 5);


	pMainInputSizer->Add(pElemEditSizer, 0, wxEXPAND, 5);

	wxStaticLine* pStaticLine = new wxStaticLine(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	pMainInputSizer->Add(pStaticLine, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* pRelationSizer;
	pRelationSizer = new wxBoxSizer(wxHORIZONTAL);

	wxGridSizer* pRelaEditSizer;
	pRelaEditSizer = new wxGridSizer(3, 3, 0, 0);

	wxStaticText* pRelLabel1 = new wxStaticText(pInputPanel, wxID_ANY, wxT("System element(s)"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel1->Wrap(-1);
	pRelaEditSizer->Add(pRelLabel1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* pRelLabel2 = new wxStaticText(pInputPanel, wxID_ANY, wxT("influence with strength"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel2->Wrap(-1);
	pRelaEditSizer->Add(pRelLabel2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* pRelLabel3 = new wxStaticText(pInputPanel, wxID_ANY, wxT("the target element(s)"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel3->Wrap(-1);
	pRelaEditSizer->Add(pRelLabel3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pSourceElementsList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pRelaEditSizer->Add(pSourceElementsList, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pInfluenceComboBox = new wxComboBox(pInputPanel, wxID_ANY, wxT("Strength..."), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	pRelaEditSizer->Add(pInfluenceComboBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pTargetElementsList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pRelaEditSizer->Add(pTargetElementsList, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);


	pRelationSizer->Add(pRelaEditSizer, 1, wxEXPAND, 5);

	wxButton* pBtnAddRelation = new wxButton(pInputPanel, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	pRelationSizer->Add(pBtnAddRelation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


	pMainInputSizer->Add(pRelationSizer, 0, wxEXPAND, 5);

	wxListCtrl* pRelationList = new wxListCtrl(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST);
	pRelationList->SetMinSize(wxSize(-1,350));

	pMainInputSizer->Add(pRelationList, 1, wxALL|wxEXPAND, 5);


	pInputPanel->SetSizer(pMainInputSizer);
	pInputPanel->Layout();
	pMainInputSizer->Fit(pInputPanel);
	pNotebook->AddPage(pInputPanel, wxT("Input"), true);
	wxPanel* pOutputPanel = new wxPanel(pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	pOutputPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	wxBoxSizer* pMainOutputSizer;
	pMainOutputSizer = new wxBoxSizer(wxVERTICAL);

	wxButton* pBtnCalculate = new wxButton(pOutputPanel, wxID_ANY, wxT("Calculate!"), wxDefaultPosition, wxDefaultSize, 0);
	pMainOutputSizer->Add(pBtnCalculate, 0, wxALIGN_RIGHT|wxALL, 5);


	pOutputPanel->SetSizer(pMainOutputSizer);
	pOutputPanel->Layout();
	pMainOutputSizer->Fit(pOutputPanel);
	pNotebook->AddPage(pOutputPanel, wxT("Output"), false);

	pMainSizer->Add(pNotebook, 1, wxEXPAND | wxALL, 5);
	// send events
    Bind(wxEVT_BUTTON, &IOPanel::OnUpdate, this, ID_UPDATE_ITEMS);
    Bind(wxEVT_BUTTON, &IOPanel::OnAddElement, this, ID_NEW_ELEMENT);

	this->SetSizer(pMainSizer);
	this->Layout();
}

void IOPanel::OnUpdate(wxCommandEvent &event){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	this->UpdateCombo(this->pWeightComboBox, pControl->weightsMap);
	this->UpdateCombo(this->pInfluenceComboBox, pControl->influencesMap);
}

void IOPanel::OnAddElement(wxCommandEvent &event){
	// pack this into a seperate function:
	this->pSourceElementsList->Insert(this->pElemNameInput->GetValue(), 0);
	this->pTargetElementsList->Insert(this->pElemNameInput->GetValue(), 0);
	wxCommandEvent newEvent = wxCommandEvent(wxEVT_BUTTON, ID_NEW_ELEMENT);
	wxPostEvent(dynamic_cast<ControlPanel*>(this->GetGrandParent())->pSidePanel, newEvent);
}

void IOPanel::UpdateCombo(wxComboBox *combo, const std::map<int, wxString> &map){
    combo->Clear();
	for(const auto& pair : map){
		combo->Append(pair.second);
    };
}
