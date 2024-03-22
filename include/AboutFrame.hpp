#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/hyperlink.h>
#include <wx/statline.h>
#include <tinyxml2.h>

namespace ow{
    class AboutFrame : public wxDialog{
        public:
            AboutFrame(wxWindow* parent);
        protected:
        private:
    };
} // namespace ow
