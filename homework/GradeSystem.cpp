//
// Created by Septieme on 2019/7/29.
//

#include <io.h>
#include "GradeSystem.h"
#include "iostream"
#include "iomanip"

// 两个用于成绩比较排序的函数
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

int sortById(Profile a, Profile b) {
    return a.id < b.id;
}

void GradeSystem::introduction() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓〓  ☆   学 生 成 绩 管 理 系  统     ☆  〓〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓★★★★★         ★★★★★★★         ★★★★★〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.增加学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.查询学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         3.排序统计成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         4.删除学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         5.修改学生成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         6.查看成绩总览         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.安全退出系统         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "Tip: 建议您使用安全退出，强行关闭程序可能会导致数据丢失。" << std::endl;
}

// 通过学生学号查询
void GradeSystem::searchById() {
    std::cout << "请输入需要查询的学生的学号：" << std::endl;
    std::string id;
    std::cin >> id;
    showStudentDetailbyId(id);
    exit2Menu();
}

// 通过学生姓名查询
void GradeSystem::searchByName() {
    std::cout << "请输入需要查询的学生的姓名：" << std::endl;
    std::string name;
    std::cin >> name;
    showStudentDetailbyName(name);
    exit2Menu();
}

void GradeSystem::addInformationByFile() {
    char buff[1000];
    _getcwd(buff, 1000);        // 获取当前生成的exe程序的绝对路径
    std::cout << "请在当前提示的目录内建立一个名为\"scores.txt\" 的文本文档(建议使用GBK编码，UTF-8可能会导致出现乱码)，并按照指定格式输入成绩" << std::endl;
    std::cout << "输入要求: 第一行为输入的学生数量, 从第二行开始为每位学生的姓名、学号和科目数量n" << std::endl;
    std::cout << buff << std::endl;
    std::cout << "以下n行依照：科目  科目学分  成绩  课程类型（1必修 0选修）的格式输入成绩" << std::endl;
    std::cout << "文档编辑完毕后输入任意字符开始录入" << std::endl;
    std::string move;
    std::cin >> move;
    strcat(buff, "\\scores.txt");   // 在当前路径后添加子路径
    std::ifstream in;
    in.open(buff, std::ios::in);
    int t;
    in >> t;
    for (int j = 0; j < t; j++) {
        std::string name, id, sub;
        int num;
        in >> name >> id >> num;
        int k;
        for (k = 0; k < students.size(); k++) {
            if (students[k].id == id && students[k].name == name)
                break;
        }
        if (k == students.size()) {
            students.push_back(Profile(name, id));
            Profile &a = students.back();
            for (int i = 0; i < num; i++) {
                double credit;
                int grade, dir;
                in >> sub >> credit >> grade >> dir;
                try {
                    if (in.fail())
                        throw 1;
                }                   // 异常处理 防止出现输入格式错误导致程序崩溃
                catch (int) {
                    in.clear();
                    in.sync();
                    std::cout << "学生 " << a.name << " 的" << "科目 " << sub << " 输入格式出现了错误，读取过程结束" << std::endl;
                    std::cout << " 在此学生以前的学生成绩均已成功登记，请修正输入文件格式后再登记其余同学的成绩" << std::endl;
                    students.pop_back();   // 输入错误的学生信息将被删除
                    return;
                }
                Subject subject(sub, credit, grade, dir);
                addScore(sub, subject.getGPA(), grade, credit, dir);        // 在系统中加入新科目

                double c, g, G, sum_g, sum_G;
                int r;
                students.back().getAll(G, g, c, r);
                sum_g = g * c;
                sum_G = G * c;
                c += credit;
                g = (sum_g + grade * credit) / c;
                G = (sum_G + subject.getGPA() * credit) / c;
                students.back().setAll(G, g, c, r);                         // 实时统计此学生成绩

                if (subject.dir == 1) {
                    a.addCommonSubject(subject);
                    a.num_com++;
                } else {
                    a.addElectiveSubject(subject);
                    a.num_elec++;
                }
            }
            std::cout << "您本次为学生 " << a.name << " 登记了 " << a.num_com << " 门必修课成绩和 " << a.num_elec << " 门选修课成绩"
                      << std::endl;
        } else {                // 此学生已在系统内
            Profile &a = students[k];
            for (int i = 0; i < num; i++) {
                double credit;
                int grade, dir;
                in >> sub >> credit >> grade >> dir;
                try {
                    if (in.fail())
                        throw 1;
                }                   // 异常处理 防止出现输入格式错误导致程序崩溃
                catch (int) {
                    in.clear();
                    in.sync();
                    std::cout << "学生 " << a.name << " 的" << "科目 " << sub << " 输入格式出现了错误，读取过程结束" << std::endl;
                    std::cout << " 在此学生以前的学生成绩均已成功登记，请修正输入文件格式后再登记其余同学的成绩" << std::endl;
                    return;
                }
                Subject subject(sub, credit, grade, dir);
                int l;
                std::vector<Subject> ss;
                if (dir == 1) {
                    students[k].getCommonSubjects(ss);
                } else {
                    students[k].getElectiveSubjects(ss);
                }
                for (l = 0; l < ss.size(); l++) {
                    if (ss[l].name == subject.getName()) {
                        break;
                    }
                }
                if (l == ss.size()) {
                    addScore(sub, subject.getGPA(), grade, credit, dir);        // 该学生未登记过此成绩
                    double c, g, G, sum_g, sum_G;
                    int r;
                    students[k].getAll(G, g, c, r);
                    sum_g = g * c;
                    sum_G = G * c;
                    c += credit;
                    g = (sum_g + grade * credit) / c;
                    G = (sum_G + subject.getGPA() * credit) / c;
                    students[k].setAll(G, g, c, r);                         // 实时统计此学生成绩

                    if (subject.dir == 1) {
                        a.addCommonSubject(subject);
                        a.num_com++;
                    } else {
                        a.addElectiveSubject(subject);
                        a.num_elec++;
                    }
                } else {
                    GradeBean gra = students[k].fixCourse(subject.getName(), subject.dir, subject.getGrade());
                    for (int v = 0; v < scores.size(); v++) {
                        if (scores[v].name == subject.getName()) {
                            int grade = gra.grade;
                            double GPA = gra.GPA, t_g, t_G;
                            if (scores[v].studentNum == 1) {
                                scores.erase(scores.begin() + v);
                                break;
                            }
                            t_g = scores[v].grade * scores[v].studentNum;
                            t_G = scores[v].GPA * scores[v].studentNum;
                            scores[v].grade = (t_g - grade) / scores[v].studentNum;
                            scores[v].GPA = (t_G - GPA) / scores[v].studentNum;
                            break;
                        }
                    }
                }
            }

        }

    }
    in.close();
    exit2Menu();
}

