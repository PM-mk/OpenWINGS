#include "ScalePanel.hpp"
using namespace ow;

ScalePanel::ScalePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
    wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* pScaleEditSizer;
    pScaleEditSizer = new wxBoxSizer(wxHORIZONTAL);

    wxTextCtrl* pTextValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), wxTE_RIGHT,
        wxMakeIntegerValidator(&value));
    pTextValue->SetMaxSize(wxSize(50,-1));

    pScaleEditSizer->Add(pTextValue, 1, wxALL, 5);

    wxTextCtrl* pTextName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    pScaleEditSizer->Add(pTextName, 1, wxALL, 5);

    wxButton* pBtnScaleAdd = new wxButton(this, wxID_ADD, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    pScaleEditSizer->Add(pBtnScaleAdd, 0, wxALL, 5);


    pMainSizer->Add(pScaleEditSizer, 0, wxEXPAND, 5);

    wxBoxSizer* scaleGridSizer;
    scaleGridSizer = new wxBoxSizer(wxHORIZONTAL);

    pScaleList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_DESCENDING);
	pScaleList->InsertColumn(0, "Value", 0, 50);
	pScaleList->InsertColumn(1, "Name", 0, 227);
    long ndx = pScaleList->InsertItem(0, "0");
    pScaleList->SetItem(ndx, 1, "NONE");
    ndx = pScaleList->InsertItem(1, "1");
    pScaleList->SetItem(ndx, 1, "LOW");
    ndx = pScaleList->InsertItem(2, "2");
    pScaleList->SetItem(ndx, 1, "MEDIUM");
    ndx = pScaleList->InsertItem(3, "3");
    pScaleList->SetItem(ndx, 1, "HIGH");
    ndx = pScaleList->InsertItem(4, "4");
    pScaleList->SetItem(ndx, 1, "VERY HIGH");
    scaleGridSizer->Add(pScaleList, 1, wxALL|wxEXPAND, 5);

    wxButton* pBtnScaleDelete = new wxButton(this, wxID_DELETE, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0);
    scaleGridSizer->Add(pBtnScaleDelete, 0, wxALL, 5);


    pMainSizer->Add(scaleGridSizer, 1, wxEXPAND, 5);

    wxBoxSizer* pBottomBtnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* pBtnScaleClear = new wxButton(this, wxID_CLEAR, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0);
    pBottomBtnSizer->Add(pBtnScaleClear, 0, wxALL, 5);
    pMainSizer->Add(pBottomBtnSizer, 0, wxEXPAND, 5);

    Bind(wxEVT_BUTTON, &ScalePanel::OnAdd, this, wxID_ADD);
    Bind(wxEVT_BUTTON, &ScalePanel::OnDelete, this, wxID_DELETE);
    Bind(wxEVT_BUTTON, &ScalePanel::OnClear, this, wxID_CLEAR);
    // finish frame
    this->SetSizer(pMainSizer);
    this->Layout();
}

void ScalePanel::OnAdd(wxCommandEvent& event){
}

void ow::ScalePanel::OnDelete(wxCommandEvent &event){
}

void ow::ScalePanel::OnClear(wxCommandEvent &event){
    this->pScaleList->DeleteAllItems();
}