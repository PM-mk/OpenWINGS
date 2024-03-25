#include "scalePanel.hpp"
using namespace ow;


ScalePanel::ScalePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pScaleEditSizer;
	pScaleEditSizer = new wxBoxSizer(wxHORIZONTAL);

	wxTextCtrl* pTextValue = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), wxTE_RIGHT);
	pTextValue->SetMaxSize(wxSize(50,-1 ));

	pScaleEditSizer->Add(pTextValue, 1, wxALL, 5);

	wxTextCtrl* pTextName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	pScaleEditSizer->Add(pTextName, 1, wxALL, 5);

	wxButton* pBtnScaleAdd = new wxButton(this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
	pScaleEditSizer->Add(pBtnScaleAdd, 0, wxALL, 5);


	pMainSizer->Add(pScaleEditSizer, 0, wxEXPAND, 5);

	wxBoxSizer* scaleGridSizer;
	scaleGridSizer = new wxBoxSizer(wxHORIZONTAL);

	wxDataViewListCtrl* pScaleData = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES);
	wxDataViewColumn* pColValue = pScaleData->AppendTextColumn(wxT("Value"), wxDATAVIEW_CELL_INERT, 50, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_SORTABLE);
	wxDataViewColumn* pColName = pScaleData->AppendTextColumn(wxT("Name"), wxDATAVIEW_CELL_EDITABLE, 170, static_cast<wxAlignment>(wxALIGN_LEFT), 0);
	scaleGridSizer->Add(pScaleData, 1, wxALL|wxEXPAND, 5);

	wxButton* pBtnScaleDelete = new wxButton(this, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0);
	scaleGridSizer->Add(pBtnScaleDelete, 0, wxALL, 5);


	pMainSizer->Add(scaleGridSizer, 1, wxEXPAND, 5);

	wxBoxSizer* pBottomBtnSizer = new wxBoxSizer(wxHORIZONTAL);

	wxButton* pBtnScaleDefault = new wxButton(this, wxID_ANY, wxT("Reset to default"), wxDefaultPosition, wxDefaultSize, 0);
	pBottomBtnSizer->Add(pBtnScaleDefault, 0, wxALL, 5);

	wxButton* pBtnScaleClear = new wxButton(this, wxID_ANY, wxT("Clear"), wxDefaultPosition, wxDefaultSize, 0);
	pBottomBtnSizer->Add(pBtnScaleClear, 0, wxALL, 5);


	pMainSizer->Add(pBottomBtnSizer, 0, wxEXPAND, 5);


	this->SetSizer(pMainSizer);
	this->Layout();


    Bind(wxEVT_BUTTON, &ScalePanel::OnSetScale,this, ID_SET_SCALE);
}

void ScalePanel::OnSetScale(wxCommandEvent& event){
    return;
}
