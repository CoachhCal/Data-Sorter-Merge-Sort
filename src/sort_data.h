//
// Created by calvi on 2025-04-10.
//

#ifndef EMPLOYEE_RECORD_SORTER_SORT_DATA_H
#define EMPLOYEE_RECORD_SORTER_SORT_DATA_H


#include <string>
#include "merge_sort.h"

class SortData {
public:

    std::string _data_file;
    int _field_num;
    std::string _file_to_save;

    void sort_employees() const;
    void create_files(const MergeSort&) const;
    void save_sorted_file(const MergeSort&) const;
    static void delete_files(const MergeSort&);

};


#endif //EMPLOYEE_RECORD_SORTER_SORT_DATA_H
