#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <map>
#include "helper.hpp"
#include <wx/listctrl.h>
#include <wx/valtext.h>
#include <wx/valnum.h>

namespace ow{
    class ScalePanel : public wxPanel{
        public:
            ScalePanel(wxWindow* parent);
            short value = 0;
            wxListView* pScaleList;
            void Update(const std::map<int, wxString>& map);
            void Save(std::map<int, wxString>& map);
        protected:
        private:
        // handlers:
            void OnAdd(wxCommandEvent& event);
            void OnDelete(wxCommandEvent& event);
            void OnClear(wxCommandEvent& event);
    };
} // namespace ow