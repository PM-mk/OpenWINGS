#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/listctrl.h>

namespace ow{
    enum eventID{
        ID_NEW_PROJECT = wxID_HIGHEST+1,
        ID_SET_DEFAULT,
        ID_DEL_ITEM, // bitmaps don't work on buttons with stock ID's!
        ID_NEW_ELEMENT, // for IOPanel
        ID_NEW_RELATION, // for scale editor
        ID_UPDATE_ITEMS,
        ID_WEIGHT_COMBO,
        ID_INFLUENCE_COMBO,
        ID_RUN_WINGS
    };
    void ErrMsg(wxWindow* window, const wxString& msg);
    bool Ask(wxWindow* window, const wxString& msg);
    long findRecord(wxListView* pList, const int& col, wxString string);
} // namespace ow