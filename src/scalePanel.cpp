#include "ScalePanel.hpp"
using namespace ow;

ScalePanel::ScalePanel(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
    wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* pTitle = new wxStaticText(this, wxID_ANY, title,
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    pTitle->Wrap(-1);
   pMainSizer->Add(pTitle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP, 5);

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

    wxDataViewListCtrl* pScaleData = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES);
    wxDataViewColumn* pColValue = pScaleData->AppendTextColumn(wxT("Value"), wxDATAVIEW_CELL_INERT, 50, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_SORTABLE);
    wxDataViewColumn* pColName = pScaleData->AppendTextColumn(wxT("Name"), wxDATAVIEW_CELL_EDITABLE, 170, static_cast<wxAlignment>(wxALIGN_LEFT), 0);
    scaleGridSizer->Add(pScaleData, 1, wxALL|wxEXPAND, 5);

    wxButton* pBtnScaleDelete = new wxButton(this, wxID_DELETE, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0);
    scaleGridSizer->Add(pBtnScaleDelete, 0, wxALL, 5);


    pMainSizer->Add(scaleGridSizer, 1, wxEXPAND, 5);

    wxBoxSizer* pBottomBtnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* pBtnScaleDefault = new wxButton(this, ID_SET_DEFAULT, wxT("Reset to default"), wxDefaultPosition, wxDefaultSize, 0);
    pBottomBtnSizer->Add(pBtnScaleDefault, 0, wxALL, 5);

    wxButton* pBtnScaleClear = new wxButton(this, wxID_CLEAR, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0);
    pBottomBtnSizer->Add(pBtnScaleClear, 0, wxALL, 5);
    pMainSizer->Add(pBottomBtnSizer, 0, wxEXPAND, 5);

    Bind(wxEVT_BUTTON, &ScalePanel::OnAdd, this, wxID_ADD);
    Bind(wxEVT_BUTTON, &ScalePanel::OnDelete, this, wxID_DELETE);
    Bind(wxEVT_BUTTON, &ScalePanel::OnClear, this, wxID_CLEAR);
    Bind(wxEVT_BUTTON, &ScalePanel::OnSetDefault, this, ID_SET_DEFAULT);
    // finish frame
    this->SetSizer(pMainSizer);
    this->Layout();
}

void ScalePanel::OnAdd(wxCommandEvent& event){
}

void ow::ScalePanel::OnDelete(wxCommandEvent &event){
}

void ow::ScalePanel::OnClear(wxCommandEvent &event){
}

void ow::ScalePanel::OnSetDefault(wxCommandEvent &event){
}
