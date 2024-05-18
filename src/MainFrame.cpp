#include "MainFrame.hpp"
using namespace ow;

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, wxT("OpenWINGS"), wxDefaultPosition, wxSize(800,600)){
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
    wxStaticText* pStartTxt = new wxStaticText(pStartPanel, wxID_ANY, wxT("Ctrl+N - New project\nCtrl+O - Open file\nCtrl+Q - Quit"),
        wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxStaticBitmap* pBackgroundBitmap = new wxStaticBitmap(pStartPanel, wxID_ANY, wxBitmap(ow_background_gray_xpm), wxDefaultPosition, wxDefaultSize, 0);
    pBackgroundBitmap->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    pStartSizer->Add(pBackgroundBitmap, 0, wxALIGN_CENTER_HORIZONTAL, 5);

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
    wxXmlNode* pRoot = this->pProjectFile->GetRoot();
    if(pRoot){
        // get major nodes
        wxXmlNode* pScales = pRoot->GetChildren();
        wxXmlNode* pWeights = pScales->GetChildren();
        wxXmlNode* pInfluences = pWeights->GetNext();
        wxXmlNode* pElements = pScales->GetNext();
        wxXmlNode* pRelations = pElements->GetNext();
        if(pWeights && pInfluences && pElements && pRelations){
            wxXmlNode* pNode = pWeights->GetChildren(); /* get weights */
            if(pNode){
                this->pControlPanel->weightsMap.clear();
                while(pNode){
                    this->pControlPanel->weightsMap.insert({wxAtoi(pNode->GetAttribute("val")), pNode->GetAttribute("name")});
                    pNode = pNode->GetNext();
                }
            }
            pNode = pInfluences->GetChildren(); /* get strengths */
            if(pNode){
                this->pControlPanel->influencesMap.clear();
                while(pNode){
                    this->pControlPanel->influencesMap.insert({wxAtoi(pNode->GetAttribute("val")), pNode->GetAttribute("name")});
                    pNode = pNode->GetNext();
                }
            }
            this->pControlPanel->pIOPanel->pSourceElementsList->Clear();
            this->pControlPanel->pIOPanel->pTargetElementsList->Clear();
            wxCommandEvent event = wxCommandEvent(wxEVT_BUTTON, ID_UPDATE_ITEMS);
            wxPostEvent(this->pControlPanel->pIOPanel, event); /* update combo boxes */
            pNode = pElements->GetChildren(); /* get elements */
            if(pNode){
                this->pControlPanel->pSidePanel->pElementList->DeleteAllItems();
                wxString weightLabel = wxEmptyString;
                wxString elementLabel = wxEmptyString;
                long ndx = 0;
                this->pControlPanel->pSidePanel->pElementList->Freeze();
                while(pNode){
                    weightLabel = (*this->pControlPanel->weightsMap.find(wxAtoi(pNode->GetAttribute("weight")))).second;
                    elementLabel = pNode->GetAttribute("name");
                    ndx = this->pControlPanel->pSidePanel->pElementList->InsertItem(0, weightLabel);
                    this->pControlPanel->pSidePanel->pElementList->SetItem(ndx, 1, elementLabel);
                    this->pControlPanel->pIOPanel->AddElement(elementLabel);
                    pNode = pNode->GetNext();
                }
                this->pControlPanel->pSidePanel->pElementList->Thaw();
            }
            pNode = pRelations->GetChildren(); /* get relations */
            if(pNode){
                wxString sourceLabel = wxEmptyString;
                wxString targetLabel = wxEmptyString;
                RelationshipData* pData = nullptr;
                int strength = 0;
                this->pControlPanel->pIOPanel->pRelationList->Freeze();
                while(pNode){
                    sourceLabel = pNode->GetAttribute("source");
                    targetLabel = pNode->GetAttribute("target");
                    strength = wxAtoi(pNode->GetAttribute("strength"));
					pData = new RelationshipData(
						RelationshipData::CreateItem(this->pControlPanel->pIOPanel->getWeight(sourceLabel), sourceLabel),
						strength,
						RelationshipData::CreateItem(this->pControlPanel->pIOPanel->getWeight(targetLabel), targetLabel)
					);
					this->pControlPanel->pIOPanel->AddRelation(pData);
                    pNode = pNode->GetNext();
                }
                this->pControlPanel->pIOPanel->pRelationList->Thaw();
            }
        }
        else{
            ErrMsg(this, wxT("Major XML nodes are missing from the file, data could not be loaded."));
        }
    }
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
    wxPostEvent(this->pControlPanel->pSidePanel, event); /* send event to display scale editor */
}

void MainFrame::OnQuit(wxCommandEvent &event){
    if(!this->isFileLoaded() || Ask(this, "Any unsaved changes will be lost.\nAre you sure you want to exit?")){
        Close(true);
    }
}