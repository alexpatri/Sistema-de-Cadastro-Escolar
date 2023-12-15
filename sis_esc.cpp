#include "sis_esc.hpp"

#include <wx/listctrl.h>
#include <wx/spinctrl.h>

#include <cstdio>
#include <string>

#include "escola/aluno.hpp"
#include "escola/disciplina.hpp"
#include "escola/matricula.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Centre();
    frame->Show(true);
    return true;
}

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Escola") {
    //Definindo Variaveis
    //tamanho da Fonte de Títulos
    wxFont font_title;
    font_title.SetPointSize(20);

    //Tamanho da Fonte Padrão
    wxFont font;
    font.SetPointSize(12);

    //Seção Adicionar Aluno
    wxPanel* panel_al_title = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 150));
    //panel_al_title->SetBackgroundColour(wxColor(20, 160, 170));

    wxPanel* line = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1, -1));
    line->SetBackgroundColour(wxColor(232, 232, 232));

    wxStaticText* title_al =
        new wxStaticText(panel_al_title, wxID_ANY, "Novo Aluno", wxDefaultPosition, wxSize(-1, -1));
    title_al->SetFont(font_title);
    //titulo_al->SetBackgroundColour(wxColor(220, 50, 125));

    wxPanel* panel_al = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 300));
    //panel_al->SetBackgroundColour(wxColor(100, 100, 200));

    wxStaticText* name_label_al = new wxStaticText(panel_al, wxID_ANY, "Nome:", wxDefaultPosition);
    //name_label_al->SetFont(font);

    name_input_al = new wxTextCtrl(panel_al, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));

    btn_add_al = new wxButton(panel_al, wxID_ANY, "Adicionar", wxDefaultPosition, wxSize(100, -1));
    btn_add_al->Bind(wxEVT_BUTTON, &MainFrame::OnAddAl, this);

    //Seção Adicionar Disciplina
    wxPanel* panel_dis_title = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(250, 150));
    //panel_dis_title->SetBackgroundColour(wxColor(200, 10, 180));

    wxStaticText* title_dis = new wxStaticText(panel_dis_title, wxID_ANY, "Nova Disciplina");
    title_dis->SetFont(font_title);

    wxPanel* line2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1, -1));
    line2->SetBackgroundColour(wxColor(232, 232, 232));

    //Esquerda
    wxPanel* panel_dis_l = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(125, 300));
    //panel_dis_l->SetBackgroundColour(wxColor(100, 200, 100));

    wxStaticText* name_label_dis = new wxStaticText(panel_dis_l, wxID_ANY, "Nome:");

    name_input_dis = new wxTextCtrl(panel_dis_l, wxID_ANY, "", wxDefaultPosition, wxSize(300, -1));

    wxStaticText* ch_label = new wxStaticText(panel_dis_l, wxID_ANY, "Carga Horaria:");

    ch_spin = new wxSpinCtrl(panel_dis_l, wxID_ANY);

    //Direita
    wxPanel* panel_dis_r = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(125, 300));
    //panel_dis_r->SetBackgroundColour(wxColor(100, 200, 150));

    check_box_dis = new wxCheckBox(panel_dis_r, wxID_ANY, "Disciplina Pratica");

    wxStaticText* chp_label = new wxStaticText(panel_dis_r, wxID_ANY, "Carga Horaria Pratica:");

    chp_spin = new wxSpinCtrl(panel_dis_r, wxID_ANY);

    btn_add_dis =
        new wxButton(panel_dis_r, wxID_ANY, "Adicionar", wxDefaultPosition, wxSize(100, -1));
    btn_add_dis->Bind(wxEVT_BUTTON, &MainFrame::OnAddDis, this);

    //Seção de Visualização
    wxPanel* panel_vis = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 200));
    //panel_vis->SetBackgroundColour(wxColor(200, 100, 100));

    wxPanel* panel_vis_info = new wxPanel(panel_vis, wxID_ANY);
    //panel_vis_info->SetBackgroundColour(wxColor(200, 100, 100));

    btn_vis_al =
        new wxButton(panel_vis_info, wxID_ANY, "Ver Alunos", wxDefaultPosition, wxSize(150, -1));
    btn_vis_al->Bind(wxEVT_BUTTON, &MainFrame::OnSeeAl, this);

    btn_vis_dis = new wxButton(panel_vis_info, wxID_ANY, "Ver Disciplinas", wxDefaultPosition,
                               wxSize(150, -1));
    btn_vis_dis->Bind(wxEVT_BUTTON, &MainFrame::OnSeeDis, this);

    btn_vis_clear =
        new wxButton(panel_vis_info, wxID_ANY, "Limpar Tudo", wxDefaultPosition, wxSize(150, -1));
    btn_vis_clear->Bind(wxEVT_BUTTON, &MainFrame::OnClearAll, this);

    //Lista
    list_ctrl =
        new wxListCtrl(panel_vis, wxID_ANY, wxDefaultPosition, wxSize(500, 200), wxLC_REPORT);
    list_ctrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, &MainFrame::OnOpenDialog, this);

    //Posicionando os Ctrl na tela =============================================================
    //painel Add Aluno (panel_al)
    wxSizer* sizer_alc = new wxBoxSizer(wxVERTICAL);
    sizer_alc->Add(name_label_al, 0, wxBOTTOM | wxTOP, 5);
    sizer_alc->Add(name_input_al, 0, wxRIGHT, 5);
    sizer_alc->Add(btn_add_al, 0, wxBOTTOM | wxTOP, 5);

    wxSizer* sizer_al = new wxBoxSizer(wxVERTICAL);
    sizer_al->Add(sizer_alc, 0, wxALIGN_LEFT);
    panel_al->SetSizerAndFit(sizer_al);

    //Painel Add Disciplina (panel_dis_l, panel_dis_r)
    //panel_dis_l
    wxSizer* sizer_ch = new wxBoxSizer(wxHORIZONTAL);
    sizer_ch->Add(ch_label, 0, wxALIGN_CENTER);
    sizer_ch->Add(ch_spin, 0, wxALIGN_CENTER | wxLEFT, 5);

    wxSizer* sizer_dis_lc = new wxBoxSizer(wxVERTICAL);
    sizer_dis_lc->Add(name_label_dis, 0, wxTOP | wxBOTTOM, 5);
    sizer_dis_lc->Add(name_input_dis, 0, wxEXPAND);
    sizer_dis_lc->Add(sizer_ch, 0, wxTOP, 5);

    wxSizer* sizer_dis_l = new wxBoxSizer(wxVERTICAL);
    sizer_dis_l->Add(sizer_dis_lc, 0, wxALIGN_LEFT);
    panel_dis_l->SetSizerAndFit(sizer_dis_l);

    //panel_dis_r
    wxSizer* sizer_chp = new wxBoxSizer(wxHORIZONTAL);
    sizer_chp->Add(chp_label, 0, wxALIGN_CENTER | wxLEFT, 5);
    sizer_chp->Add(chp_spin, 0, wxALIGN_CENTER | wxLEFT, 5);

    wxSizer* sizer_dis_rc = new wxBoxSizer(wxVERTICAL);
    sizer_dis_rc->Add(check_box_dis, 0);
    sizer_dis_rc->Add(sizer_chp, 0, wxLEFT, 5);
    sizer_dis_rc->Add(btn_add_dis, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM, 5);

    wxSizer* sizer_dis_r = new wxBoxSizer(wxVERTICAL);
    sizer_dis_r->Add(sizer_dis_rc, 0, wxALIGN_RIGHT);
    panel_dis_r->SetSizerAndFit(sizer_dis_r);

    //Juntando os Paineis
    wxSizer* sizer_content = new wxBoxSizer(wxHORIZONTAL);
    sizer_content->Add(panel_al, 1, wxEXPAND);
    sizer_content->Add(line2, 0, wxEXPAND);
    sizer_content->Add(panel_dis_l, 1, wxEXPAND | wxLEFT, 15);
    sizer_content->Add(panel_dis_r, 1, wxALIGN_BOTTOM);

    //Painel Títulos
    wxSizer* sizer_al_title = new wxBoxSizer(wxHORIZONTAL);
    sizer_al_title->Add(title_al, 0);
    panel_al_title->SetSizerAndFit(sizer_al_title);

    wxSizer* sizer_dis_title = new wxBoxSizer(wxHORIZONTAL);
    sizer_dis_title->Add(title_dis, 0, wxLEFT, 15);
    panel_dis_title->SetSizerAndFit(sizer_dis_title);

    wxSizer* sizer_title = new wxBoxSizer(wxHORIZONTAL);
    sizer_title->Add(panel_al_title, 1, wxEXPAND);
    sizer_title->Add(line, 0, wxEXPAND);
    sizer_title->Add(panel_dis_title, 2, wxEXPAND);

    wxSizer* sizer_add = new wxBoxSizer(wxVERTICAL);
    sizer_add->Add(sizer_title, 1, wxEXPAND);
    sizer_add->Add(sizer_content, 2, wxEXPAND);

    //Painel de Visualização
    wxSizer* sizer_vis_info = new wxBoxSizer(wxVERTICAL);
    sizer_vis_info->Add(btn_vis_al, 0);
    sizer_vis_info->Add(btn_vis_dis, 0, wxTOP, 5);
    sizer_vis_info->Add(btn_vis_clear, 0, wxTOP, 5);
    panel_vis_info->SetSizerAndFit(sizer_vis_info);

    wxSizer* sizer_vis = new wxBoxSizer(wxHORIZONTAL);
    sizer_vis->Add(panel_vis_info, 1, wxEXPAND | wxTOP, 60);
    sizer_vis->Add(list_ctrl, 4, wxEXPAND | wxTOP, 60);
    panel_vis->SetSizerAndFit(sizer_vis);

    //Sizer Principal (Junta todos os demais)
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(sizer_add, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 100);
    sizer->Add(panel_vis, 2, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 100);
    this->SetSizerAndFit(sizer);
}

