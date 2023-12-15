#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/listctrl.h>
#include <wx/spinctrl.h>

#include <cstdio>

#include "dialog.hpp"
#include "escola/aluno.hpp"
#include "escola/disciplina.hpp"
#include "escola/matricula.hpp"

class App : public wxApp {
   public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame {
   public:
    MainFrame();

   private:
    wxTextCtrl* name_input_al;
    wxButton* btn_add_al;
    wxTextCtrl* name_input_dis;
    wxSpinCtrl* ch_spin;
    wxCheckBox* check_box_dis;
    wxSpinCtrl* chp_spin;
    wxButton* btn_add_dis;
    wxButton* btn_vis_al;
    wxButton* btn_vis_dis;
    wxButton* btn_vis_clear;
    wxListCtrl* list_ctrl;

    bool fileExists(const std::string& filename);

    void OnLoadAl();
    void OnAddAl(wxCommandEvent& evt);

    void OnSeeAl(wxCommandEvent& evt);

    void OnLoadDis();
    void OnAddDis(wxCommandEvent& evt);

    void OnSeeDis(wxCommandEvent& evt);

    void OnClearAll(wxCommandEvent& evt);
    void OnOpenDialog(wxListEvent& event);
};
