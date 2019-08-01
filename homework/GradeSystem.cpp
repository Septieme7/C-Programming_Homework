//
// Created by Septieme on 2019/7/29.
//

#include <libloaderapi.h>
#include <io.h>
#include "GradeSystem.h"
#include "iostream"
#include "iomanip"


int compareGrade(Profile a, Profile b) {
    if (a.getGrade() == b.getGrade())
        return a.getGPA() > b.getGPA();
    return a.getGrade() > b.getGrade();
}

int compareGrade2(GradeBean a, GradeBean b) {
    if (a.grade == b.grade)
        return a.id > b.id;
    return a.grade > b.grade;
}

void GradeSystem::introduction() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "��������������������  ��   ѧ �� �� �� �� �� ϵ  ͳ     ��  ��������������������" << std::endl;
    std::cout << "��������������������         ��������         �������������������" << std::endl;
    std::cout << "��������������������  ��         1.����ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         2.��ѯѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         3.����ͳ�Ƴɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         4.ɾ��ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         5.�޸�ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         6.�鿴�ɼ�����         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         0.��ȫ�˳�ϵͳ         ��  �������������������" << std::endl;
}

// ͨ��ѧ��ѧ�Ų�ѯ
void GradeSystem::searchById() {
    Profile s;
    std::cout << "��������Ҫ��ѯ��ѧ����ѧ�ţ�" << std::endl;
    std::string id;
    std::cin >> id;
    std::vector<Subject> all;
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            std::cout << "ѧ�������� " << students[i].name << " ѧ�ţ� " << students[i].id << std::endl;
            s = students[i];
            students[i].getCommonSubjects(all);
            students[i].getElectiveSubjects(all);
            break;
        }           //  ��ȡѧ���ɼ���Ϣ
    }
    if (i == students.size()) {
        std::cout << "���������ڣ�" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "��Ŀ     ѧ��     �ɼ�     ����     �γ�����" << std::endl;
    for (int j = 0; j < all.size(); j++) {
        Subject subject = all[j];
        std::cout << subject.name << "  " << subject.getCredit() << "  " << subject.getGrade() << "  "
                  << subject.getGPA() << "  ";
        if (subject.dir == 1)
            std::cout << "����" << std::endl;
        else
            std::cout << "ѡ��" << std::endl;
    }
    std::cout << std::setprecision(4) << "ƽ��GPA��" << s.getGPA();
    std::cout << "  ƽ����Ȩ��" << s.getGrade() << "    ��ѧ������" << s.getCredit() << std::endl;
    exit2Menu();
}

// ͨ��ѧ��������ѯ
void GradeSystem::searchByName() {
    Profile s;
    std::cout << "��������Ҫ��ѯ��ѧ����������" << std::endl;
    std::string name;
    std::cin >> name;
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].name == name) {             // ��Ϊ���ܴ���ͬ������������ҵ������
            std::vector<Subject> all;
            std::cout << "ѧ�������� " << students[i].name << " ѧ�ţ� " << students[i].id << std::endl;
            s = students[i];
            students[i].getCommonSubjects(all);
            students[i].getElectiveSubjects(all);
            std::cout << "��Ŀ     ѧ��     �ɼ�     ����     �γ�����" << std::endl;
            for (int j = 0; j < all.size(); j++) {
                Subject subject = all[j];
                std::cout << subject.name << "   " << subject.getCredit() << "   " << subject.getGrade() << "  "
                          << subject.getGPA() << "   ";
                if (subject.dir == 1)
                    std::cout << "����" << std::endl;
                else
                    std::cout << "ѡ��" << std::endl;
            }
            std::cout << std::setprecision(4) << "ƽ��GPA��" << s.getGPA();
            std::cout << "   ƽ����Ȩ��" << s.getGrade() << "    ��ѧ������" << s.getCredit() << std::endl << std::endl;
        }           //  ��ȡѧ���ɼ���Ϣ
    }
    if (i == students.size() && students[i - 1].name != name) {
        std::cout << "���������ڣ�" << std::endl;
        exit2Menu();
        return;
    }
    exit2Menu();
}