//Lógica ==================================================================
void MainFrame::OnLoadAl() {
    list_ctrl->ClearAll();

    list_ctrl->InsertColumn(0, wxT("Tipo"));
    list_ctrl->InsertColumn(1, wxT("Codigo"), wxLIST_FORMAT_LEFT, 150);
    list_ctrl->InsertColumn(2, wxT("Nome"), wxLIST_FORMAT_LEFT, 150);

    list_ctrl->SetColumnWidth(0, 0);

    std::string id;
    std::string name;

    std::ifstream file("alunos.csv");

    if (!file.is_open()) {
        wxMessageBox(wxT("Erro ao abrir o arquivo alunos.csv"), wxT("Erro"), wxICON_ERROR | wxOK,
                     this);
        return;
    }

    int i = 0;
    while (file.good()) {
        getline(file, id, ',');
        getline(file, name, '\n');

        if (id.empty() || name.empty()) { continue; }

        wxString data1 = wxString::Format(wxT("1"));
        wxString data2 = wxString::Format(wxT("%s"), id);
        wxString data3 = wxString::Format(wxT("%s"), name);

        long index = list_ctrl->InsertItem(i, data1);
        list_ctrl->SetItem(index, 1, data2);
        list_ctrl->SetItem(index, 2, data3);
    }
}