void GradeSystem::addInformationByTap() {
    std::string name, id;
    char flag;
    std::cout << "请输入该学生的姓名：" << std::endl;
    std::cin >> name;
    std::cout << "请输入该学生的学号：" << std::endl;
    std::cin >> id;
    std::cout << "您输入的学生信息为: 姓名: " << name << " 学号： " << id << std::endl;
    std::cout << "正确请输入 1 ， 有误请输入 2 并重新输入，返回请输入 0" << std::endl;
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
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].name == name && students[i].id == id) {
            break;
        }
    }
    if (i == students.size()) {
        students.push_back(Profile(name, id));
        std::cout << "请按照如下格式输入该学生的成绩：" << std::endl;
        std::string sub;
        int grade, dir;
        double credit;
        std::cout << "科目  科目学分  成绩  课程类型（1必修 0选修）(四个项目均为0则代表结束）" << std::endl;
        while (1) {
            std::cin >> sub >> credit >> grade >> dir;
            try {
                if (std::cin.fail())
                    throw 1;
            }                   // 异常处理 防止出现输入格式错误导致程序崩溃
            catch (int) {
                std::cin.clear();
                std::cin.sync();
                std::cout << "输入格式出现了错误, 请从科目名称开始重新输入当前科目：" << std::endl;
                continue;
            }
            if (sub == "0" && grade == 0 && credit == 0 && dir == 0)
                break;
            Subject subject(sub, credit, grade, dir);
            addScore(sub, subject.getGPA(), grade, credit, dir);        // 在系统中加入新科目

            double c, g, G, sum_g, sum_G;
            int r;
            students.back().getAll(G, g, c, r);
            sum_g = g * c;
            sum_G = G * c;
            c += credit;
            g = (sum_g + grade * credit) / c;
            G = (sum_G + subject.getGPA() * credit) / c;
            students.back().setAll(G, g, c, r);                         // 实时统计此学生成绩

            if (subject.dir == 1) {
                students.back().addCommonSubject(subject);
                students.back().num_com++;
            } else {
                students.back().addElectiveSubject(subject);
                students.back().num_elec++;
            }
        }
        Profile a = students.back();
        std::cout << "您本次为学生 " << a.name << " 登记了 " << a.num_com << " 门必修课成绩和 " << a.num_elec << " 门选修课成绩" << std::endl;
    } else {
        std::cout << "请按照如下格式输入该学生的成绩：" << std::endl;
        std::string sub;
        int grade, dir;
        double credit;
        std::cout << "科目  科目学分  成绩  课程类型（1必修 0选修）(四个项目均为0则代表结束）" << std::endl;
        while (1) {
            std::cin >> sub >> credit >> grade >> dir;
            try {
                if (std::cin.fail())
                    throw 1;
            }                   // 异常处理 防止出现输入格式错误导致程序崩溃
            catch (int) {
                std::cin.clear();
                std::cin.sync();
                std::cout << "输入格式出现了错误, 请从科目名称开始重新输入当前科目：" << std::endl;
                continue;
            }
            if (sub == "0" && grade == 0 && credit == 0 && dir == 0)
                break;
            Subject subject(sub, credit, grade, dir);
            int l;
            std::vector<Subject> ss;
            if (dir == 1) {
                students[i].getCommonSubjects(ss);
            } else {
                students[i].getElectiveSubjects(ss);
            }
            for (l = 0; l < ss.size(); l++) {
                if (ss[l].name == subject.getName()) {
                    break;
                }
            }
            if (l == ss.size()) {
                addScore(sub, subject.getGPA(), grade, credit, dir);        // 在系统中加入新科目
                double c, g, G, sum_g, sum_G;
                int r;
                students[i].getAll(G, g, c, r);
                sum_g = g * c;
                sum_G = G * c;
                c += credit;
                g = (sum_g + grade * credit) / c;
                G = (sum_G + subject.getGPA() * credit) / c;
                students[i].setAll(G, g, c, r);                         // 实时统计此学生成绩

                if (subject.dir == 1) {
                    students[i].addCommonSubject(subject);
                    students[i].num_com++;
                } else {
                    students[i].addElectiveSubject(subject);
                    students[i].num_elec++;
                }
            } else {
                GradeBean gra = students[i].fixCourse(subject.getName(), subject.dir, subject.getGrade());
                for (int v = 0; v < scores.size(); v++) {
                    if (scores[v].name == subject.getName()) {
                        int grade = gra.grade;
                        double GPA = gra.GPA, t_g, t_G;
                        if (scores[v].studentNum == 1) {
                            scores.erase(scores.begin() + v);
                            break;
                        }
                        t_g = scores[v].grade * scores[v].studentNum;
                        t_G = scores[v].GPA * scores[v].studentNum;
                        scores[v].grade = (t_g - grade) / scores[v].studentNum;
                        scores[v].GPA = (t_G - GPA) / scores[v].studentNum;
                        break;
                    }
                }

            }
        }

    }
    exit2Menu();
}

