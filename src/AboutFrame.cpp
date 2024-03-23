#include "AboutFrame.hpp"
using namespace ow;

AboutFrame::AboutFrame(wxWindow* parent) :
    wxDialog(parent, wxID_ABOUT, "About", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE){
    // main credits
    wxBoxSizer* pSizerMain = new wxBoxSizer(wxVERTICAL);
    wxString aboutOw = "";
    aboutOw += "OpenWINGS Version 0.0.1\n";
    aboutOw += "Open source GUI tool for WINGS and ALMODES system analysis and modelling.\n\n";
    aboutOw += "by Paweł Misiek\n";
    wxStaticText* pAboutText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8(aboutOw),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    pAboutText->Wrap(-1);
    wxHyperlinkCtrl* pLinkGithub = new wxHyperlinkCtrl(this, wxID_ANY, "github.com/PM-mk/OpenWINGS",
        wxT("https://github.com/PM-mk/OpenWINGS"), wxDefaultPosition, wxDefaultSize);
	wxStaticLine* pStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    pSizerMain->Add(pAboutText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP, 5);
    wxStaticBitmap* ow_logo = new wxStaticBitmap(this, wxID_ANY, wxBitmap(ow_logo_xpm), wxDefaultPosition, wxDefaultSize, 0);
    pSizerMain->Add(ow_logo, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    pSizerMain->Add(pLinkGithub, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
	pSizerMain->Add(pStaticLine, 0, wxALL|wxEXPAND, 5);

    // wxWidgets credits
    wxBoxSizer* pSizerWxCredit = new wxBoxSizer(wxVERTICAL);
    wxString aboutWx = wxString::Format(wxT("GUI made with %s"),wxVERSION_STRING);
    wxStaticText* pWxText = new wxStaticText( this, wxID_ANY, aboutWx, wxDefaultPosition, wxDefaultSize);
    pWxText->Wrap(-1);
    wxHyperlinkCtrl* pLinkWx = new wxHyperlinkCtrl(this, wxID_ANY, "wxwidgets.org",
        wxT("https://www.wxwidgets.org"), wxDefaultPosition, wxDefaultSize);
    pSizerWxCredit->Add(pWxText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
	pSizerWxCredit->Add(pLinkWx, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    // TinyXML-2 credits
    wxBoxSizer* pSizerXmlCredit = new wxBoxSizer(wxVERTICAL);
    wxString aboutXml = wxString::Format(wxT("XML files handled with TinyXML-2 v.%i.%i.%i"),
        TINYXML2_MAJOR_VERSION, TINYXML2_MINOR_VERSION, TINYXML2_PATCH_VERSION);
    wxStaticText* pXmlText = new wxStaticText( this, wxID_ANY, aboutXml, wxDefaultPosition, wxDefaultSize);
    pXmlText->Wrap(-1);
    wxHyperlinkCtrl* pLinkXml = new wxHyperlinkCtrl(this, wxID_ANY, "github.com/leethomason/tinyxml2",
        wxT("https://github.com/leethomason/tinyxml2"), wxDefaultPosition, wxDefaultSize);
    pSizerXmlCredit->Add(pXmlText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
	pSizerXmlCredit->Add(pLinkXml, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    // finish frame
    pAboutText->SetFocus(); // set focus on wxStaticText control to prevent focus frame from showing
	pSizerMain->Add(pSizerWxCredit, 0, wxEXPAND, 5);
	pSizerMain->Add(pSizerXmlCredit, 0, wxEXPAND, 5);
	this->SetSizer(pSizerMain);
	this->Layout();
    this->Fit();
	this->Centre(wxBOTH);
}