void MainFrame::OnLoadDis() {
    list_ctrl->ClearAll();

    list_ctrl->InsertColumn(0, wxT("Tipo"));
    list_ctrl->InsertColumn(1, wxT("Codigo"), wxLIST_FORMAT_LEFT, 150);
    list_ctrl->InsertColumn(2, wxT("Nome"), wxLIST_FORMAT_LEFT, 150);
    list_ctrl->InsertColumn(3, wxT("Carga Horaria"), wxLIST_FORMAT_LEFT, 150);
    list_ctrl->InsertColumn(4, wxT("Pratica"), wxLIST_FORMAT_LEFT, 150);
    list_ctrl->InsertColumn(5, wxT("Carga Horaria Pratica"), wxLIST_FORMAT_LEFT, 150);

    list_ctrl->SetColumnWidth(0, 0);

    std::string id;
    std::string name;
    std::string ch;
    std::string pratica;
    std::string chp;

    std::ifstream file("disciplina.csv");

    if (!file.is_open()) {
        wxMessageBox(wxT("Erro ao abrir o arquivo disciplina.csv"), wxT("Erro"),
                     wxICON_ERROR | wxOK, this);
        return;
    }

    int i = 0;
    while (file.good()) {
        getline(file, id, ',');
        getline(file, name, ',');
        getline(file, ch, ',');
        getline(file, pratica, ',');
        getline(file, chp, '\n');

        if (id.empty() || name.empty() || ch.empty() || pratica.empty() || chp.empty()) {
            continue;
        }

        wxString data1 = wxString::Format(wxT("0"));
        wxString data2 = wxString::Format(wxT("%s"), id);
        wxString data3 = wxString::Format(wxT("%s"), name);
        wxString data4 = wxString::Format(wxT("%s"), ch);
        wxString data5 = wxString::Format(wxT("%s"), pratica == "1" ? "S" : "N");
        wxString data6 = wxString::Format(wxT("%s"), pratica == "1" ? chp : "");

        long index = list_ctrl->InsertItem(i, data1);
        list_ctrl->SetItem(index, 1, data2);
        list_ctrl->SetItem(index, 2, data3);
        list_ctrl->SetItem(index, 3, data4);
        list_ctrl->SetItem(index, 4, data5);
        list_ctrl->SetItem(index, 5, data6);
    }
}

void MainFrame::OnAddAl(wxCommandEvent& evt) {
    int nextId;
    std::ifstream fileId;
    fileId.open("nextIdAl.txt");

    if (name_input_al->GetValue().ToStdString() == "") {
        wxMessageBox(wxT("Campos obrigatoris faltando"), wxT("Erro"), wxICON_ERROR | wxOK, this);
        return;
    }

    if (fileId.good()) {
        fileId >> nextId;
        fileId.close();
    } else {
        fileId.close();

        nextId = 1;
        std::ofstream newFile;
        newFile.open("nextIdAl.txt");

        newFile << nextId;
        newFile.close();
    }

    Aluno* al = new Aluno(nextId, name_input_al->GetValue().ToStdString());
    al->appendToFile("alunos.csv");

    nextId++;

    std::ofstream fileIdWriter;
    fileIdWriter.open("nextIdAl.txt");
    fileIdWriter << nextId;
    fileIdWriter.close();

    name_input_al->Clear();
    delete al;

    OnLoadAl();
}

