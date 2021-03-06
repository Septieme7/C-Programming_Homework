//
// Created by Septieme on 2019/7/26.
//
/**
 * 用户界面不作为评分项（用Dos界面即可），评分项包括代码风格、注释完整性、功能完整性、文档完整性。
   基于面向对象设计并实现学生成绩管理系统，用于统计单科成绩、加权分计算、年级排名等。
    设计发散功能可作为加分项。
 */
#include "bits/stdc++.h"
#include "GradeSystem.h"

using namespace std;

int main() {
    char move;  // 增强代码健壮性
    GradeSystem gradeSystem;     // 实例化一个成绩管理系统

    gradeSystem.readFromLocal(); // 从本地加载保存的数据

    gradeSystem.introduction();   // 系统功能菜单

    while (cin >> move) {
        switch (move - '0') {
            case 0:
                gradeSystem.safeExit();
                return 0;
                break;
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
                gradeSystem.deleteScores();
                break;
            case 5:
                gradeSystem.fixScores();
                break;
            case 6:
                gradeSystem.displayAll();
                break;
            default:
                cout << "不存在此操作!" << endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.增加学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.查询学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         3.排序统计成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         4.删除学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         5.修改学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         6.查看成绩总览         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.安全退出系统         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "Tip: 建议您使用安全退出，强行关闭程序可能会导致数据丢失。" << std::endl;
                continue;
        }
    }
    return 0;
}