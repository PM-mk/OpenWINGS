#include "helper.hpp"
using namespace ow;

void ow::ErrMsg(wxFrame* frame, const wxString& msg){
    wxMessageDialog errDlg = wxMessageDialog(frame, msg, wxT("Error"), wxOK|wxICON_ERROR);
    errDlg.ShowModal();
}

bool ow::Ask(wxFrame* frame, const wxString& msg){
    wxMessageDialog askDlg = wxMessageDialog(frame, msg, wxT("Confirmation"), wxYES_NO);
    return (askDlg.ShowModal() == wxID_YES) ? true : false;
}