void GradeSystem::addStudent() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓〓  ☆          学生信息录入          ☆  〓〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓★★★★★         ★★★★★★★         ★★★★★〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.通过输入增加(单人)   ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.通过文件增加(大量)   ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.返回                ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
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
                std::cout << " 您输入的指令不存在！" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.通过输入增加(少量)   ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.通过文件增加(大量)   ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.返回                ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
        }
    }

}

void GradeSystem::searchStudent() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓〓  ☆          学生成绩查询          ☆  〓〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓★★★★★         ★★★★★★★         ★★★★★〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.通过姓名查询         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.通过学号查询         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.返回                ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    char move;
    while (std::cin >> move) {
        switch (move - '0') {
            case 0:
                introduction();
                return;
                break;
            case 1:
                searchByName();
                return;
                break;
            case 2:
                searchById();
                return;
                break;
            default:
                std::cout << " 您输入的指令不存在！" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.通过姓名查询         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.通过学号查询         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.返回                ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
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
    if (i == scores.size()) {    // 此科目为新科目
        scores.push_back(StacticScore(name, GPA, grade, credit, dir));
    }
}

void GradeSystem::sortScores() {
    std::cout << "***************************************************************************" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓〓  ☆          学科成绩查询          ☆  〓〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓★★★★★         ★★★★★★★         ★★★★★〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.查询学生排名         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.查询科目成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
    std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.返回                ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
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
                std::cout << " 您输入的指令不存在！" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         1.查询科目成绩         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         2.查询科目排名         ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
                std::cout << "〓〓〓〓〓〓〓〓〓★  ☆         0.返回                ☆  ★〓〓〓〓〓〓〓〓〓" << std::endl;
        }
    }
}

