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
    char move;  // ��ǿ��׳��
    GradeSystem gradeSystem;     // ʵ����һ���ɼ�����ϵͳ
    gradeSystem.introduction();
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

        }
    }
    return 0;
}