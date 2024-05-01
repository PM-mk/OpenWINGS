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

	pWeightComboBox = new wxComboBox(pInputPanel, ID_WEIGHT_COMBO, wxT("Weight..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER);
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
	pRelaEditSizer = new wxFlexGridSizer(2, 3, 0, 0);

	wxStaticText* pRelLabel1 = new wxStaticText(pInputPanel, wxID_ANY, wxT("System element(s)"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel1->Wrap(-1);
	pRelaEditSizer->Add(pRelLabel1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* pRelLabel2 = new wxStaticText(pInputPanel, wxID_ANY, wxT("influence with strength"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel2->Wrap(-1);
	pRelaEditSizer->Add(pRelLabel2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* pRelLabel3 = new wxStaticText(pInputPanel, wxID_ANY, wxT("the target element(s)"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel3->Wrap(-1);
	pRelaEditSizer->Add(pRelLabel3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pSourceElementsList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxSize(400,250), 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pRelaEditSizer->Add(pSourceElementsList, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pInfluenceComboBox = new wxComboBox(pInputPanel, ID_INFLUENCE_COMBO, wxT("Strength..."), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER);
	pRelaEditSizer->Add(pInfluenceComboBox, 0, wxALIGN_CENTER|wxALL, 5);

	pTargetElementsList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxSize(400,250), 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pRelaEditSizer->Add(pTargetElementsList, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);


	pRelationSizer->Add(pRelaEditSizer, 1, wxEXPAND, 5);

	wxButton* pBtnAddRelation = new wxButton(pInputPanel, ID_NEW_RELATION, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	pRelationSizer->Add(pBtnAddRelation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


	pMainInputSizer->Add(pRelationSizer, 0, wxEXPAND, 5);

	pRelationList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);

	pMainInputSizer->Add(pRelationList, 1, wxALL|wxEXPAND, 5);


	pInputPanel->SetSizer(pMainInputSizer);
	pInputPanel->Layout();
	pMainInputSizer->Fit(pInputPanel);
	pNotebook->AddPage(pInputPanel, wxT("Input"), true);
	wxPanel* pOutputPanel = new wxPanel(pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

	wxBoxSizer* pMainOutputSizer;
	pMainOutputSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pRunBtnSizer;
	pRunBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	pAbsValuesCheckbox = new wxCheckBox(pOutputPanel, wxID_ANY, wxT("Absolute values"), wxDefaultPosition, wxDefaultSize, 0);
	pRunBtnSizer->Add(pAbsValuesCheckbox, 0, wxALL|wxEXPAND, 5);

	wxButton* pBtnCalculate = new wxButton(pOutputPanel, ID_RUN_WINGS, wxT("Run WINGS"), wxDefaultPosition, wxDefaultSize, 0);
	pRunBtnSizer->Add(pBtnCalculate, 0, wxALL|wxEXPAND, 5);

	pMainOutputSizer->Add(pRunBtnSizer, 0, wxALIGN_RIGHT, 5);

    pWingsPlot = new mpWindow(pOutputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);

	pMainOutputSizer->Add(pWingsPlot, 1, wxALL|wxEXPAND, 5);

	pWingsList = new wxListView(pOutputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	pWingsList->InsertColumn(0, wxT("Label"), 0, 350);
	pWingsList->InsertColumn(1, wxT("Impact"));
	pWingsList->InsertColumn(2, wxT("Receptivity"));
	pWingsList->InsertColumn(3, wxT("Involvement"));
	pWingsList->InsertColumn(4, wxT("Role"));
	pMainOutputSizer->Add(pWingsList, 1, wxALL|wxEXPAND, 5);
	pOutputPanel->SetSizer(pMainOutputSizer);
	pOutputPanel->Layout();
	pMainOutputSizer->Fit(pOutputPanel);
	pNotebook->AddPage(pOutputPanel, wxT("WINGS"), false);

	pMainSizer->Add(pNotebook, 1, wxEXPAND | wxALL, 5);
	// send events
    Bind(wxEVT_BUTTON, &IOPanel::OnUpdate, this, ID_UPDATE_ITEMS);
    Bind(wxEVT_BUTTON, &IOPanel::OnAddElement, this, ID_NEW_ELEMENT);
    Bind(wxEVT_BUTTON, &IOPanel::OnAddRelation, this, ID_NEW_RELATION);
    Bind(wxEVT_TEXT_ENTER, &IOPanel::OnEnterText, this);
    Bind(wxEVT_BUTTON, &IOPanel::OnCalculate, this, ID_RUN_WINGS);

	this->SetSizer(pMainSizer);
	this->Layout();
}

void IOPanel::AddElement(const wxString& item){
	this->pSourceElementsList->Insert(item, 0);
	this->pTargetElementsList->Insert(item, 0);
}

void IOPanel::OnUpdate(wxCommandEvent& event){
    ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	this->UpdateCombo(this->pWeightComboBox, pControl->weightsMap);
	this->UpdateCombo(this->pInfluenceComboBox, pControl->influencesMap);
}

void IOPanel::OnAddElement(wxCommandEvent& event){
	wxString elementLabel = this->pElemNameInput->GetValue().Trim().Trim(false);
	wxString weightLabel = this->pWeightComboBox->GetStringSelection();
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	if (elementLabel != wxEmptyString &&
		this->pWeightComboBox->FindString(weightLabel) != wxNOT_FOUND &&
		pControl->pSidePanel->canAddElement(elementLabel)){

		this->AddElement(elementLabel);
		wxPostEvent(pControl->pSidePanel, event); /* fire OnAdd in ElementPanel*/
		this->pElemNameInput->SetFocus();
	}
	else{
		wxBell();
	}
}

void IOPanel::OnAddRelation(wxCommandEvent& event){
	wxString influenceLabel = this->pInfluenceComboBox->GetStringSelection();
	if (this->pInfluenceComboBox->FindString(influenceLabel) != wxNOT_FOUND){
		wxArrayInt sourceIndices = {};
		wxArrayInt targetIndices = {};
		int sourceCount = this->pSourceElementsList->GetSelections(sourceIndices);
		int targetCount = this->pTargetElementsList->GetSelections(targetIndices);
		if(sourceCount && targetCount){
			wxString targetLabel = wxEmptyString;
			wxString sourceLabel = wxEmptyString;
			RelationshipData* pData = nullptr;
			for(const auto& sourceNdx : sourceIndices){
				wxString sourceLabel = this->pSourceElementsList->GetString(sourceNdx);
				for(const auto& targetNdx : targetIndices){
					targetLabel = this->pTargetElementsList->GetString(targetNdx);
					pData = new RelationshipData(
						RelationshipData::CreateItem(this->getWeight(sourceLabel), sourceLabel),
						this->getInfluence(influenceLabel),
						RelationshipData::CreateItem(this->getWeight(targetLabel), targetLabel)
					);
					this->AddRelation(pData);
				}
			}
		}
	}
}

void IOPanel::AddRelation(RelationshipData* pData){
	if (this->canAddRelation(pData)){
		// construct text
		wxString text = this->getRelationText(pData);
		this->pRelationList->Append(text, pData);
	}
	else{
		delete pData;
	}
}

bool IOPanel::canAddRelation(RelationshipData *pData){
	for(auto i = 0; i<this->pRelationList->GetCount(); i++){
		if (*dynamic_cast<RelationshipData*>(this->pRelationList->GetClientObject(i)) == *pData){
			return false;
		}
	}
    return true;
}

wxString IOPanel::getRelationText(RelationshipData *pData){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	if(pData->source.label == pData->target.label){
		return wxString::Format(wxT("System element %s is affecting itself with %s intensity."),
			pData->source.label, pControl->influencesMap.find(pData->influenceValue)->second);
	}
	else{
		return wxString::Format(wxT("System element %s is affecting the element %s with %s intensity."),
			pData->source.label, pData->target.label, pControl->influencesMap.find(pData->influenceValue)->second);
	}
}

int IOPanel::getWeight(wxString label){
    ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	long ndx = ow::findRecord(pControl->pSidePanel->pElementList, 1, label);
	wxString weightString = pControl->pSidePanel->pElementList->GetItemText(ndx, 0);
    return pControl->scaleStrToInt(weightString, true);
}

int IOPanel::getInfluence(wxString label){
   ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
   return pControl->scaleStrToInt(label, false);
}

void IOPanel::OnEnterText(wxCommandEvent& event){
	wxComboBox* pCombo = dynamic_cast<wxComboBox*>(event.GetEventObject());
	wxString str = pCombo->GetValue();
	int ndx = pCombo->FindString(str);
	if (ndx != wxNOT_FOUND){
		pCombo->SetSelection(ndx);
		if (pCombo->GetId() == ID_WEIGHT_COMBO){
			this->pElemNameInput->SetFocus();
		}
		else{
			this->pTargetElementsList->SetFocus();
		}
	}
}

void IOPanel::UpdateCombo(wxComboBox *pCombo, const std::map<int, wxString> &map)
{
    pCombo->Clear();
	for(const auto& pair : map){
		pCombo->Append(pair.second);
    }
	pCombo->AutoComplete(pCombo->GetStrings());
}

void IOPanel::OnCalculate(wxCommandEvent &event){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	int elementCount = pControl->pSidePanel->pElementList->GetItemCount();
	int relationCount = this->pRelationList->GetCount();
	if (elementCount >= 2 && relationCount){
		Matrix matrix = this->getMatrix();
		this->runWings(matrix);
	}
}

Matrix IOPanel::getMatrix(){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	int elementCount = pControl->pSidePanel->pElementList->GetItemCount();
	Matrix matrix = Matrix::Zero(elementCount, elementCount);
	int value = 0;
	// fill weight values
	for(int i = 0; i<elementCount; i++){
		value = pControl->scaleStrToInt(pControl->pSidePanel->pElementList->GetItemText(i, 0), true);
		matrix(i, i) += value;
	}
	// fill influence values
	int relationCount = this->pRelationList->GetCount();
	RelationshipData* pData = nullptr;
	int x = 0;
	int y = 0;
	for(int i = 0; i<relationCount; i++){
		pData = dynamic_cast<RelationshipData*>(this->pRelationList->GetClientObject(i));
		x = ow::findRecord(pControl->pSidePanel->pElementList, 1, pData->source.label);
		y = ow::findRecord(pControl->pSidePanel->pElementList, 1, pData->target.label);
		matrix(x, y) += pData->influenceValue;
	}
    return matrix;
}

void IOPanel::runWings(Matrix& matrix){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	bool absoluteMode = this->pAbsValuesCheckbox->IsChecked();

	float scaleFactor = matrix.sum();
	matrix = matrix / scaleFactor; /* matrix = A/s */
	int n = matrix.cols();
	Matrix matrixIS = (Matrix::Identity(n, n) - matrix).inverse(); /* matrix = (I - S)^(-1) */
	matrix = matrix * matrixIS; /* matrix = S*[(I - S)^(-1)] = T */

	Vector impactVector = {};
	Vector receptivityVector = {};
	Vector involvementVector = {};
	Vector roleVector = {};

	if (this->pAbsValuesCheckbox->IsChecked()){ /* if mode = absolute values */
		matrix = matrix.cwiseAbs();
		impactVector = matrix.rowwise().sum();
		receptivityVector = matrix.colwise().sum();
	}
	else{
		impactVector = matrix.rowwise().sum().cwiseAbs();
		receptivityVector = matrix.colwise().sum().cwiseAbs();
	}
	involvementVector = impactVector + receptivityVector;
	roleVector = impactVector - receptivityVector;

	long record = 0;
	long ndx = 0;
	this->pWingsList->DeleteAllItems();
	for (auto i = 0; i < n; i++){
		ndx = this->pWingsList->InsertItem(record++, pControl->pSidePanel->pElementList->GetItemText(i, 1));
		this->pWingsList->SetItem(ndx, 1, wxString::Format(wxT("%f"), impactVector(i)));
		this->pWingsList->SetItem(ndx, 2, wxString::Format(wxT("%f"), receptivityVector(i)));
		this->pWingsList->SetItem(ndx, 3, wxString::Format(wxT("%f"), involvementVector(i)));
		this->pWingsList->SetItem(ndx, 4, wxString::Format(wxT("%f"), roleVector(i)));
	}
}
