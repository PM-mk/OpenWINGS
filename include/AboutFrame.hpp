#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/hyperlink.h>
#include <wx/statline.h>
#include "ow_logo.xpm"
#include "config.hpp"

namespace ow{
    class AboutFrame : public wxDialog{
        public:
            AboutFrame(wxWindow* parent);
        protected:
        private:
    };
} // namespace ow
