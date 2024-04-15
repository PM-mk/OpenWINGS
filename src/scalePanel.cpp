#include "ScalePanel.hpp"
using namespace ow;

ScalePanel::ScalePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
    wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* pScaleEditSizer;
    pScaleEditSizer = new wxBoxSizer(wxHORIZONTAL);

    pTextValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), wxTE_RIGHT,
        wxMakeIntegerValidator(&value));
    pTextValue->SetMaxSize(wxSize(50,-1));
    pScaleEditSizer->Add(pTextValue, 1, wxALL, 5);

    pTextLabel = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    pScaleEditSizer->Add(pTextLabel, 1, wxALL, 5);

    wxButton* pBtnScaleAdd = new wxButton(this, wxID_ADD, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    pScaleEditSizer->Add(pBtnScaleAdd, 0, wxALL, 5);


    pMainSizer->Add(pScaleEditSizer, 0, wxEXPAND, 5);

    wxBoxSizer* scaleGridSizer;
    scaleGridSizer = new wxBoxSizer(wxHORIZONTAL);

    pScaleList = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_DESCENDING);
	pScaleList->InsertColumn(0, "Value", 0, 50);
	pScaleList->InsertColumn(1, "Label", 0, 227);
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

void ScalePanel::Update(const std::map<int, wxString>& map){
    long ndx = 0;
    int recordNumber = 0;
    wxString scaleValue = "";
    for(const auto& pair : map){
        scaleValue = wxString::Format(wxT("%i"), pair.first);
        ndx = this->pScaleList->InsertItem(recordNumber++, scaleValue);
        this->pScaleList->SetItem(ndx, 1, pair.second); /*scaleLabel*/
    };
}

void ow::ScalePanel::Save(std::map<int, wxString>& map){
    map.clear();
    for(auto i = 0; i<this->pScaleList->GetItemCount(); i++){
        int scaleValue = wxAtoi(GetCellContentsString(this->pScaleList, i, 0));
        wxString scaleLabel = GetCellContentsString(this->pScaleList, i, 1);
        map.insert({scaleValue, scaleLabel});
    }
}

void ScalePanel::OnAdd(wxCommandEvent& event){
    long ndx = this->pScaleList->InsertItem(0, this->pTextValue->GetValue());
    this->pScaleList->SetItem(ndx, 1, this->pTextLabel->GetValue());
}

void ow::ScalePanel::OnDelete(wxCommandEvent &event){
    long itemID = this->pScaleList->GetFirstSelected();
    this->pScaleList->DeleteItem(itemID);
}

void ow::ScalePanel::OnClear(wxCommandEvent &event){
    this->pScaleList->DeleteAllItems();
}