void GradeSystem::addInformationByFile() {
    char buff[1000];
    _getcwd(buff, 1000);        // ��ȡ��ǰ���ɵ�exe����ľ���·��
    std::cout << "���ڵ�ǰ��ʾ��Ŀ¼�ڽ���һ����Ϊ\"scores.txt\" ���ı��ĵ�(����ʹ��GBK���룬UTF-8���ܻᵼ�³�������)��������ָ����ʽ����ɼ�" << std::endl;
    std::cout << "����Ҫ��: ��һ��Ϊ�����ѧ������, �ӵڶ��п�ʼΪÿλѧ����������ѧ�źͿ�Ŀ����n" << std::endl;
    std::cout << buff << std::endl;
    std::cout << "����n�����գ���Ŀ  ��Ŀѧ��  �ɼ�  �γ����ͣ�1���� 0ѡ�ޣ��ĸ�ʽ����ɼ�" << std::endl;
    std::cout << "�ĵ��༭��Ϻ����������ַ���ʼ¼��" << std::endl;
    std::string move;
    std::cin >> move;
    strcat(buff, "\\scores.txt");   // �ڵ�ǰ·���������·��
    std::ifstream in;
    in.open(buff, std::ios::in);
    int t;
    in >> t;
    for (int j = 0; j < t; j++) {
        std::string name, id, sub;
        int num;
        in >> name >> id >> num;
        students.push_back(Profile(name, id));
        Profile &a = students.back();
        for (int i = 0; i < num; i++) {
            double credit;
            int grade, dir;
            in >> sub >> credit >> grade >> dir;
            try {
                if (in.fail())
                    throw 1;
            }                   // �쳣���� ��ֹ���������ʽ�����³������
            catch (int) {
                in.clear();
                in.sync();
                std::cout << "ѧ�� " << a.name << " ��" << "��Ŀ " << sub << " �����ʽ�����˴��󣬶�ȡ���̽���" << std::endl;
                std::cout << " �ڴ�ѧ����ǰ��ѧ���ɼ����ѳɹ��Ǽǣ������������ļ���ʽ���ٵǼ�����ͬѧ�ĳɼ�" << std::endl;
                students.pop_back();   // ��������ѧ����Ϣ����ɾ��
                return;
            }
            Subject subject(sub, credit, grade, dir);
            addScore(sub, subject.getGPA(), grade, credit, dir);        // ��ϵͳ�м����¿�Ŀ

            double c, g, G, sum_g, sum_G;
            int r;
            students.back().getAll(G, g, c, r);
            sum_g = g * c;
            sum_G = G * c;
            c += credit;
            g = (sum_g + grade * credit) / c;
            G = (sum_G + subject.getGPA() * credit) / c;
            students.back().setAll(G, g, c, r);                         // ʵʱͳ�ƴ�ѧ���ɼ�

            if (subject.dir == 1) {
                a.addCommonSubject(subject);
                a.num_com++;
            } else {
                a.addElectiveSubject(subject);
                a.num_elec++;
            }
        }
        std::cout << "������Ϊѧ�� " << a.name << " �Ǽ��� " << a.num_com << " �ű��޿γɼ��� " << a.num_elec << " ��ѡ�޿γɼ�"
                  << std::endl;
    }
    in.close();
    exit2Menu();
}

