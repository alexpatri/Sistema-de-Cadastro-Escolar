#include <wx/grid.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/wxprec.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "escola/aluno.hpp"
#include "escola/disciplina.hpp"
#include "escola/matricula.hpp"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class DialogAl : public wxDialog {
   public:
    DialogAl(wxWindow* parent, const wxString& title, Aluno* name);

   private:
    Aluno* aluno;
    wxTextCtrl* year_input;
    wxChoice* select_gra;
    wxChoice* select_dis;
    wxTextCtrl* n1_input;
    wxTextCtrl* n2_input;
    wxTextCtrl* n3_input;
    wxTextCtrl* n4_input;
    wxButton* btn_add_mat;
    wxGrid* grid;
    wxListCtrl* list_mat;

    std::vector<Disciplina*> disciplinas;
    std::vector<Matricula*> matriculas;

    std::vector<Disciplina*> loadDis(const std::string& filename);

    std::vector<Matricula*> loadAllMat(const std::string& filename);

    void OnChar(wxKeyEvent& event);
    void OnChar2(wxKeyEvent& event);

    void OnLoadMat();

    void OnAddMat(wxCommandEvent& evt);
};