void GradeSystem::studentRank() {
    if (students.empty()) {
        std::cout << "数据为空！请先录入学生信息" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "请输入希望查看排名的科目名称(如想查询总排名请输入\"总成绩\", 按照加权排名）： " << std::endl;
    std::string name;
    std::cin >> name;
    if (name == "总成绩") {
        std::vector<Profile> a = students;
        sort(a.begin(), a.end(), compareGrade);
        std::cout << "姓名    " << "学号    " << "加权    " << "绩点" << std::endl;
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
        std::cout << "该科目不存在！" << std::endl;
        std::cout << "输入任意字符返回..." << std::endl;
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
    }           // 寻找所有拥有此课程的学生，并记录课程信息

    sort(a.begin(), a.end(), compareGrade2);  // 排序
    std::cout << "姓名    " << "学号    " << "加权    " << "绩点" << std::endl;
    for (int i = 0; i < a.size(); i++) {
        std::cout << i + 1 << ". " << a[i].name << "  " << a[i].id << "  " << a[i].grade << "  "
                  << a[i].GPA << std::endl;
    }

    exit2Menu();
}

void GradeSystem::subjectInfo() {
    if (students.empty()) {
        std::cout << "数据为空！请先录入学生信息" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "请输入想要查询的科目名称(如想查询总览请输入\"总成绩\"）： " << std::endl;
    std::string name;
    std::cin >> name;
    StacticScore a;
    if (name == "总成绩") {
        std::vector<Subject> sub;
        double GPA = 0, grade = 0, credit = 0;
        for (int i = 0; i < scores.size(); i++) {
            a = scores[i];
            credit += a.credit;
            GPA += a.GPA * a.credit;
            grade += a.grade * a.credit;
            std::string type = (a.dir) ? "必修" : "选修";
            std::cout << "科目名称： " << a.name << "    科目学分： " << a.credit << "    科目类型： " << type << std::endl;
            std::cout << "年级平均GPA： " << a.GPA << "      年级平均成绩： " << a.grade << std::endl;
        }
        std::cout << std::endl << "年级平均总GPA： " << GPA / credit << "      年级平均总成绩： " << grade / credit << std::endl;
        exit2Menu();
        return;
    }
    int i;
    for (i = 0; i < scores.size(); i++) {
        if (scores[i].name == name) {
            a = scores[i];
            break;
        }           //  获取科目成绩信息
    }
    if (i == scores.size()) {
        std::cout << "该科目不存在！" << std::endl;
        std::cout << "输入任意字符返回..." << std::endl;
        std::string move;
        std::cin >> move;
        sortScores();
        return;
    }
    std::string type = (a.dir) ? "必修" : "选修";
    std::cout << "科目名称： " << a.name << "    科目学分： " << a.credit << "    科目类型： " << type << std::endl;
    std::cout << "年级平均GPA： " << a.GPA << "      年级平均成绩： " << a.grade << std::endl;
    std::cout << "————具体学生信息————" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::vector<Subject> sub;
        if (a.dir == 1)
            students[i].getCommonSubjects(sub);
        else
            students[i].getElectiveSubjects(sub);
        for (int j = 0; j < sub.size(); j++) {
            if (sub[j].name == a.name) {
                std::cout << "学生姓名： " << students[i].name << " 学号： " << students[i].id << std::endl;
                std::cout << "绩点： " << sub[j].getGPA() << "" << "     成绩：" << sub[j].getGrade() << std::endl
                          << std::endl;
                break;
            }
        }
    }
    exit2Menu();
}

void GradeSystem::exit2Menu() {
    std::cout << "输入任意字符返回..." << std::endl;
    std::string move;
    std::cin >> move;
    introduction();
}

void GradeSystem::readFromLocal() {
    char buff[1000];
    _getcwd(buff, 1000);
    strcat(buff, "\\local_save.txt");   // 本地保存文件
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
            addScore(sub, subject.getGPA(), grade, credit, dir);        // 在系统中加入新科目

            double c, g, G, sum_g, sum_G;
            int r;
            students.back().getAll(G, g, c, r);
            sum_g = g * c;
            sum_G = G * c;
            c += credit;
            g = (sum_g + grade * credit) / c;
            G = (sum_G + subject.getGPA() * credit) / c;
            students.back().setAll(G, g, c, r);                         // 实时统计此学生成绩

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
    std::cout << "本地数据记录加载成功..." << std::endl;
}

void GradeSystem::deleteScores() {
    std::cout << "请输入您想要删除成绩的学生的学号：" << std::endl;
    std::string id;
    std::cin >> id;
    Profile s;
    std::vector<Subject> all;
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            std::cout << "学生姓名： " << students[i].name << " 学号： " << students[i].id << std::endl;
            s = students[i];
            students[i].getCommonSubjects(all);
            students[i].getElectiveSubjects(all);
            break;
        }           //  获取学生成绩信息
    }
    if (i == students.size()) {
        std::cout << "该生不存在！" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "科目     学分     成绩     绩点     课程类型" << std::endl;
    for (int j = 0; j < all.size(); j++) {
        Subject subject = all[j];
        std::cout << subject.name << "  " << subject.getCredit() << "  " << subject.getGrade() << "  "
                  << subject.getGPA() << "  ";
        if (subject.dir == 1)
            std::cout << "必修" << std::endl;
        else
            std::cout << "选修" << std::endl;
    }
    std::cout << std::setprecision(4) << "平均GPA：" << s.getGPA();
    std::cout << "  平均加权：" << s.getGrade() << "    总学分数：" << s.getCredit() << std::endl << std::endl;
    std::cout << "请输入您想要删除的科目, 输入0代表结束：" << std::endl;
    while (1) {
        int d, k;
        double c;
        if (students[i].num_elec == 0 && students[i].num_com == 0) {
            std::cout << "不存在任何课程成绩！" << std::endl;
            break;
        }
        std::string move;
        std::cin >> move;
        if (move == "0")
            break;
        for (k = 0; k < all.size(); k++) {
            if (all[k].name == move) {
                d = all[k].dir;
                c = all[k].getCredit();
                break;
            }
        }
        if (k == all.size()) {
            std::cout << "课程不存在！" << std::endl;
            continue;
        }
        GradeBean gra = students[i].deleteCourse(move, d);
        for (int v = 0; v < scores.size(); v++) {
            if (scores[v].name == move) {
                int grade = gra.grade;
                double GPA = gra.GPA, t_g, t_G;
                if (scores[v].studentNum == 1) {
                    scores.erase(scores.begin() + v);
                    break;
                }
                t_g = scores[v].grade * scores[v].studentNum;
                t_G = scores[v].GPA * scores[v].studentNum;
                scores[v].studentNum--;
                scores[v].grade = (t_g - grade) / scores[v].studentNum;
                scores[v].GPA = (t_G - GPA) / scores[v].studentNum;
                break;
            }
        }
        std::cout << "课程 " << move << " 成绩已被成功删除！" << std::endl;
    }
    exit2Menu();

}

