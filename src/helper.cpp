#include "helper.hpp"
using namespace ow;

void ow::ErrMsg(wxFrame* frame, const wxString& msg){
    wxMessageDialog errDlg = wxMessageDialog(frame, msg, wxT("Error"), wxOK|wxICON_ERROR);
    errDlg.ShowModal();
}

bool ow::Ask(wxFrame* frame, const wxString& msg){
    wxMessageDialog askDlg = wxMessageDialog(frame, msg, wxT("Confirmation"), wxYES_NO);
    return askDlg.ShowModal() == wxID_YES;
}

long ow::findRecord(wxListView* pList, const int& col, wxString string){
    long index = -1;
    if (col == 0){
        return pList->FindItem(index, string);
    }
    else{
        while ((index = pList->GetNextItem(index)) != wxNOT_FOUND){
            if (string.MakeLower() == pList->GetItemText(index, col).MakeLower()){
                return index;
            }
        }
    }
    return -1;
}