void GradeSystem::addInformationByTap() {
    std::string name, id;
    char flag;
    std::cout << "�������ѧ����������" << std::endl;
    std::cin >> name;
    std::cout << "�������ѧ����ѧ�ţ�" << std::endl;
    std::cin >> id;
    std::cout << "�������ѧ����ϢΪ: ����: " << name << " ѧ�ţ� " << id << std::endl;
    std::cout << "��ȷ������ 1 �� ���������� 2 ���������룬���������� 0" << std::endl;
    std::cin >> flag;
    switch (flag - '0') {
        case 0:
            introduction();
            return;
        case 1:
            break;
        case 2:
            addInformationByTap();
            return;
    }
    students.push_back(Profile(name, id));
    std::cout << "�밴�����¸�ʽ�����ѧ���ĳɼ���" << std::endl;
    std::string sub;
    int grade, dir;
    double credit;
    std::cout << "��Ŀ  ��Ŀѧ��  �ɼ�  �γ����ͣ�1���� 0ѡ�ޣ�(�ĸ���Ŀ��Ϊ0����������" << std::endl;
    while (1) {
        std::cin >> sub >> credit >> grade >> dir;
        try {
            if (std::cin.fail())
                throw 1;
        }                   // �쳣���� ��ֹ���������ʽ�����³������
        catch (int) {
            std::cin.clear();
            std::cin.sync();
            std::cout << "�����ʽ�����˴���, ��ӿ�Ŀ���ƿ�ʼ�������뵱ǰ��Ŀ��" << std::endl;
            continue;
        }
        if (sub == "0" && grade == 0 && credit == 0 && dir == 0)
            break;
        Subject subject(sub, credit, grade, dir);
        addScore(sub, subject.getGPA(), grade, credit, dir);        // ��ϵͳ�м����¿�Ŀ

        double c, g, G, sum_g, sum_G;
        int r;
        students.back().getAll(G, g, c, r);
        sum_g = g * c;
        sum_G = G * c;
        c += credit;
        g = (sum_g + grade * credit) / c;
        G = (sum_G + subject.getGPA() * credit) / c;
        students.back().setAll(G, g, c, r);                         // ʵʱͳ�ƴ�ѧ���ɼ�

        if (subject.dir == 1) {
            students.back().addCommonSubject(subject);
            students.back().num_com++;
        } else {
            students.back().addElectiveSubject(subject);
            students.back().num_elec++;
        }
    }
    Profile a = students.back();
    std::cout << "������Ϊѧ�� " << a.name << " �Ǽ��� " << a.num_com << " �ű��޿γɼ��� " << a.num_elec << " ��ѡ�޿γɼ�" << std::endl;
    exit2Menu();
}

void GradeSystem::addStudent() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "��������������������  ��          ѧ����Ϣ¼��          ��  ��������������������" << std::endl;
    std::cout << "��������������������         ��������         �������������������" << std::endl;
    std::cout << "��������������������  ��         1.ͨ����������(����)   ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         2.ͨ���ļ�����(����)   ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         0.����                ��  �������������������" << std::endl;
    char move;
    while (std::cin >> move) {
        switch (move - '0') {
            case 0:
                introduction();
                return;
            case 1:
                addInformationByTap();
                return;
            case 2:
                addInformationByFile();
                return;
            default:
                std::cout << " �������ָ����ڣ�" << std::endl;
                std::cout << "��������������������  ��         1.ͨ����������(����)   ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         2.ͨ���ļ�����(����)   ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         0.����                ��  �������������������" << std::endl;
        }
    }

}

void GradeSystem::searchStudent() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "��������������������  ��          ѧ���ɼ���ѯ          ��  ��������������������" << std::endl;
    std::cout << "��������������������         ��������         �������������������" << std::endl;
    std::cout << "��������������������  ��         1.ͨ��������ѯ         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         2.ͨ��ѧ�Ų�ѯ         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         0.����                ��  �������������������" << std::endl;
    char move;
    while (std::cin >> move) {
        switch (move - '0') {
            case 0:
                introduction();
                return;
            case 1:
                searchByName();
                return;
            case 2:
                searchById();
                return;
            default:
                std::cout << " �������ָ����ڣ�" << std::endl;
                std::cout << "��������������������  ��         1.ͨ��������ѯ         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         2.ͨ��ѧ�Ų�ѯ         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         0.����                ��  �������������������" << std::endl;
        }
    }
}

