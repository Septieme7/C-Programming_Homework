//
// Created by Septieme on 2019/7/26.
//
/**
 * �û����治��Ϊ�������Dos���漴�ɣ������������������ע�������ԡ����������ԡ��ĵ������ԡ�
   �������������Ʋ�ʵ��ѧ���ɼ�����ϵͳ������ͳ�Ƶ��Ƴɼ�����Ȩ�ּ��㡢�꼶�����ȡ�
    ��Ʒ�ɢ���ܿ���Ϊ�ӷ��
 */
#include "bits/stdc++.h"
#include "GradeSystem.h"

using namespace std;

int main() {
    char move;  // ��ǿ���뽡׳��
    GradeSystem gradeSystem;     // ʵ����һ���ɼ�����ϵͳ

    gradeSystem.readFromLocal(); // �ӱ��ؼ��ر��������

    gradeSystem.introduction();   // ϵͳ���ܲ˵�

    while (cin >> move) {
        switch (move - '0') {
            case 0:
                return 0;
            case 1:
                gradeSystem.addStudent();
                break;
            case 2:
                gradeSystem.searchStudent();
                break;
            case 3:
                gradeSystem.sortScores();
                break;
            case 4:
                break;
            default:
                cout << "�����ڴ˲���!" << endl;
                std::cout << "��������������������  ��         1.����ѧ���ɼ�         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         2.��ѯѧ���ɼ�         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         3.����ͳ�Ƴɼ�         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         4.ɾ��ѧ���ɼ�         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         5.�޸�ѧ���ɼ�         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         6.�鿴�ɼ�����         ��  �������������������" << std::endl;
                std::cout << "��������������������  ��         0.��ȫ�˳�ϵͳ         ��  �������������������" << std::endl;
                continue;
        }
    }
    return 0;
}