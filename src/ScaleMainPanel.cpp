#include "ScaleMainPanel.hpp"
using namespace ow;

ScaleMainPanel::ScaleMainPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL){
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxHORIZONTAL);
	ScalePanel* pWeightScalePanel = new ScalePanel(this);
	pMainSizer->Add(pWeightScalePanel, 1, wxEXPAND | wxALL, 5);

	wxStaticLine* m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	pMainSizer->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	ScalePanel* pInfluenceScalePanel = new ScalePanel(this);
	pMainSizer->Add(pInfluenceScalePanel, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(pMainSizer);
	this->Layout();
}
