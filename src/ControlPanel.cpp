#include "ControlPanel.hpp"
using namespace ow;

ControlPanel::ControlPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxSplitterWindow* pSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_BORDER|wxSP_LIVE_UPDATE);
	pSplitter->SetMinimumPaneSize(200);

	pSidePanel = new ElementPanel(pSplitter);
	pSidePanel->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	pIOPanel = new IOPanel(pSplitter);
	pIOPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	pSplitter->SplitVertically(pSidePanel, pIOPanel, 200);
	bSizer1->Add(pSplitter, 1, wxEXPAND, 5);

	// send events
    Bind(wxEVT_IDLE, &ControlPanel::OnIdle, this, wxID_ANY);

	this->SetSizer(bSizer1);
	this->Layout();
}

void ow::ControlPanel::OnIdle(wxIdleEvent &event){
	return;
}