void MainFrame::OnAddDis(wxCommandEvent& evt) {
    int nextId;
    std::ifstream fileId;
    fileId.open("nextIdDis.txt");

    if (name_input_dis->GetValue().ToStdString() == "" || ch_spin->GetValue() == 0) {
        wxMessageBox(wxT("Campos obrigatoris faltando"), wxT("Erro"), wxICON_ERROR | wxOK, this);
        return;
    }

    if (!check_box_dis->GetValue() && chp_spin->GetValue() > 0) {
        wxMessageBox(
            wxT("Para adicionar carga horaria pratica disciplina pratica deve estar ativa."),
            wxT("Erro"), wxICON_ERROR | wxOK, this);
        return;
    }

    if (check_box_dis->GetValue() && chp_spin->GetValue() == 0) {
        wxMessageBox(wxT("Campos obrigatoris faltando"), wxT("Erro"), wxICON_ERROR | wxOK, this);
        return;
    }

    if (fileId.good()) {
        fileId >> nextId;
        fileId.close();
    } else {
        fileId.close();

        nextId = 1;
        std::ofstream newFile;
        newFile.open("nextIdDis.txt");

        newFile << nextId;
        newFile.close();
    }

    if (!check_box_dis->GetValue()) {
        Disciplina* dis =
            new Disciplina(nextId, name_input_dis->GetValue().ToStdString(), ch_spin->GetValue());
        dis->appendToFile("disciplina.csv");
        delete dis;
    } else {
        DisciplinaPratica* disp =
            new DisciplinaPratica(nextId, name_input_dis->GetValue().ToStdString(),
                                  ch_spin->GetValue(), chp_spin->GetValue());
        disp->appendToFile("disciplina.csv");
        delete disp;
    }

    nextId++;
    std::ofstream fileIdWriter;
    fileIdWriter.open("nextIdDis.txt");
    fileIdWriter << nextId;
    fileIdWriter.close();

    name_input_dis->Clear();
    ch_spin->SetValue(0);
    check_box_dis->SetValue(false);
    chp_spin->SetValue(0);

    OnLoadDis();
}

void MainFrame::OnSeeAl(wxCommandEvent& evt) {
    OnLoadAl();
}

void MainFrame::OnSeeDis(wxCommandEvent& evt) {
    OnLoadDis();
}

bool MainFrame::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void MainFrame::OnClearAll(wxCommandEvent& evt) {
    int nextId;
    std::ifstream file("nextIdAl.txt");

    if (file.good()) {
        file >> nextId;

        for (int i = 1; i < nextId; i++) {
            std::stringstream ss;
            ss << "matriculas/matriculas-" << i << ".csv";
            std::string filepath = ss.str();

            if (!fileExists(filepath)) continue;

            if (std::remove(filepath.c_str()) != 0) {
                wxMessageBox(wxT("Nao foi possivel excluir os itens"), wxT("Algo deu Errado"),
                             wxICON_ERROR | wxOK, this);
                return;
            }
        }
    }

    std::ofstream file1("alunos.csv");
    std::ofstream file2("nextIdAl.txt");
    std::ofstream file3("disciplina.csv");
    std::ofstream file4("nextIdDis.txt");

    if (!file1.is_open() | !file2.is_open() | !file3.is_open() | !file4.is_open()) {
        wxMessageBox(wxT("Nao foi possivel excluir os itens"), wxT("Algo deu Errado"),
                     wxICON_ERROR | wxOK, this);
        return;
    }

    file2 << 1;
    file1 << "";
    file3 << "";
    file4 << 1;

    OnLoadDis();
}

void MainFrame::OnOpenDialog(wxListEvent& evt) {
    int itemIndex = evt.GetIndex();
    wxString column_value = list_ctrl->GetItemText(itemIndex, 0);

    long value;
    column_value.ToLong(&value);

    if (value == 0) return;

    wxString cod = list_ctrl->GetItemText(itemIndex, 1);

    long int_cod;
    cod.ToLong(&int_cod);

    wxString name = list_ctrl->GetItemText(itemIndex, 2);

    Aluno* aluno = new Aluno(int_cod, name.ToStdString());

    DialogAl* dialogAl = new DialogAl(this, "Aluno", aluno);
    dialogAl->ShowModal();
}
