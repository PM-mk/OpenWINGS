#include "ControlPanel.hpp"
using namespace ow;

ControlPanel::ControlPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxSplitterWindow* pSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_THIN_SASH|wxSP_LIVE_UPDATE);
	pSplitter->SetMinimumPaneSize(200);

	pSidePanel = new ElementPanel(pSplitter);

	pIOPanel = new IOPanel(pSplitter);

	pSplitter->SplitVertically(pSidePanel, pIOPanel, 200);
	bSizer1->Add(pSplitter, 1, wxEXPAND, 5);

	// set up memory objects
	std::map<int, wxString> defaultScale = {
		{0, wxT("None")},
		{1, wxT("Low")},
		{2, wxT("Medium")},
		{3, wxT("High")},
		{4, wxT("Very high")},
	};
	weightsMap = defaultScale;
	influencesMap = defaultScale;
	elementMap = {};

	// send events
    Bind(wxEVT_IDLE, &ControlPanel::OnIdle, this, wxID_ANY);

	this->SetSizer(bSizer1);
	this->Layout();
}

int ControlPanel::scaleStrToInt(const wxString& label, bool mode){
	auto map = (mode == true) ? this->weightsMap : this->influencesMap;
	for(const auto& it : map){
		if(it.second == label){return it.first;}
	}
    return -1;
}

void ControlPanel::OnIdle(wxIdleEvent &event){
    return;
}