void GradeSystem::addScore(std::string name, double GPA, int grade, double credit, int dir) {
    int i = 0;
    for (i = 0; i < scores.size(); i++) {
        if (scores[i].name == name) {
            StacticScore &a = scores[i];
            double total_G = a.GPA * a.studentNum, total_g = a.grade * a.studentNum;
            a.studentNum++;
            a.GPA = (total_G + GPA) / a.studentNum;
            a.grade = (total_g + grade) / a.studentNum;
            break;
        }
    }
    if (i == scores.size()) {    // �˿�ĿΪ�¿�Ŀ
        scores.push_back(StacticScore(name, GPA, grade, credit, dir));
    }
}

void GradeSystem::sortScores() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "��������������������  ��          ѧ�Ƴɼ���ѯ          ��  ��������������������" << std::endl;
    std::cout << "��������������������         ��������         �������������������" << std::endl;
    std::cout << "��������������������  ��         1.��ѯѧ������         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         2.��ѯ��Ŀ�ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         0.����                ��  �������������������" << std::endl;
    char move;
    while (std::cin >> move) {
        switch (move - '0') {
            case 0:
                introduction();
                return;
            case 1:
                studentRank();
                return;
            case 2:
                subjectInfo();
                return;
            default:
                std::cout << " �������ָ����ڣ�" << std::endl;
                std::cout << "��������������������  ��         1.��ѯ��Ŀ�ɼ�         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         2.��ѯ��Ŀ����         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         0.����                ��  �������������������" << std::endl;
        }
    }
}