void GradeSystem::fixScores() {
    std::cout << "请输入您想要修改成绩的学生的学号：" << std::endl;
    std::string id;
    std::cin >> id;
    Profile s;
    std::vector<Subject> all;
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            std::cout << "学生姓名： " << students[i].name << " 学号： " << students[i].id << std::endl;
            s = students[i];
            students[i].getCommonSubjects(all);
            students[i].getElectiveSubjects(all);
            break;
        }           //  获取学生成绩信息
    }
    if (i == students.size()) {
        std::cout << "该生不存在！" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "科目     学分     成绩     绩点     课程类型" << std::endl;
    for (int j = 0; j < all.size(); j++) {
        Subject subject = all[j];
        std::cout << subject.name << "  " << subject.getCredit() << "  " << subject.getGrade() << "  "
                  << subject.getGPA() << "  ";
        if (subject.dir == 1)
            std::cout << "必修" << std::endl;
        else
            std::cout << "选修" << std::endl;
    }
    std::cout << std::setprecision(4) << "平均GPA：" << s.getGPA();
    std::cout << "  平均加权：" << s.getGrade() << "    总学分数：" << s.getCredit() << std::endl << std::endl;
    std::cout << "请输入您想要修改的科目, 输入0代表结束：" << std::endl;
    while (1) {
        int d, k, value;
        double c;
        std::string move;
        std::cin >> move;
        if (move == "0")
            break;
        for (k = 0; k < all.size(); k++) {
            if (all[k].name == move) {
                d = all[k].dir;
                c = all[k].getCredit();
                std::cout << "请输入修改后的成绩：" << std::endl;
                std::cin >> value;
                break;
            }
        }
        if (k == all.size()) {
            std::cout << "课程不存在！" << std::endl;
            continue;
        }
        GradeBean gra = students[i].fixCourse(move, d, value);
        for (int v = 0; v < scores.size(); v++) {
            if (scores[v].name == move) {
                int grade = gra.grade;
                double GPA = gra.GPA, t_g, t_G;
                t_g = scores[v].grade * scores[v].studentNum;
                t_G = scores[v].GPA * scores[v].studentNum;
                scores[v].grade = (t_g - grade) / scores[v].studentNum;
                scores[v].GPA = (t_G - GPA) / scores[v].studentNum;
                break;
            }
        }
        std::cout << "课程 " << move << " 成绩已被成功修改为：" << value << std::endl;
    }
    exit2Menu();
}

