#include "MainFrame.hpp"
#include "AboutFrame.hpp"
using namespace ow;

ow::MainFrame::MainFrame() :
        wxFrame(nullptr, wxID_ANY, "OpenWINGS", wxPoint(0,0)){
    // menus
    wxMenu* pFileMenu = new wxMenu;
    wxMenu* pHelpMenu = new wxMenu;
    pHelpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
    pFileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

    wxMenuBar* pMenuBar = new wxMenuBar();
    pMenuBar->Append(pFileMenu, wxT("&File"));
    pMenuBar->Append(pHelpMenu, wxT("&Help"));

    SetMenuBar(pMenuBar);

    // Status bar
    CreateStatusBar(2);
    SetStatusText(wxT("Ready"));

    CentreOnScreen(wxBOTH);

    // Send events
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
}

void ow::MainFrame::OnQuit(wxCommandEvent &event){
    Close(true);
}

void ow::MainFrame::OnAbout(wxCommandEvent &event){
    AboutFrame* pAboutBox = new AboutFrame(this);
    pAboutBox->ShowModal();
}
