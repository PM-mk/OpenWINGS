#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif // WX_PRECOMP
#include <wx/dynarray.h>
#include <wx/textfile.h>

namespace ow{
    class MainFrame : public wxFrame{
        public:
            MainFrame();
        protected:
        private:
            wxTextFile* pFile = nullptr;
            wxPanel* pWingsEditPanel = nullptr;
            wxPanel* pAlmodesEditPanel = nullptr;
            wxBoxSizer* pMainSizer = nullptr;
            std::vector<wxPanel*> mainPanelsArray = {};
            void SetPanel(wxPanel* panel);
            void EnableSaving(bool enable);
        // handlers:
            void OnNewFile(wxCommandEvent& event);
            void OnOpen(wxCommandEvent& event);
            void OnSave(wxCommandEvent& event);
            void OnSaveAs(wxCommandEvent& event);
            void OnQuit(wxCommandEvent& event);
            void OnAbout(wxCommandEvent& event);
    };
} // namespace ow