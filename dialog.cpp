#include "dialog.hpp"

#include <wx/grid.h>
#include <wx/listctrl.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "escola/aluno.hpp"
#include "escola/disciplina.hpp"
#include "escola/matricula.hpp"

DialogAl::DialogAl(wxWindow* parent, const wxString& title, Aluno* aluno)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE) {
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 750));

    SetSize(wxSize(500, 750));

    this->aluno = aluno;

    wxFont font_title;
    font_title.SetPointSize(18);

    wxFont font_subtitle;
    font_subtitle.SetPointSize(12);

    wxStaticText* title_label = new wxStaticText(panel, wxID_ANY, aluno->getNome());
    title_label->SetFont(font_title);

    wxStaticText* desc = new wxStaticText(panel, wxID_ANY, "Cadastro de nova matricula");
    desc->SetFont(font_subtitle);

    wxStaticText* year_label = new wxStaticText(panel, wxID_ANY, "Ano:");
    year_input = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));

    year_input->Bind(wxEVT_CHAR, &DialogAl::OnChar, this);

    wxArrayString series({"6 ano", "7 ano", "8 ano", "9 ano", "1 ano", "2 ano", "3 ano"});

    wxStaticText* ser_label = new wxStaticText(panel, wxID_ANY, "Serie:");
    select_gra = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(150, -1), series);

    wxArrayString choices;
    disciplinas = loadDis("disciplina.csv");
    for (Disciplina* dis : disciplinas) {
        wxString name(dis->getNome());

        choices.Add(name);
    }

    wxStaticText* select_label = new wxStaticText(panel, wxID_ANY, "Disciplina:");
    select_dis = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(150, -1), choices);

    wxStaticText* n1_label = new wxStaticText(panel, wxID_ANY, "Nota 1");
    n1_input = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition);
    n1_input->SetMaxSize(wxSize(150, -1));
    n1_input->Bind(wxEVT_CHAR, &DialogAl::OnChar2, this);

    wxStaticText* n2_label = new wxStaticText(panel, wxID_ANY, "Nota 2");
    n2_input = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition);
    n2_input->SetMaxSize(wxSize(150, -1));
    n2_input->Bind(wxEVT_CHAR, &DialogAl::OnChar2, this);

    wxStaticText* n3_label = new wxStaticText(panel, wxID_ANY, "Nota 3");
    n3_input = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition);
    n3_input->SetMaxSize(wxSize(150, -1));
    n3_input->Bind(wxEVT_CHAR, &DialogAl::OnChar2, this);

    wxStaticText* n4_label = new wxStaticText(panel, wxID_ANY, "Nota 4");
    n4_input = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition);
    n4_input->SetMaxSize(wxSize(150, -1));
    n4_input->Bind(wxEVT_CHAR, &DialogAl::OnChar2, this);

    btn_add_mat = new wxButton(panel, wxID_ANY, "Cadastrar", wxDefaultPosition, wxSize(125, -1));
    btn_add_mat->Bind(wxEVT_BUTTON, &DialogAl::OnAddMat, this);

    wxStaticText* grid_title = new wxStaticText(panel, wxID_ANY, "Boletim escolar");
    grid_title->SetFont(font_subtitle);

    grid = new wxGrid(panel, wxID_ANY, wxDefaultPosition, wxSize(425, -1));
    grid->CreateGrid(5, 4);
    grid->EnableEditing(false);

    grid->SetRowLabelValue(0, "Nota 1");
    grid->SetRowLabelValue(1, "Nota 2");
    grid->SetRowLabelValue(2, "Nota 3");
    grid->SetRowLabelValue(3, "Nota 4");
    grid->SetRowLabelValue(4, "Media");

    grid->SetColLabelValue(0, "");
    grid->SetColLabelValue(1, "");
    grid->SetColLabelValue(2, "");
    grid->SetColLabelValue(3, "");

    list_mat = new wxListCtrl(panel, wxID_ANY, wxDefaultPosition, wxSize(425, 150), wxLC_REPORT);
    list_mat->InsertColumn(0, wxT("Aluno"), wxLIST_FORMAT_LEFT, 100);
    list_mat->InsertColumn(1, wxT("Disciplina"), wxLIST_FORMAT_LEFT, 100);
    list_mat->InsertColumn(2, wxT("Ano"), wxLIST_FORMAT_LEFT, 100);
    list_mat->InsertColumn(3, wxT("Serie"), wxLIST_FORMAT_LEFT, 100);

    std::stringstream ss;
    ss << "matriculas/matriculas-" << aluno->getCodigo() << ".csv";
    std::string filepath = ss.str();
    matriculas = loadAllMat(filepath);
    OnLoadMat();

    //Posicionando ========================================================================
    wxSizer* sizer_year = new wxBoxSizer(wxHORIZONTAL);
    sizer_year->Add(year_label, 0, wxALIGN_CENTER | wxRIGHT, 5);
    sizer_year->Add(year_input, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

    wxSizer* sizer_gra = new wxBoxSizer(wxHORIZONTAL);
    sizer_gra->Add(ser_label, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
    sizer_gra->Add(select_gra, 1, wxLEFT, 5);

    wxSizer* sizer_l1 = new wxBoxSizer(wxHORIZONTAL);
    sizer_l1->Add(sizer_year, 1);
    sizer_l1->Add(sizer_gra, 1);

    wxSizer* sizer_l2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_l2->Add(select_label, 0, wxALIGN_CENTER);
    sizer_l2->Add(select_dis, 1, wxLEFT, 5);

    wxSizer* sizer_l1l2 = new wxBoxSizer(wxVERTICAL);
    sizer_l1l2->Add(sizer_l1, 0, wxEXPAND | wxBOTTOM, 10);
    sizer_l1l2->Add(sizer_l2, 0, wxEXPAND);

    wxSizer* sizer_n1 = new wxBoxSizer(wxVERTICAL);
    sizer_n1->Add(n1_label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    sizer_n1->Add(n1_input, 0, wxEXPAND);

    wxSizer* sizer_n2 = new wxBoxSizer(wxVERTICAL);
    sizer_n2->Add(n2_label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    sizer_n2->Add(n2_input, 0, wxEXPAND);

    wxSizer* sizer_n3 = new wxBoxSizer(wxVERTICAL);
    sizer_n3->Add(n3_label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    sizer_n3->Add(n3_input, 0, wxEXPAND);

    wxSizer* sizer_n4 = new wxBoxSizer(wxVERTICAL);
    sizer_n4->Add(n4_label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
    sizer_n4->Add(n4_input, 0, wxEXPAND);

    wxSizer* sizer_n = new wxBoxSizer(wxHORIZONTAL);
    sizer_n->Add(sizer_n1, 1, wxRIGHT, 5);
    sizer_n->Add(sizer_n2, 1, wxLEFT | wxRIGHT, 5);
    sizer_n->Add(sizer_n3, 1, wxLEFT | wxRIGHT, 5);
    sizer_n->Add(sizer_n4, 1, wxLEFT, 5);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(title_label, 0, wxALIGN_CENTER | wxTOP, 10);
    sizer->Add(desc, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    sizer->Add(sizer_l1l2, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    sizer->Add(sizer_n, 0, wxALIGN_CENTER | wxTOP, 5);
    sizer->Add(btn_add_mat, 0, wxALIGN_CENTER | wxTOP, 15);
    sizer->Add(grid_title, 0, wxALIGN_CENTER | wxTOP, 25);
    sizer->Add(grid, 0, wxALIGN_CENTER | wxTOP, 5);
    sizer->Add(list_mat, 0, wxALIGN_CENTER | wxTOP, 15);

    panel->SetSizerAndFit(sizer);
}

std::vector<Disciplina*> DialogAl::loadDis(const std::string& filename) {
    std::vector<Disciplina*> disciplinas;
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open()) return {};

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string id;
        std::string name;
        std::string ch;
        std::string pratica;
        std::string chp;

        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, ch, ',');
        getline(iss, pratica, ',');
        getline(iss, chp, '\n');

        if (id.empty() || name.empty()) continue;

        long int_pratica;
        wxString pwx(pratica);
        pwx.ToLong(&int_pratica);

        long int_id;
        wxString idwx(id);
        idwx.ToLong(&int_id);

        long int_ch;
        wxString chwx(ch);
        chwx.ToLong(&int_ch);

        long int_chp;
        wxString chpwx(chp);
        chpwx.ToLong(&int_chp);

        if (int_pratica == 0) {
            Disciplina* dis = new Disciplina(int_id, name, int_ch);
            disciplinas.push_back(dis);
        } else if (int_pratica == 1) {
            DisciplinaPratica* dis = new DisciplinaPratica(int_id, name, int_ch, int_chp);
            disciplinas.push_back(dis);
        }
    }

    return disciplinas;
}

void DialogAl::OnAddMat(wxCommandEvent& evt) {
    if (year_input->GetValue().ToStdString() == "" || select_gra->GetSelection() == wxNOT_FOUND ||
        select_dis->GetSelection() == wxNOT_FOUND || n1_input->GetValue().ToStdString() == "" ||
        n2_input->GetValue().ToStdString() == "" || n3_input->GetValue().ToStdString() == "" ||
        n4_input->GetValue().ToStdString() == "") {
        wxMessageBox(wxT("Campos obrigatoris faltando"), wxT("Erro"), wxICON_ERROR | wxOK, this);
        return;
    }

    wxString year(year_input->GetValue());
    wxString gra(select_gra->GetString(select_gra->GetCurrentSelection()));
    int dis = select_dis->GetCurrentSelection();
    wxString n1(n1_input->GetValue());
    wxString n2(n2_input->GetValue());
    wxString n3(n3_input->GetValue());
    wxString n4(n4_input->GetValue());

    long int_year;
    year.ToLong(&int_year);

    double float_n1;
    n1.ToDouble(&float_n1);

    double float_n2;
    n2.ToDouble(&float_n2);

    double float_n3;
    n3.ToDouble(&float_n3);

    double float_n4;
    n4.ToDouble(&float_n4);

    if (float_n1 > 10 || float_n2 > 10 || float_n3 > 10 || float_n4 > 10) {
        wxMessageBox(wxT("Informe uma nota valida"), wxT("Erro"), wxICON_ERROR | wxOK, this);
        return;
    }

    Matricula* mat = new Matricula(int_year, gra.ToStdString(), aluno, disciplinas[dis], float_n1,
                                   float_n2, float_n3, float_n4);
    matriculas.push_back(mat);

    std::stringstream ss;
    ss << "matriculas/matriculas-" << aluno->getCodigo() << ".csv";
    std::string filepath = ss.str();
    OnLoadMat();

    mat->AppendToFile(filepath);
    year_input->Clear();
    select_gra->SetSelection(wxNOT_FOUND);
    select_dis->SetSelection(wxNOT_FOUND);
    n1_input->Clear();
    n2_input->Clear();
    n3_input->Clear();
    n4_input->Clear();
}

std::vector<Matricula*> DialogAl::loadAllMat(const std::string& filename) {
    std::vector<Matricula*> mat;
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open()) return {};

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string sid_al;
        std::string sid_dis;
        std::string syear;
        std::string gra;
        std::string sn1;
        std::string sn2;
        std::string sn3;
        std::string sn4;

        getline(iss, sid_al, ',');
        getline(iss, sid_dis, ',');
        getline(iss, syear, ',');
        getline(iss, gra, ',');
        getline(iss, sn1, ',');
        getline(iss, sn2, ',');
        getline(iss, sn3, ',');
        getline(iss, sn4, '\n');

        if (sid_al.empty() || sid_dis.empty() || gra.empty()) continue;

        wxString id_al(sid_al);
        wxString year(syear);
        wxString n1(sn1);
        wxString n2(sn2);
        wxString n3(sn3);
        wxString n4(sn4);
        wxString id_dis(sid_dis);

        int int_id_al;
        id_al.ToInt(&int_id_al);

        long int_id_dis;
        id_dis.ToLong(&int_id_dis);

        long int_year;
        year.ToLong(&int_year);

        double float_n1;
        n1.ToDouble(&float_n1);

        double float_n2;
        n2.ToDouble(&float_n2);

        double float_n3;
        n3.ToDouble(&float_n3);

        double float_n4;
        n4.ToDouble(&float_n4);

        Disciplina* disciplina;

        for (Disciplina* dis : disciplinas) {
            if (dis->getCodigo() == int_id_dis) {
                disciplina = dis;
                break;
            }
        }

        Matricula* m =
            new Matricula(int_year, gra, aluno, disciplina, float_n1, float_n2, float_n3, float_n4);
        mat.push_back(m);
    }

    return mat;
}

void DialogAl::OnLoadMat() {
    list_mat->DeleteAllItems();

    int i = 0;
    for (Matricula* mat : matriculas) {
        int j = 0;
        wxString data1 = wxString::Format(wxT("%s"), mat->getAluno()->getNome());
        wxString data2 = wxString::Format(wxT("%s"), mat->getDisciplina()->getNome());
        wxString data3 = wxString::Format(wxT("%li"), mat->getAnoLetivo());
        wxString data4 = wxString::Format(wxT("%s"), mat->getSerie());

        long index = list_mat->InsertItem(0, data1);
        list_mat->SetItem(index, 1, data2);
        list_mat->SetItem(index, 2, data3);
        list_mat->SetItem(index, 3, data4);

        std::vector<float> ns;
        ns.push_back(mat->getNota1());
        ns.push_back(mat->getNota2());
        ns.push_back(mat->getNota3());
        ns.push_back(mat->getNota4());

        grid->SetColLabelValue(i, mat->getDisciplina()->getNome());

        for (j; j < 4; j++) grid->SetCellValue(j, i, wxString::Format(wxT("%.2f"), ns[j]));

        grid->SetCellValue(4, i,
                           wxString::Format(wxT("%.2f"), mat->getDisciplina()->calcularMedia(
                                                             ns[0], ns[1], ns[2], ns[3])));
        i++;
    }
}

void DialogAl::OnChar(wxKeyEvent& event) {
    int keyCode = event.GetKeyCode();

    if ((keyCode >= '0' && keyCode <= '9') || keyCode == WXK_BACK || keyCode == WXK_RETURN) {
        event.Skip();
    }
}

void DialogAl::OnChar2(wxKeyEvent& event) {
    int keyCode = event.GetKeyCode();

    if ((keyCode >= '0' && keyCode <= '9') || keyCode == '.' || keyCode == WXK_BACK ||
        keyCode == WXK_RETURN) {
        event.Skip();
    }
}
