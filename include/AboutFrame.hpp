#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP

namespace ow{
    class AboutFrame : public wxDialog{
        public:
            AboutFrame(wxWindow* parent);
        protected:
        private:
    };
} // namespace ow
