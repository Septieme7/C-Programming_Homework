//
// Created by Septieme on 2019/7/29.
//

#include "GradeSystem.h"
#include "iostream"

void GradeSystem::introduction() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "��������������������  ��   ѧ �� �� �� �� �� ϵ  ͳ     ��  ��������������������" << std::endl;
    std::cout << "��������������������         ��������         �������������������" << std::endl;
    std::cout << "��������������������  ��         1.����ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         2.��ʾѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         3.����ͳ�Ƴɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         4.����ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         5.ɾ��ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         6.�޸�ѧ���ɼ�         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         7.�鿴�ɼ�����         ��  �������������������" << std::endl;
    std::cout << "��������������������  ��         0.��ȫ�˳�ϵͳ         ��  �������������������" << std::endl;
}

void GradeSystem::searchById() {

}

void GradeSystem::searchByName() {

}

void GradeSystem::addInformationByFile() {

}

void GradeSystem::addInformationByTap() {
    std::cout << "" << std::endl;
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
