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

	pWeightComboBox = new wxComboBox(pInputPanel, ID_WEIGHT_COMBO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER);
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

	wxBoxSizer* pRelationSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* pRelaEditSizer1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pRelaEditSizer2 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pRelaEditSizer3 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* pRelLabel1 = new wxStaticText(pInputPanel, wxID_ANY, wxT("System element(s)"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel1->Wrap(-1);
	pRelaEditSizer1->Add(pRelLabel1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* pRelLabel2 = new wxStaticText(pInputPanel, wxID_ANY, wxT("influence with strength"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel2->Wrap(-1);
	pRelaEditSizer2->Add(pRelLabel2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* pRelLabel3 = new wxStaticText(pInputPanel, wxID_ANY, wxT("the target element(s)"), wxDefaultPosition, wxDefaultSize, 0);
	pRelLabel3->Wrap(-1);
	pRelaEditSizer3->Add(pRelLabel3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	pSourceElementsList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pRelaEditSizer1->Add(pSourceElementsList, 1, wxALL|wxEXPAND, 5);

	pInfluenceComboBox = new wxComboBox(pInputPanel, ID_INFLUENCE_COMBO, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER);
	pRelaEditSizer2->Add(pInfluenceComboBox, 0, wxALIGN_CENTER|wxALL, 5);

	pTargetElementsList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pRelaEditSizer3->Add(pTargetElementsList, 1, wxALL|wxEXPAND, 5);

	pRelationSizer->Add(pRelaEditSizer1, 1, wxEXPAND, 5);
	pRelationSizer->Add(pRelaEditSizer2, 1, wxEXPAND, 5);
	pRelationSizer->Add(pRelaEditSizer3, 1, wxEXPAND, 5);

	wxButton* pBtnAddRelation = new wxButton(pInputPanel, ID_NEW_RELATION, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	pRelationSizer->Add(pBtnAddRelation, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	pMainInputSizer->Add(pRelationSizer, 1, wxEXPAND, 5);

	pRelationList = new wxListBox(pInputPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED|wxLB_NEEDED_SB);
	pMainInputSizer->Add(pRelationList, 1, wxALL|wxEXPAND, 5);

	wxButton* pBtnDeleteElement = new wxButton(pInputPanel, ID_DEL_ITEM, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	pBtnDeleteElement->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_BUTTON));
	pMainInputSizer->Add(pBtnDeleteElement, 0, wxALIGN_RIGHT|wxALL, 0);

	pInputPanel->SetSizer(pMainInputSizer);
	pInputPanel->Layout();
	pMainInputSizer->Fit(pInputPanel);
	pNotebook->AddPage(pInputPanel, wxT("Input"), true);
	// Wings page
	wxPanel* pWingsPanel = new wxPanel(pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pMainWingsSizer;
	pMainWingsSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pRunWingsBtnSizer;
	pRunWingsBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	pAbsValuesCheckbox = new wxCheckBox(pWingsPanel, wxID_ANY, wxT("Absolute values"), wxDefaultPosition, wxDefaultSize, 0);
	pRunWingsBtnSizer->Add(pAbsValuesCheckbox, 0, wxALL|wxEXPAND, 5);

	wxButton* pBtnCalculateWings = new wxButton(pWingsPanel, ID_RUN_WINGS, wxT("Run WINGS"), wxDefaultPosition, wxDefaultSize, 0);
	pRunWingsBtnSizer->Add(pBtnCalculateWings, 0, wxALL|wxEXPAND, 5);

	pMainWingsSizer->Add(pRunWingsBtnSizer, 0, wxALIGN_RIGHT, 5);
	// WINGS plot
    pWingsPlot = new mpWindow(pWingsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
	pWingsPlot->SetMPScrollbars(true);
	pMainWingsSizer->Add(pWingsPlot, 1, wxALL|wxEXPAND, 5);

	pWingsList = new wxListView(pWingsPanel, ID_WINGS_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	pWingsList->InsertColumn(0, wxT("Label"), 0, 225);
	pWingsList->InsertColumn(1, wxT("Impact"));
	pWingsList->InsertColumn(2, wxT("Receptivity"));
	pWingsList->InsertColumn(3, wxT("Involvement"));
	pWingsList->InsertColumn(4, wxT("Role"));
	pMainWingsSizer->Add(pWingsList, 1, wxALL|wxEXPAND, 5);
	pWingsPanel->SetSizer(pMainWingsSizer);
	pWingsPanel->Layout();
	pMainWingsSizer->Fit(pWingsPanel);
	pNotebook->AddPage(pWingsPanel, wxT("WINGS"), false);
	// Almodes page
	wxPanel* pAlmodesPanel = new wxPanel(pNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pMainAlmodesSizer;
	pMainAlmodesSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pRunAlmodesBtnSizer;
	pRunAlmodesBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* pAlmodesCtrlText = new wxStaticText(pAlmodesPanel, wxID_ANY, wxT("Time"), wxDefaultPosition, wxDefaultSize);
	pRunAlmodesBtnSizer->Add(pAlmodesCtrlText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);

	pAlmodesTimeCtrl = new wxSpinCtrl(pAlmodesPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 999, 10);
	pRunAlmodesBtnSizer->Add(pAlmodesTimeCtrl, 0, wxALL|wxEXPAND, 5);

	wxButton* pBtnCalculateAlmodes = new wxButton(pAlmodesPanel, ID_RUN_ALMODES, wxT("Run ALMODES"), wxDefaultPosition, wxDefaultSize, 0);
	pRunAlmodesBtnSizer->Add(pBtnCalculateAlmodes, 0, wxALL|wxEXPAND, 5);

	pMainAlmodesSizer->Add(pRunAlmodesBtnSizer, 0, wxALIGN_RIGHT, 5);
	// ALMODES plot
    pAlmodesPlot = new mpWindow(pAlmodesPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
	pAlmodesPlot->SetMPScrollbars(true);
	pMainAlmodesSizer->Add(pAlmodesPlot, 1, wxALL|wxEXPAND, 5);

	pAlmodesList = new wxListView(pAlmodesPanel, ID_ALMODES_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	pAlmodesList->InsertColumn(0, wxT("Label"), 0, 225);
	pAlmodesList->InsertColumn(1, wxT("Impact(t)"));
	pAlmodesList->InsertColumn(2, wxT("Receptivity(t)"));
	pAlmodesList->InsertColumn(3, wxT("Involvement(t)"));
	pAlmodesList->InsertColumn(4, wxT("Role(t)"));
	pMainAlmodesSizer->Add(pAlmodesList, 1, wxALL|wxEXPAND, 5);
	pAlmodesPanel->SetSizer(pMainAlmodesSizer);
	pAlmodesPanel->Layout();
	pMainAlmodesSizer->Fit(pAlmodesPanel);
	pNotebook->AddPage(pAlmodesPanel, wxT("ALMODES"), false);

	pMainSizer->Add(pNotebook, 1, wxEXPAND | wxALL, 5);
	// send events
    Bind(wxEVT_BUTTON, &IOPanel::OnUpdate, this, ID_UPDATE_ITEMS);
    Bind(wxEVT_BUTTON, &IOPanel::OnAddElement, this, ID_NEW_ELEMENT);
    Bind(wxEVT_BUTTON, &IOPanel::OnAddRelation, this, ID_NEW_RELATION);
    Bind(wxEVT_BUTTON, &IOPanel::OnDeleteRelation, this, ID_DEL_ITEM);
    Bind(wxEVT_TEXT_ENTER, &IOPanel::OnEnterText, this);
    Bind(wxEVT_BUTTON, &IOPanel::OnCalculateWings, this, ID_RUN_WINGS);
    Bind(wxEVT_BUTTON, &IOPanel::OnCalculateAlmodes, this, ID_RUN_ALMODES);
    Bind(wxEVT_LIST_ITEM_ACTIVATED, &IOPanel::OnActivateListItem, this, ID_WINGS_LIST);
    Bind(wxEVT_LIST_ITEM_ACTIVATED, &IOPanel::OnActivateListItem, this, ID_ALMODES_LIST);

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

void ow::IOPanel::OnDeleteRelation(wxCommandEvent &event){
	this->pRelationList->Freeze();
	for(auto i = 0; i<this->pRelationList->GetCount(); i++){
		if (this->pRelationList->IsSelected(i)){
			this->pRelationList->Delete(i--);
		}
	}
	this->pRelationList->Thaw();
}

void IOPanel::AddRelation(RelationshipData* pData){
	if (this->canAddRelation(pData)){
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

int IOPanel::getWeight(wxString& label){
    ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	long ndx = ow::findRecord(pControl->pSidePanel->pElementList, 1, label);
	wxString weightString = pControl->pSidePanel->pElementList->GetItemText(ndx, 0);
    return pControl->scaleStrToInt(weightString, true);
}

int IOPanel::getInfluence(wxString& label){
   ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
   return pControl->scaleStrToInt(label, false);
}

void IOPanel::deleteDependantRelations(wxString label){
	RelationshipData* pData = nullptr;
	this->pRelationList->Freeze();
	for(auto i = 0; i<this->pRelationList->GetCount(); i++){
		RelationshipData* pData = dynamic_cast<RelationshipData*>(this->pRelationList->GetClientObject(i));
		if (pData->source.label == label || pData->target.label == label){
			this->pRelationList->Delete(i--);
		}
	}
	this->pRelationList->Thaw();
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
	pCombo->SetSelection(0);
	pCombo->AutoComplete(pCombo->GetStrings());
}

void IOPanel::OnCalculateWings(wxCommandEvent &event){
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
	// transform matrix
	float scaleFactor = matrix.sum();
	matrix = matrix / scaleFactor; /* matrix = A/s */
	int n = matrix.cols();
	Matrix matrixIS = (Matrix::Identity(n, n) - matrix).inverse(); /* matrix = (I - S)^(-1) */
	matrix = matrix * matrixIS; /* matrix = S*[(I - S)^(-1)] = T */
	// calculate value vectors
	Vector impactVector = {};
	Vector receptivityVector = {};
	Vector involvementVector = {};
	Vector roleVector = {};
	wxString labelPrefix = wxEmptyString;

	if (this->pAbsValuesCheckbox->IsChecked()){ /* if mode = absolute values */
		matrix = matrix.cwiseAbs();
		impactVector = matrix.rowwise().sum();
		receptivityVector = matrix.colwise().sum();
		labelPrefix = wxT("Absolute");
	}
	else{
		impactVector = matrix.rowwise().sum().cwiseAbs();
		receptivityVector = matrix.colwise().sum().cwiseAbs();
		labelPrefix = wxT("Relative");
	}
	involvementVector = impactVector + receptivityVector;
	roleVector = impactVector - receptivityVector;
	// fill value table
	long ndx = 0;
	this->pWingsList->DeleteAllItems();
	this->pWingsList->Freeze();
	for (auto i = 0; i < n; i++){
		ndx = this->pWingsList->InsertItem(i, pControl->pSidePanel->pElementList->GetItemText(i, 1));
		this->pWingsList->SetItem(ndx, 1, wxString::Format(wxT("%f"), impactVector(i)));
		this->pWingsList->SetItem(ndx, 2, wxString::Format(wxT("%f"), receptivityVector(i)));
		this->pWingsList->SetItem(ndx, 3, wxString::Format(wxT("%f"), involvementVector(i)));
		this->pWingsList->SetItem(ndx, 4, wxString::Format(wxT("%f"), roleVector(i)));
	}
	this->pWingsList->Thaw();
	// plot WINGS
	this->pWingsPlot->DelAllLayers(true);
    mpScaleX* xAxis = new mpScaleX(labelPrefix + wxT(" involvement"), mpALIGN_CENTER, false, mpX_NORMAL);
    mpScaleY* yAxis = new mpScaleY(labelPrefix + wxT(" role"), mpALIGN_CENTER, false);
    pWingsPlot->AddLayer(xAxis, false);
    pWingsPlot->AddLayer(yAxis, false);
	std::vector<double> xDataVector = {};
	std::vector<double> yDataVector = {};
	mpFXYVector* pVectorLayer = nullptr;
	wxPen pen = wxPen(*wxBLUE, 5);
	for (auto i = 0; i < n; i++){
		xDataVector = {involvementVector[i]};
		yDataVector = {roleVector[i]};
		pVectorLayer = new mpFXYVector(pControl->pSidePanel->pElementList->GetItemText(i, 1));
		pVectorLayer->SetData(xDataVector, yDataVector);
		pVectorLayer->SetPen(pen);
		this->pWingsPlot->AddLayer(pVectorLayer, false);
		pVectorLayer->SetVisible(false);
	}
	this->pWingsPlot->UpdateAll();
}

void IOPanel::OnCalculateAlmodes(wxCommandEvent &event){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	int elementCount = pControl->pSidePanel->pElementList->GetItemCount();
	int relationCount = this->pRelationList->GetCount();
	if (elementCount >= 2 && relationCount){
		Matrix matrix = this->getMatrix();
		this->runAlmodes(matrix);
	}
}

void IOPanel::OnActivateListItem(wxListEvent &event){
	wxListView* pList = dynamic_cast<wxListView*>(event.GetEventObject());
	int listId = pList->GetId();
	mpWindow* pPlot = nullptr;
	if(listId == ID_WINGS_LIST){
		pPlot = this->pWingsPlot;
	}
	else if(listId == ID_ALMODES_LIST){
		pPlot = this->pAlmodesPlot;
	}

	mpLayer* pLayer = pPlot->GetLayerByName(event.GetItem().GetText());
	if(pLayer){
		bool isLayerVisible = pLayer->IsVisible();
		pLayer->SetVisible(!isLayerVisible);
		wxColor color = (isLayerVisible) ? *wxBLACK : *wxBLUE;
		pList->SetItemTextColour(event.GetItem().GetId(), color);
		pPlot->Fit();
	}
}

void IOPanel::runAlmodes(Matrix &matrix){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
	const unsigned int time = pAlmodesTimeCtrl->GetValue();
	// transform matrix
	float scaleFactor = matrix.sum();
	matrix = matrix / scaleFactor; /* matrix = A/s */
	int n = matrix.cols();
	Matrix matrixIS = (Matrix::Identity(n, n) - matrix).inverse(); /* matrix = (I - S)^(-1) */
	matrix = matrix * matrixIS; /* matrix = S*[(I - S)^(-1)] = T */

	Matrix matrixStateP = Matrix::Zero(time+1, n); /* vectors of element states for each time interval */
	Matrix matrixState = Matrix::Zero(n, time+1);
	for(auto i = 0; i < n; i++){ /* set initial state s(0) and s'(0) to 1's */
		matrixStateP(0, i) = 1;
		matrixState(i, 0) = 1;
	}
	Matrix matrixStatePAcc = Matrix(matrixStateP);
	Matrix matrixStateAcc = Matrix(matrixState);
	// calculate accumulated state vectors
	for(auto t = 0; t < time; t++){
		matrixStateP(t+1, Eigen::all) = matrixStateP(t, Eigen::all) * matrix;
		matrixStatePAcc(t+1, Eigen::all) = matrixStatePAcc(t, Eigen::all) + matrixStateP(t+1, Eigen::all);

		matrixState(Eigen::all, t+1) = matrix * matrixState(Eigen::all, t);
		matrixStateAcc(Eigen::all, t+1) = matrixStateAcc(Eigen::all, t) + matrixState(Eigen::all, t+1);
	}
	// fill table
	long ndx = 0;
	float impactT = 0;
	float receptivityT = 0;
	this->pAlmodesList->DeleteAllItems();
	this->pAlmodesList->Freeze();
	for (auto i = 0; i < n; i++){
		receptivityT = matrixStatePAcc(Eigen::last, i);
		impactT = matrixStateAcc(i, Eigen::last);
		ndx = this->pAlmodesList->InsertItem(i, pControl->pSidePanel->pElementList->GetItemText(i, 1));
		this->pAlmodesList->SetItem(ndx, 1, wxString::Format(wxT("%f"), impactT));
		this->pAlmodesList->SetItem(ndx, 2, wxString::Format(wxT("%f"), receptivityT));
		this->pAlmodesList->SetItem(ndx, 3, wxString::Format(wxT("%f"), impactT + receptivityT));
		this->pAlmodesList->SetItem(ndx, 4, wxString::Format(wxT("%f"), impactT - receptivityT));
	}
	this->pAlmodesList->Thaw();
	// plot almodes
	this->pAlmodesPlot->DelAllLayers(true);
    mpScaleX* xAxis = new mpScaleX(wxT("Time"), mpALIGN_CENTER, true, mpX_NORMAL);
    mpScaleY* yAxis = new mpScaleY(wxT("State"), mpALIGN_CENTER, false);
    pAlmodesPlot->AddLayer(xAxis, false);
    pAlmodesPlot->AddLayer(yAxis, false);
	std::vector<double> xDataVector(time+1);
	std::iota(std::begin(xDataVector), std::end(xDataVector), 0);
	std::vector<double> yDataVector = {};
	wxPen pen = wxPen(*wxBLUE, 2);
	mpFXYVector* pVectorLayer = nullptr;
	for (auto i = 0; i < n; i++){
		// copy each column to yDataVector
		yDataVector = columnToVector(matrixStatePAcc, i);
		pVectorLayer = new mpFXYVector(pControl->pSidePanel->pElementList->GetItemText(i, 1));
		pVectorLayer->SetData(xDataVector, yDataVector);
		pVectorLayer->SetContinuity(true);
		pVectorLayer->SetPen(pen);
		this->pAlmodesPlot->AddLayer(pVectorLayer, false);
		pVectorLayer->SetVisible(false);
	}
	this->pAlmodesPlot->UpdateAll();
}

std::vector<double> IOPanel::columnToVector(Matrix &matrix, const int& column){
	std::vector<double> vec = {};
	const int rows = matrix.rows();
	for (auto i = 0; i < rows; i++){
		vec.push_back(matrix(i, column));
	}
    return vec;
}
