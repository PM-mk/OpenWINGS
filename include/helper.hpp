#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/listctrl.h>

namespace ow{
    enum eventID{
        ID_NEW_WINGS = wxID_HIGHEST+1,
        ID_NEW_ALMODES,
        ID_SET_DEFAULT,
        ID_NEW_ELEMENT, // for IOPanel
        ID_NEW_RELATION, // for scale editor
        ID_UPDATE_ITEMS
    };
    void ErrMsg(wxFrame* frame, const wxString& msg);
    bool Ask(wxFrame* frame, const wxString& msg);
    void UpdateList(wxListCtrl* list);
    void UpdateCombo(wxComboBox* combo);
} // namespace ow