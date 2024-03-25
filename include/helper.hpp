#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP

namespace ow{
    enum eventID{
        ID_NEW_WINGS = wxID_HIGHEST+1,
        ID_NEW_ALMODES,
        ID_SET_SCALE
    };

    void ErrMsg(wxFrame* frame, const wxString& msg);
    bool Ask(wxFrame* frame, const wxString& msg);
} // namespace ow