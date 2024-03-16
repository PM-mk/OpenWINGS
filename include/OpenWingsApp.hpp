#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

namespace ow{
    class OWApp : public wxApp{
        public:
            bool OnInit() override;
        protected:
        private:
    };
}