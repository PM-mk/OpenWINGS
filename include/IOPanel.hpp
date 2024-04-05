#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/notebook.h>
#include <wx/statline.h>
#include <wx/listctrl.h>

namespace ow{
    class IOPanel : public wxPanel{
        public:
            IOPanel(wxWindow* parent);
        protected:
        private:
        // handlers:

    };
} // namespace ow