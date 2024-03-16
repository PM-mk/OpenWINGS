#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/dynarray.h>

namespace ow{
    class MainFrame : public wxFrame{
        public:
            MainFrame();
            bool fileLoaded = false;
        protected:
        private:
            wxPanel* pWingsEditPanel = nullptr;
            wxPanel* pAlmodesEditPanel = nullptr;
            wxBoxSizer* pMainSizer = nullptr;
            std::vector<wxPanel*> mainPanelsArray = {};
            void SetPanel(MainFrame* parent, wxPanel* panel);
        // handlers:
            void OnNewFile(wxCommandEvent& event);
            void OnOpen(wxCommandEvent& event);
            void OnSave(wxCommandEvent& event);
            void OnSaveAs(wxCommandEvent& event);
            void OnQuit(wxCommandEvent& event);
            void OnAbout(wxCommandEvent& event);
    };
}