void GradeSystem::displayAll() {
    sort(students.begin(), students.end(), sortById);
    std::cout << "——————学生成绩统计——————" << std::endl;
    for (int i = 0; i < students.size(); i++) {
        showStudentDetailbyId(students[i].id);
        std::cout << std::endl;
    }
    StacticScore a;
    std::vector<Subject> sub;
    double GPA = 0, grade = 0, credit = 0;
    std::cout << "——————科目成绩统计——————" << std::endl;
    for (int i = 0; i < scores.size(); i++) {
        a = scores[i];
        credit += a.credit;
        GPA += a.GPA * a.credit;
        grade += a.grade * a.credit;
        std::string type = (a.dir) ? "必修" : "选修";
        std::cout << "科目名称： " << a.name << "    科目学分： " << a.credit << "    科目类型： " << type << std::endl;
        std::cout << "年级平均GPA： " << a.GPA << "      年级平均成绩： " << a.grade << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl << "年级平均总GPA： " << GPA / credit << "      年级平均总成绩： " << grade / credit << std::endl;
    exit2Menu();

}

void GradeSystem::safeExit() {
    std::cout << "正在保存学生信息到本地....." << std::endl;
    char buff[1000];
    _getcwd(buff, 1000);        // 获取当前生成的exe程序的绝对路径
    strcat(buff, "\\local_save.txt");
    bool flag = remove(buff);  // remove()函数返回值为0或EPF(-1)
    if (flag == 0)
        std::cout << "过期存档删除成功！" << std::endl;
    else {
        std::cout << "不存在存档..." << std::endl;
    }
    std::ofstream OutFile(buff);
    OutFile << students.size() << std::endl;
    for (int i = 0; i < students.size(); i++) {
        std::vector<Subject> all;
        OutFile << students[i].name << " " << students[i].id << " " << students[i].num_elec + students[i].num_com
                << std::endl;
        students[i].getCommonSubjects(all);
        students[i].getElectiveSubjects(all);
        for (int j = 0; j < all.size(); j++) {
            Subject subject = all[j];
            OutFile << subject.name << "   " << subject.getCredit() << "   " << subject.getGrade() << "  "
                    << subject.dir << std::endl;
        }
        OutFile << std::endl;
    }
    std::cout << "新存档保存成功，已安全退出..." << std::endl;
    OutFile.close();

}

void GradeSystem::showStudentDetailbyId(std::string id) {
    Profile s;
    std::vector<Subject> all;
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            std::cout << "学生姓名： " << students[i].name << " 学号： " << students[i].id << std::endl;
            s = students[i];
            students[i].getCommonSubjects(all);
            students[i].getElectiveSubjects(all);
            break;
        }           //  获取学生成绩信息
    }
    if (i == students.size()) {
        std::cout << "该生不存在！" << std::endl;
        exit2Menu();
        return;
    }
    std::cout << "科目     学分     成绩     绩点     课程类型" << std::endl;
    for (int j = 0; j < all.size(); j++) {
        Subject subject = all[j];
        std::cout << subject.name << "  " << subject.getCredit() << "  " << subject.getGrade() << "  "
                  << subject.getGPA() << "  ";
        if (subject.dir == 1)
            std::cout << "必修" << std::endl;
        else
            std::cout << "选修" << std::endl;
    }
    std::cout << std::setprecision(4) << "平均GPA：" << s.getGPA();
    std::cout << "  平均加权：" << s.getGrade() << "    总学分数：" << s.getCredit() << std::endl;
}