void GradeSystem::studentRank() {
    if (students.empty()) {
        std::cout << "����Ϊ�գ�����¼��ѧ����Ϣ" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "������ϣ���鿴�����Ŀ�Ŀ����(�����ѯ������������\"�ܳɼ�\", ���ռ�Ȩ�������� " << std::endl;
    std::string name;
    std::cin >> name;
    if (name == "�ܳɼ�") {
        std::vector<Profile> a = students;
        sort(a.begin(), a.end(), compareGrade);
        std::cout << "����    " << "ѧ��    " << "��Ȩ    " << "����" << std::endl;
        for (int i = 0; i < a.size(); i++) {
            std::cout << i + 1 << ". " << a[i].name << "  " << a[i].id << "  " << a[i].getGrade() << "  "
                      << a[i].getGPA() << std::endl;
        }
        exit2Menu();
        return;
    }
    int i, dir = 0;
    for (i = 0; i < scores.size(); i++) {
        if (scores[i].name == name) {
            dir = scores[i].dir;
            break;
        }
    }
    if (i == scores.size()) {
        std::cout << "�ÿ�Ŀ�����ڣ�" << std::endl;
        std::cout << "���������ַ�����..." << std::endl;
        std::string move;
        std::cin >> move;
        sortScores();
        return;
    }
    std::vector<GradeBean> a;
    for (int j = 0; j < students.size(); j++) {
        GradeBean m = students[j].getSubjectDetail(name, dir);
        if (m.name != "")
            a.push_back(m);
    }           // Ѱ������ӵ�д˿γ̵�ѧ��������¼�γ���Ϣ

    sort(a.begin(), a.end(), compareGrade2);  // ����
    std::cout << "����    " << "ѧ��    " << "��Ȩ    " << "����" << std::endl;
    for (int i = 0; i < a.size(); i++) {
        std::cout << i + 1 << ". " << a[i].name << "  " << a[i].id << "  " << a[i].grade << "  "
                  << a[i].GPA << std::endl;
    }

    exit2Menu();
}

void GradeSystem::subjectInfo() {
    if (students.empty()) {
        std::cout << "����Ϊ�գ�����¼��ѧ����Ϣ" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "��������Ҫ��ѯ�Ŀ�Ŀ����(�����ѯ����������\"�ܳɼ�\"���� " << std::endl;
    std::string name;
    std::cin >> name;
    StacticScore a;
    if (name == "�ܳɼ�") {
        std::vector<Subject> sub;
        double GPA = 0, grade = 0, credit = 0;
        for (int i = 0; i < scores.size(); i++) {
            a = scores[i];
            credit += a.credit;
            GPA += a.GPA * a.credit;
            grade += a.grade * a.credit;
            std::string type = (a.dir) ? "����" : "ѡ��";
            std::cout << "��Ŀ���ƣ� " << a.name << "    ��Ŀѧ�֣� " << a.credit << "    ��Ŀ���ͣ� " << type << std::endl;
            std::cout << "�꼶ƽ��GPA�� " << a.GPA << "      �꼶ƽ���ɼ��� " << a.grade << std::endl;
        }
        std::cout << std::endl << "�꼶ƽ����GPA�� " << GPA / credit << "      �꼶ƽ���ܳɼ��� " << grade / credit << std::endl;
        exit2Menu();
        return;
    }
    int i;
    for (i = 0; i < scores.size(); i++) {
        if (scores[i].name == name) {
            a = scores[i];
            break;
        }           //  ��ȡ��Ŀ�ɼ���Ϣ
    }
    if (i == scores.size()) {
        std::cout << "�ÿ�Ŀ�����ڣ�" << std::endl;
        std::cout << "���������ַ�����..." << std::endl;
        std::string move;
        std::cin >> move;
        sortScores();
        return;
    }
    std::string type = (a.dir) ? "����" : "ѡ��";
    std::cout << "��Ŀ���ƣ� " << a.name << "    ��Ŀѧ�֣� " << a.credit << "    ��Ŀ���ͣ� " << type << std::endl;
    std::cout << "�꼶ƽ��GPA�� " << a.GPA << "      �꼶ƽ���ɼ��� " << a.grade << std::endl;
    std::cout << "������������ѧ����Ϣ��������" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::vector<Subject> sub;
        if (a.dir == 1)
            students[i].getCommonSubjects(sub);
        else
            students[i].getElectiveSubjects(sub);
        for (int j = 0; j < sub.size(); j++) {
            if (sub[j].name == a.name) {
                std::cout << "ѧ�������� " << students[i].name << " ѧ�ţ� " << students[i].id << std::endl;
                std::cout << "���㣺 " << sub[j].getGPA() << "" << "     �ɼ���" << sub[j].getGrade() << std::endl
                          << std::endl;
                break;
            }
        }
    }
    exit2Menu();
}

void GradeSystem::exit2Menu() {
    std::cout << "���������ַ�����..." << std::endl;
    std::string move;
    std::cin >> move;
    introduction();
}

void GradeSystem::readFromLocal() {
    char buff[1000];
    _getcwd(buff, 1000);
    strcat(buff, "\\local_save.txt");   // ���ر����ļ�
    std::ifstream in;
    in.open(buff, std::ios::in);
    int t;
    in >> t;
    for (int j = 0; j < t; j++) {
        std::string name, id, sub;
        int num;
        in >> name >> id >> num;
        students.push_back(Profile(name, id));
        Profile &a = students.back();
        for (int i = 0; i < num; i++) {
            double credit;
            int grade, dir;
            in >> sub >> credit >> grade >> dir;
            Subject subject(sub, credit, grade, dir);
            addScore(sub, subject.getGPA(), grade, credit, dir);        // ��ϵͳ�м����¿�Ŀ

            double c, g, G, sum_g, sum_G;
            int r;
            students.back().getAll(G, g, c, r);
            sum_g = g * c;
            sum_G = G * c;
            c += credit;
            g = (sum_g + grade * credit) / c;
            G = (sum_G + subject.getGPA() * credit) / c;
            students.back().setAll(G, g, c, r);                         // ʵʱͳ�ƴ�ѧ���ɼ�

            if (subject.dir == 1) {
                a.addCommonSubject(subject);
                a.num_com++;
            } else {
                a.addElectiveSubject(subject);
                a.num_elec++;
            }
        }
    }
    in.close();
    std::cout << "�������ݼ�¼���سɹ�..." << std::endl;
}


