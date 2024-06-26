#include "AboutFrame.hpp"
using namespace ow;

AboutFrame::AboutFrame(wxWindow* parent) :
    wxDialog(parent, wxID_ABOUT, "About", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE){
    // main credits
    wxBoxSizer* pSizerMain = new wxBoxSizer(wxVERTICAL);
    wxString aboutOw = "OpenWINGS ";
    aboutOw += PROJECT_VER;
    aboutOw += "\nOpen source GUI tool for WINGS and ALMODES system analysis and modelling.";
    wxStaticText* pAboutText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8(aboutOw),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    wxString signature = "by Paweł Misiek";
    wxStaticText* pSignatureText = new wxStaticText(this, wxID_ANY, wxString::FromUTF8(signature),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
    pAboutText->Wrap(-1);
    wxHyperlinkCtrl* pLinkGithub = new wxHyperlinkCtrl(this, wxID_ANY, "github.com/PM-mk/OpenWINGS",
        wxT("https://github.com/PM-mk/OpenWINGS"), wxDefaultPosition, wxDefaultSize);
    wxStaticLine* pStaticLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    pSizerMain->Add(pAboutText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP, 5);
    wxStaticBitmap* ow_logo = new wxStaticBitmap(this, wxID_ANY, wxBitmap(ow_logo_xpm), wxDefaultPosition, wxDefaultSize, 0);
    pSizerMain->Add(ow_logo, 0, wxALIGN_CENTER_HORIZONTAL, 5);
    pSizerMain->Add(pSignatureText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_TOP, 5);
    pSizerMain->Add(pLinkGithub, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    pSizerMain->Add(pStaticLine, 0, wxALL|wxEXPAND, 5);

    // wxWidgets credits
    wxBoxSizer* pSizerWxCredit = new wxBoxSizer(wxVERTICAL);
    wxString aboutWx = wxString::Format(wxT("GUI made with %s"),wxVERSION_STRING);
    wxStaticText* pWxText = new wxStaticText( this, wxID_ANY, aboutWx, wxDefaultPosition, wxDefaultSize);
    pWxText->Wrap(-1);
    wxHyperlinkCtrl* pLinkWx = new wxHyperlinkCtrl(this, wxID_ANY, wxT("wxwidgets.org"),
        wxT("https://www.wxwidgets.org"), wxDefaultPosition, wxDefaultSize);
    pSizerWxCredit->Add(pWxText, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    pSizerWxCredit->Add(pLinkWx, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    // wxMathPlot credits
    wxBoxSizer* pSizerPlotCredit = new wxBoxSizer(wxVERTICAL);
    wxString aboutMathPlot = wxT("Plotting handled with wxMathPlot 0.2.0");
    wxStaticText* pPlotTextCtrl = new wxStaticText( this, wxID_ANY, aboutMathPlot, wxDefaultPosition, wxDefaultSize);
    pPlotTextCtrl->Wrap(-1);
    wxHyperlinkCtrl* pLinkXml = new wxHyperlinkCtrl(this, wxID_ANY, wxT("wxmathplot.sourceforge.io"),
        wxT("https://wxmathplot.sourceforge.io"), wxDefaultPosition, wxDefaultSize);
    pSizerPlotCredit->Add(pPlotTextCtrl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    pSizerPlotCredit->Add(pLinkXml, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    // Eigen3 credits
    wxBoxSizer* pSizerEigenCredit = new wxBoxSizer(wxVERTICAL);
    wxString aboutEigen = wxString::Format(wxT("Linear algebra handled with Eigen %i.%i.%i"),
        EIGEN_WORLD_VERSION, EIGEN_MAJOR_VERSION, EIGEN_MINOR_VERSION);
    wxStaticText* pEigenTextCtrl = new wxStaticText( this, wxID_ANY, aboutEigen, wxDefaultPosition, wxDefaultSize);
    pEigenTextCtrl->Wrap(-1);
    wxHyperlinkCtrl* pLinkEigen = new wxHyperlinkCtrl(this, wxID_ANY, wxT("eigen.tuxfamily.org"),
        wxT("https://eigen.tuxfamily.org"), wxDefaultPosition, wxDefaultSize);
    pSizerEigenCredit->Add(pEigenTextCtrl, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    pSizerEigenCredit->Add(pLinkEigen, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);

    // finish frame
    pAboutText->SetFocus(); // set focus on wxStaticText control to prevent focus frame from showing
    pSizerMain->Add(pSizerWxCredit, 0, wxEXPAND, 5);
    pSizerMain->Add(pSizerPlotCredit, 0, wxEXPAND, 5);
    pSizerMain->Add(pSizerEigenCredit, 0, wxEXPAND, 5);
    this->SetSizer(pSizerMain);
    this->Layout();
    this->Fit();
    this->Centre(wxBOTH);
}