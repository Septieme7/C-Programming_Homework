//
// Created by Septieme on 2019/7/29.
//

#include <libloaderapi.h>
#include <io.h>
#include "GradeSystem.h"
#include "iostream"
#include "fstream"
#include "iomanip"


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
        std::cout << "���������ַ�����..." << std::endl;
        std::string move;
        std::cin >> move;
        introduction();
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
    std::cout << " ƽ����Ȩ��" << s.getGrade() << "  ��ѧ������" << s.getCredit() << std::endl;
    std::cout << "���������ַ�����..." << std::endl;
    std::string move;
    std::cin >> move;
    introduction();
}

void GradeSystem::searchByName() {

}

void GradeSystem::addInformationByFile() {
    char buff[1000];
    _getcwd(buff, 1000);
    std::cout << "���ڵ�ǰ��ʾ��Ŀ¼�ڽ���һ����Ϊ\"scores.txt\" ���ı��ĵ�(����ʹ��GBK���룬UTF-8���ܻᵼ�³�������)��������ָ����ʽ����ɼ�" << std::endl;
    std::cout << "����Ҫ��: ��һ��Ϊ�����ѧ������, �ӵڶ��п�ʼΪÿλѧ����������ѧ�źͿ�Ŀ����n" << std::endl;
    std::cout << buff << std::endl;
    std::cout << "����n�����գ���Ŀ  ��Ŀѧ��  �ɼ�  �γ����ͣ�1���� 0ѡ�ޣ��ĸ�ʽ����ɼ�" << std::endl;
    std::cout << "�ĵ��༭��Ϻ����������ַ���ʼ¼��" << std::endl;
    std::string move;
    std::cin >> move;
    strcat(buff, "\\scores.txt");// �ڵ�ǰ·���������·��
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
            double c, g, G, sum_g, sum_G;
            int r;
            students.back().getAll(G, g, c, r);
            sum_g = g * c;
            sum_G = G * c;
            c += credit;
            g = (sum_g + grade * credit) / c;
            G = (sum_G + subject.getGPA() * credit) / c;
            students.back().setAll(G, g, c, r);
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
    std::cout << "���������ַ�����..." << std::endl;
    std::string mo;
    std::cin >> mo;
    introduction();
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
        double c, g, G, sum_g, sum_G;
        int r;
        students.back().getAll(G, g, c, r);
        sum_g = g * c;
        sum_G = G * c;
        c += credit;
        g = (sum_g + grade * credit) / c;
        G = (sum_G + subject.getGPA() * credit) / c;
        students.back().setAll(G, g, c, r);
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
    std::cout << "���������ַ�����..." << std::endl;
    std::string move;
    std::cin >> move;
    introduction();
}

void GradeSystem::accountScore(std::string name) {

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
