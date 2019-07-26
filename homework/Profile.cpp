//
// Created by Septieme on 2019/7/26.
//

#include "Profile.h"

Profile::Profile(std::string n, std::string id) {
    name = n;
    this->id = id;
}

void Profile::addCommonSubjects(Subject sub) {
    common.push_back(sub);
}

void Profile::addElectiveSubjects(Subject sub) {
    elective.push_back(sub);
}

void Profile::getCommonSubjects(std::vector<Subject> &cs) {
    for (int i = 0; i < common.size(); i++) {
        cs.push_back(common[i]);
    }
}

void Profile::getElectiveSubjects(std::vector<Subject> &es) {
    for (int i = 0; i < elective.size(); i++) {
        es.push_back(elective[i]);
    }
}
