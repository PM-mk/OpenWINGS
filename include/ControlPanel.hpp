#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <map>
#include <wx/splitter.h>
#include "ElementPanel.hpp"
#include "IOPanel.hpp"

namespace ow{
    class ElementPanel;
    class IOPanel;
    // REMOVE CIRCURAL DEPENDANCY
    class ControlPanel : public wxPanel{
        public:
            ControlPanel(wxWindow* parent);
            std::map<int, wxString> weightsMap;
            std::map<int, wxString> influencesMap;
            std::multimap<wxString, wxString> elementMap;
            ElementPanel* pSidePanel;
            IOPanel* pIOPanel;
        protected:
        private:
        // handlers:
            void OnIdle(wxIdleEvent& event);

    };
} // namespace ow