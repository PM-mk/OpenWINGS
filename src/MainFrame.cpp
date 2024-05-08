#include "MainFrame.hpp"
using namespace ow;

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("OpenWINGS"), wxDefaultPosition, wxSize(1366,768)){
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    // menus
    wxMenu* pFileMenu = new wxMenu();
    pFileMenu->Append(ID_NEW_PROJECT, wxT("&New project\tCtrl+N"), wxT("Create new WINGS/ALMODES project"));
    pFileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl+O"), wxT("Open project"));
    pFileMenu->Append(wxID_SEPARATOR);
    pFileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"), wxT("Save current project"));
    pFileMenu->Append(wxID_SAVEAS, wxT("Sa&ve as...\tCtrl+Shift+S"), wxT("Save current project as..."));
    pFileMenu->Append(wxID_SEPARATOR);
    pFileMenu->Append(wxID_EXIT, wxT("&Quit\tCtrl+Q"), wxT("Quit this program"));
    pFileMenu->Enable(wxID_SAVE,false);
    pFileMenu->Enable(wxID_SAVEAS,false);
    wxMenu* pEditMenu = new wxMenu();
    pEditMenu->Append(wxID_EDIT, wxT("&Edit scales\tCtrl+E"), wxT("Show scale editor"));
    pEditMenu->Enable(wxID_EDIT,false);
    wxMenu* pHelpMenu = new wxMenu();
    pHelpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"), wxT("Show about dialog"));
    // menu bar
    wxMenuBar* pMenuBar = new wxMenuBar();
    pMenuBar->Append(pFileMenu, wxT("&File"));
    pMenuBar->Append(pEditMenu, wxT("&Edit"));
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
    Bind(wxEVT_MENU, &MainFrame::OnEditScales, this, wxID_EDIT);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
    // finish frame
    CentreOnScreen(wxBOTH);
    Layout();
}

void MainFrame::setPanel(wxPanel* pPanel){
    pPanel->GetContainingSizer()->ShowItems(false);
    pPanel->Show();
    pPanel->GetContainingSizer()->Layout();
}

void MainFrame::OnNewFile(wxCommandEvent &event){
    if(!this->isFileLoaded() || Ask(this, "Any unsaved changes will be lost.\nProceed?")){
        this->SetStatusText(wxT("Unsaved project"));
        delete this->pProjectFile->DetachRoot();
        this->fileName.clear();
        this->GetMenuBar()->GetMenu(1)->Enable(wxID_EDIT, true);
        this->setPanel(this->pControlPanel);
        this->enableSaving(true);
        wxPostEvent(this, wxCommandEvent(wxEVT_MENU, wxID_EDIT));
    }
}

void MainFrame::OnOpen(wxCommandEvent &event){
    this->fileName = wxLoadFileSelector(wxT("a project"), "XML", wxEmptyString, this);
    if(!!fileName){
        bool loadResult = pProjectFile->Load(fileName);
        if(loadResult){
            wxString projectType = this->pProjectFile->GetRoot()->GetAttribute("type");
            if(projectType == "OpenWINGS"){
                this->SetStatusText(wxString::Format(wxT("Loaded: %s"), this->fileName));
                this->loadData();
                this->GetMenuBar()->GetMenu(1)->Enable(wxID_EDIT, true);
                this->setPanel(this->pControlPanel);
                this->enableSaving(true);
            }
            else{
                ErrMsg(this, wxT("Unrecognized project type"));
                this->fileName.clear();
            }
        }
        else{
            this->fileName.clear();
        }
    }
}

void MainFrame::enableSaving(bool enable){
    if(this->isFileLoaded()){
        this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVE, enable);
    }
    else{
        this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVE, false);
    }
    this->GetMenuBar()->GetMenu(0)->Enable(wxID_SAVEAS, enable);
}

void MainFrame::loadData(){
    //implement this
}

