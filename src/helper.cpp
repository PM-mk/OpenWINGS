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

wxString ow::GetCellContentsString(wxListView* list, long row_number, int column)
{
   wxListItem     row_info;
   wxString       cell_contents_string;

   // Set what row it is (m_itemId is a member of the regular wxListCtrl class)
   row_info.m_itemId = row_number;
   // Set what column of that row we want to query for information.
   row_info.m_col = column;
   // Set text mask
   row_info.m_mask = wxLIST_MASK_TEXT;

   // Get the info and store it in row_info variable.
   list->GetItem( row_info );

   // Extract the text out that cell
   cell_contents_string = row_info.m_text;

   return cell_contents_string;
}