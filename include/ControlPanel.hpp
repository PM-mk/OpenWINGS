#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/splitter.h>
#include "ElementPanel.hpp"
#include "IOPanel.hpp"

namespace ow{
    class ControlPanel : public wxPanel{
        public:
            ControlPanel(wxWindow* parent);
            ElementPanel* pSidePanel;
            IOPanel* pIOPanel;
        protected:
        private:
        // handlers:
            void OnIdle(wxIdleEvent& event);

    };
} // namespace ow