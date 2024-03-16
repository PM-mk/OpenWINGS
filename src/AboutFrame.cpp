#include "AboutFrame.hpp"
#include <wx/hyperlink.h>
using namespace ow;

ow::AboutFrame::AboutFrame(wxWindow* parent) :
        wxDialog(parent, wxID_ABOUT, "About", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
    wxBoxSizer* pSizerMain = new wxBoxSizer(wxVERTICAL);

    wxString aboutOw = "";
    aboutOw += "OpenWINGS Version 0.0.1\n";
    aboutOw += "Open source GUI tool for WINGS and ALMODES system analysis and modelling.\n\n";
    aboutOw += "by Paweł Misiek\n";
    wxStaticText* pAboutText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8(aboutOw),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    pAboutText->Wrap(-1);

    wxHyperlinkCtrl* pLinkGithub = new wxHyperlinkCtrl(this, wxID_ANY, "github.com/PM-mk/OpenWINGS",
        wxT("https://github.com/PM-mk/OpenWINGS"), wxDefaultPosition, wxDefaultSize, wxVERTICAL);

    wxBoxSizer* pSizerSub = new wxBoxSizer(wxHORIZONTAL);
	pSizerMain->Add(pAboutText, 4, wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP|wxALL, 5);
	pSizerMain->Add(pLinkGithub, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    wxString aboutWx = wxString::Format(wxT("Made with %s"),wxVERSION_STRING);
    wxStaticText* pWxText = new wxStaticText( this, wxID_ANY, aboutWx, wxDefaultPosition, wxDefaultSize, 0 );
    pWxText->Wrap(-1);

    wxHyperlinkCtrl* pLinkWx = new wxHyperlinkCtrl(this, wxID_ANY, "wxwidgets.org",
        wxT("https://www.wxwidgets.org"), wxDefaultPosition, wxDefaultSize, wxVERTICAL);

    pSizerSub->Add(pWxText, 1, wxALL, 5);
	pSizerSub->Add(pLinkWx, 0, wxALL, 5 );
	pSizerMain->Add(pSizerSub, 1, wxEXPAND, 5);

	this->SetSizer(pSizerMain);
	this->Layout();
    this->Fit();
	this->Centre(wxBOTH);
}