void GradeSystem::showStudentDetailbyName(std::string name) {
    Profile s;
    bool flag = 0;
    int i;
    for (i = 0; i < students.size(); i++) {
        if (students[i].name == name) {// 因为可能存在同名情况，所以找到便输出
            flag = 1;   // 标记是否有找到
            std::vector<Subject> all;
            std::cout << "学生姓名： " << students[i].name << " 学号： " << students[i].id << std::endl;
            s = students[i];
            students[i].getCommonSubjects(all);
            students[i].getElectiveSubjects(all);
            std::cout << "科目     学分     成绩     绩点     课程类型" << std::endl;
            for (int j = 0; j < all.size(); j++) {
                Subject subject = all[j];
                std::cout << subject.name << "   " << subject.getCredit() << "   " << subject.getGrade() << "  "
                          << subject.getGPA() << "   ";
                if (subject.dir == 1)
                    std::cout << "必修" << std::endl;
                else
                    std::cout << "选修" << std::endl;
            }
            std::cout << std::setprecision(4) << "平均GPA：" << s.getGPA();
            std::cout << "   平均加权：" << s.getGrade() << "    总学分数：" << s.getCredit() << std::endl << std::endl;
        }           //  获取学生成绩信息
    }
    if (!flag) {
        std::cout << "该生不存在！" << std::endl;
        exit2Menu();
        return;
    }
}