void MainFrame::dumpData(){
    // set up file contents
    wxXmlNode* pRoot = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("project"));
    this->pProjectFile->SetRoot(pRoot);
    pRoot->AddAttribute(wxT("type"), wxT("OpenWINGS"));
    wxXmlNode* pScales = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("scales"));
    pRoot->AddChild(pScales);
    wxXmlNode* pWeights = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("weights"));
    pScales->AddChild(pWeights);
    wxXmlNode* pInfluences = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("influences"));
    pScales->AddChild(pInfluences);
    wxXmlNode* pElements = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("elements"));
    pRoot->AddChild(pElements);
    wxXmlNode* pRelations = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("relations"));
    pRoot->AddChild(pRelations);
    // dump scales
    wxXmlNode* pNewNode = nullptr;
    for (const auto& pair : this->pControlPanel->weightsMap){
        pNewNode = new wxXmlNode(pWeights, wxXML_ELEMENT_NODE, wxT("weight"), wxEmptyString, new wxXmlAttribute(wxT("name"), pair.second));
        pNewNode->AddAttribute(wxT("val"), wxString::Format(wxT("%i"), pair.first));
    }
    for (const auto& pair : this->pControlPanel->influencesMap){
        pNewNode = new wxXmlNode(pInfluences, wxXML_ELEMENT_NODE, wxT("strength"), wxEmptyString, new wxXmlAttribute(wxT("name"), pair.second));
        pNewNode->AddAttribute(wxT("val"), wxString::Format(wxT("%i"), pair.first));
    }
    // dump elements
	int elementCount = this->pControlPanel->pSidePanel->pElementList->GetItemCount();
    wxString value = wxEmptyString;
    wxString name = wxEmptyString;
	for(auto i = 0; i<elementCount; i++){
        name = this->pControlPanel->pSidePanel->pElementList->GetItemText(i, 1);
		value = wxString::Format(wxT("%i"),  this->pControlPanel->scaleStrToInt(this->pControlPanel->pSidePanel->pElementList->GetItemText(i, 0), true));
        pNewNode = new wxXmlNode(pElements, wxXML_ELEMENT_NODE, wxT("element"), wxEmptyString, new wxXmlAttribute(wxT("name"), name));
        pNewNode->AddAttribute(wxT("weight"), value);
	}
    // dump relations
	int relationCount = this->pControlPanel->pIOPanel->pRelationList->GetCount();
	RelationshipData* pData = nullptr;
	for(int i = 0; i<relationCount; i++){
		pData = dynamic_cast<RelationshipData*>(this->pControlPanel->pIOPanel->pRelationList->GetClientObject(i));
        pNewNode = new wxXmlNode(pRelations, wxXML_ELEMENT_NODE, wxT("relation"), wxEmptyString, new wxXmlAttribute(wxT("source"), pData->source.label));
        pNewNode->AddAttribute(wxT("strength"), wxString::Format(wxT("%i"), pData->influenceValue));
        pNewNode->AddAttribute(wxT("target"), pData->target.label);
	}
}

bool MainFrame::isFileLoaded(){
    return !!this->fileName;
}

void MainFrame::OnSave(wxCommandEvent &event){
    this->dumpData();
    if (this->pProjectFile->Save(this->fileName)){
        this->SetStatusText(wxString::Format(wxT("Saved: %s"), this->fileName));
    }
    else{
        ErrMsg(this, wxT("Couldn't save file."));
    }
}

void MainFrame::OnSaveAs(wxCommandEvent &event){
    wxString saveFileName = wxSaveFileSelector(wxT("a project"), "XML", wxEmptyString, this);
    if(!!saveFileName){
        this->dumpData();
        if (this->pProjectFile->Save(saveFileName)){
            this->fileName = saveFileName;
            this->SetStatusText(wxString::Format(wxT("Saved: %s"), this->fileName));
        }
        else{
            ErrMsg(this, wxT("Couldn't save file."));
        }
    }
}

void MainFrame::OnAbout(wxCommandEvent &event){
    AboutFrame* pAboutBox = new AboutFrame(this);
    pAboutBox->ShowModal();
}

void MainFrame::OnEditScales(wxCommandEvent &event){
    wxPostEvent(this->pControlPanel->pSidePanel, event);
}

void MainFrame::OnQuit(wxCommandEvent &event){
    if(!this->isFileLoaded() || Ask(this, "Any unsaved changes will be lost.\nAre you sure you want to exit?")){
        Close(true);
    }
}