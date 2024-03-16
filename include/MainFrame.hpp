#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

namespace ow{
    class MainFrame : public wxFrame{
        public:
            MainFrame();
        // handlers:
        protected:
        private:
            void OnQuit(wxCommandEvent& event);
            void OnAbout(wxCommandEvent& event);
    };
}
