#include "OpenWingsApp.hpp"
#include "MainFrame.hpp"

using namespace ow;
bool OWApp::OnInit(){
    // Main application window
    MainFrame *pFrame = new MainFrame();
    pFrame->Show(true);
    return true;
}

// void OWApp::ErrMsg(wxFrame* frame, const wxString& msg){
//     wxMessageDialog errDlg = wxMessageDialog(frame, msg, wxT("Error"), wxOK|wxICON_ERROR);
//     errDlg.ShowModal();
// }

// bool OWApp::Ask(wxFrame* frame, const wxString& msg){
//     wxMessageDialog askDlg = wxMessageDialog(frame, msg, wxT("Confirmation"), wxYES_NO);
//     return (askDlg.ShowModal() == wxID_YES) ? true : false;
// }
