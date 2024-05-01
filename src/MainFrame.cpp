#include "MainFrame.hpp"
using namespace ow;

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("OpenWINGS"), wxDefaultPosition, wxSize(1366,768)){
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    // menus
    wxMenu* pFileMenu = new wxMenu;
    pFileMenu->Append(ID_NEW_PROJECT, wxT("&New project\tCtrl+N"), wxT("Create new WINGS/ALMODES project"));
    pFileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl+O"), wxT("Open project"));
    pFileMenu->Append(wxID_SEPARATOR);
    pFileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"), wxT("Save current project"));
    pFileMenu->Append(wxID_SAVEAS, wxT("Sa&ve as...\tCtrl+Shift+S"), wxT("Save current project as..."));
    pFileMenu->Append(wxID_SEPARATOR);
    pFileMenu->Append(wxID_EXIT, wxT("&Quit\tCtrl+Q"), wxT("Quit this program"));
    pFileMenu->Enable(wxID_SAVE,false);
    pFileMenu->Enable(wxID_SAVEAS,false);
    wxMenu* pHelpMenu = new wxMenu;
    pHelpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
    // menu bar
    wxMenuBar* pMenuBar = new wxMenuBar();
    pMenuBar->Append(pFileMenu, wxT("&File"));
    pMenuBar->Append(pHelpMenu, wxT("&Help"));
    SetMenuBar(pMenuBar);

    wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
    // panels - start
    pStartPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    // move this to base class
    wxBoxSizer* pStartSizer = new wxBoxSizer(wxVERTICAL);
    pStartPanel->SetSizer(pStartSizer);
    pStartPanel->Layout();
    pStartSizer->Fit(pStartPanel);
    wxStaticText* pStartTxt = new wxStaticText(pStartPanel, wxID_ANY, wxT("Start"),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    pStartSizer->Add(pStartTxt, 1, wxEXPAND, 0);
    pMainSizer->Add(pStartPanel, 1, wxEXPAND, 0);

    pControlPanel = new ControlPanel(this);
    pMainSizer->Add(pControlPanel, 1, wxEXPAND, 0);
    pControlPanel->Hide();
    pStartPanel->Show();
    // panels - end

    // xml document
    pProjectFile = new wxXmlDocument();

    SetSizer(pMainSizer);
    // status bar
    CreateStatusBar(2);
    SetStatusText(wxT("Ready"));
    // send events
    Bind(wxEVT_MENU, &MainFrame::OnNewFile, this, ID_NEW_PROJECT);
    Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnSaveAs, this, wxID_SAVEAS);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
    // finish frame
    CentreOnScreen(wxBOTH);
    Layout();
}

void MainFrame::SetPanel(wxPanel* pPanel){
    pPanel->GetContainingSizer()->ShowItems(false);
    pPanel->Show();
    pPanel->GetContainingSizer()->Layout();
}

void MainFrame::OnNewFile(wxCommandEvent &event){
    if(!this->IsFileLoaded() || Ask(this, "Any unsaved changes will be lost.\nProceed?")){
        this->SetStatusText(wxT("Unsaved project"));
        delete this->pProjectFile->DetachRoot();
        this->SetPanel(this->pControlPanel);
        this->EnableSaving(true);
    }
}

void MainFrame::OnOpen(wxCommandEvent &event){
    wxString fileName = wxLoadFileSelector(wxT("a project"), "XML", wxEmptyString, this);
    if(!fileName.empty()){
        bool loadResult = pProjectFile->Load(fileName);
        if(loadResult){
            wxString projectType = this->pProjectFile->GetRoot()->GetAttribute("type");
            if(projectType == "OpenWINGS"){
                SetStatusText(wxString::Format(wxT("%s - %s"), fileName, projectType));
                // TODO: load data into controls
                this->SetPanel(this->pControlPanel);
                this->EnableSaving(true);
            }
            else{
                ErrMsg(this, wxString::Format(wxT("Unrecognized project type: \"%s\""),
                    projectType));
            }
        }
        else{
            ErrMsg(this, wxT("Could not open file.\n\n%s"));
        }
    }
}

void MainFrame::EnableSaving(bool enable){
    if(this->IsFileLoaded()){
        this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVE, enable);
    }
    else{
        this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVE, false);
    }
    this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVEAS, enable);
}

bool MainFrame::IsFileLoaded(){
    return this->pProjectFile->GetRoot();
}

void MainFrame::OnSave(wxCommandEvent &event){
    ErrMsg(this, "Not yet implemented :(");
}

void MainFrame::OnSaveAs(wxCommandEvent &event){
    ErrMsg(this, "Not yet implemented :(");
}

void MainFrame::OnAbout(wxCommandEvent &event){
    AboutFrame* pAboutBox = new AboutFrame(this);
    pAboutBox->ShowModal();
}

void MainFrame::OnQuit(wxCommandEvent &event){
    if(!this->IsFileLoaded() || Ask(this, "Any unsaved changes will be lost.\nAre you sure you want to exit?")){
        Close(true);
    }
}