#include "MainFrame.hpp"
#include "AboutFrame.hpp"
#include "OpenWingsApp.hpp"

using namespace ow;

enum eventID{
    ID_NEW_WINGS = wxID_HIGHEST+1,
    ID_NEW_ALMODES
};

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("OpenWINGS"), wxDefaultPosition, wxSize(1366,768)){
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    // menus
    wxMenu* pFileMenu = new wxMenu;
    pFileMenu->Append(ID_NEW_WINGS, wxT("New &WINGS\tW"), wxT("Create new WINGS project"));
    pFileMenu->Append(ID_NEW_ALMODES, wxT("New &ALMODES\tA"), wxT("Create new ALMODES project"));
    pFileMenu->Append(wxID_OPEN, wxT("&Open\tO"), wxT("Open project"));
    pFileMenu->Append(wxID_SEPARATOR);
    pFileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"), wxT("Save current project"));
    pFileMenu->Append(wxID_SAVEAS, wxT("Sa&ve as...\tCtrl+Shift+S"), wxT("Save current project as..."));
    pFileMenu->Append(wxID_SEPARATOR);
    pFileMenu->Append(wxID_EXIT, wxT("&Quit\tQ"), wxT("Quit this program"));
    pFileMenu->Enable(wxID_SAVE,false);
    pFileMenu->Enable(wxID_SAVEAS,false);
    wxMenu* pHelpMenu = new wxMenu;
    pHelpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
    // menu bar
    wxMenuBar* pMenuBar = new wxMenuBar();
    pMenuBar->Append(pFileMenu, wxT("&File"));
    pMenuBar->Append(pHelpMenu, wxT("&Help"));
    SetMenuBar(pMenuBar);
    // panels
	pMainSizer = new wxBoxSizer(wxVERTICAL);
	pWingsEditPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    pWingsEditPanel->SetBackgroundColour(wxColour(128, 255, 0));
	pAlmodesEditPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    pAlmodesEditPanel->SetBackgroundColour(wxColour(207, 21, 234));
    mainPanelsArray.push_back(pWingsEditPanel);
    mainPanelsArray.push_back(pAlmodesEditPanel);
    for(auto it = mainPanelsArray.begin(); it != mainPanelsArray.end(); ++it){
        pMainSizer->Add(*it, 1, wxEXPAND, 5);
        (*it)->Hide();
    };
    SetSizer(pMainSizer);
    // status bar
    CreateStatusBar(2);
    SetStatusText(wxT("Ready"));
    // send events
    Bind(wxEVT_MENU, &MainFrame::OnNewFile, this, ID_NEW_WINGS);
    Bind(wxEVT_MENU, &MainFrame::OnNewFile, this, ID_NEW_ALMODES);
    Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnSaveAs, this, wxID_SAVEAS);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
    // finish frame
    CentreOnScreen(wxBOTH);
	Layout();
}

void MainFrame::SetPanel(wxPanel* panel){
    for(auto it = this->mainPanelsArray.begin(); it != this->mainPanelsArray.end(); ++it){
        (*it)->Hide();
    };
    panel->Show();
    this->pMainSizer->Layout();
}

void MainFrame::OnNewFile(wxCommandEvent &event){
    switch(event.GetId()){
        case ID_NEW_WINGS:
            this->SetPanel(this->pWingsEditPanel);
            break;
        case ID_NEW_ALMODES:
            this->SetPanel(this->pAlmodesEditPanel);
            break;
        default:
            return;
    }
    this->EnableSaving(true);
}

void MainFrame::OnOpen(wxCommandEvent &event){
    wxString fileName = wxLoadFileSelector(wxT("a project"), "XML", wxEmptyString, this);
	if(!fileName.empty()){
            tinyxml2::XMLError loadResult = this->projectFile.LoadFile(fileName);
        if(loadResult == tinyxml2::XML_SUCCESS){
            tinyxml2::XMLElement* root = this->projectFile.RootElement();
            SetStatusText(wxString::Format(wxT("%s - %s"), fileName, root->Attribute("type")));
            // TODO: further work mode handling here
            this->EnableSaving(true);
        }else{
            OWApp::ErrMsg(this, wxString::Format(wxT("Could not open file.\n\n%s"),
                this->projectFile.ErrorIDToName(loadResult)));
        }
    }
}

void MainFrame::EnableSaving(bool enable){
    if(this->projectFile.ChildElementCount()){
        this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVE, enable);
    }
    this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVEAS, enable);
}

void MainFrame::OnSave(wxCommandEvent &event){
    OWApp::ErrMsg(this, "Not yet implemented :(");
}

void MainFrame::OnSaveAs(wxCommandEvent &event){
    OWApp::ErrMsg(this, "Not yet implemented :(");
}

void MainFrame::OnAbout(wxCommandEvent &event){
    AboutFrame* pAboutBox = new AboutFrame(this);
    pAboutBox->ShowModal();
}

void MainFrame::OnQuit(wxCommandEvent &event){
    Close(true);
}