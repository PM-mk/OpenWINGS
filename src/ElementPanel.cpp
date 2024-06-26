#include "ElementPanel.hpp"
using namespace ow;

ElementPanel::ElementPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer;
	pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* pMainNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
	wxPanel* pElementPanel = new wxPanel(pMainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* pElementSizer;
	pElementSizer = new wxBoxSizer(wxVERTICAL);
	pElementList = new wxListView(pElementPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_ASCENDING|wxLC_SINGLE_SEL);
	pElementList->InsertColumn(0, wxT("Weight"), 0, 50);
	pElementList->InsertColumn(1, wxT("Name"), 0, pElementList->GetSize().x-135-50);
	pElementSizer->Add(pElementList, 1, wxALL|wxEXPAND, 5);

	wxButton* pBtnDeleteElement = new wxButton(pElementPanel, ID_DEL_ITEM, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	pBtnDeleteElement->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_BUTTON));
	pElementSizer->Add(pBtnDeleteElement, 0, wxALIGN_RIGHT|wxALL, 0);

	pElementPanel->SetSizer(pElementSizer);
	pElementPanel->Layout();
	pElementSizer->Fit(pElementPanel);
	pMainNotebook->AddPage(pElementPanel, wxT("Elements"), true);

    // send events
    Bind(wxEVT_MENU, &ElementPanel::OnEditScales, this, wxID_EDIT);
    Bind(wxEVT_BUTTON, &ElementPanel::OnAdd, this, ID_NEW_ELEMENT);
    Bind(wxEVT_BUTTON, &ElementPanel::OnDelete, this, ID_DEL_ITEM);

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

void ElementPanel::OnAdd(wxCommandEvent& event){
	ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
    long ndx = this->pElementList->InsertItem(0, pControl->pIOPanel->pWeightComboBox->GetValue());
    this->pElementList->SetItem(ndx, 1, pControl->pIOPanel->pElemNameInput->GetValue().Trim().Trim(false));
}

void ElementPanel::OnDelete(wxCommandEvent& event){
	long ndx = this->pElementList->GetFirstSelected();
	if(ndx != wxNOT_FOUND){
		wxString elementLabel = this->pElementList->GetItemText(ndx, 1);
		if(Ask(this, wxString::Format(wxT("Are you sure you want to delete element \"%s\"?\n%s"), elementLabel,
				wxT("All relations that depend on this element will be deleted as well."))))
		{
			ControlPanel* pControl = dynamic_cast<ControlPanel*>(this->GetGrandParent());
			pControl->pIOPanel->deleteDependantRelations(elementLabel);
			pControl->pIOPanel->pSourceElementsList->Delete(pControl->pIOPanel->pSourceElementsList->FindString(elementLabel));
			pControl->pIOPanel->pTargetElementsList->Delete(pControl->pIOPanel->pTargetElementsList->FindString(elementLabel));
			this->pElementList->DeleteItem(ndx);
		}
	}
}