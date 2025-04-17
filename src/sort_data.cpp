//
// Created by calvi on 2025-04-10.
//

#include <iostream>
#include <fstream>
#include "sort_data.h"
#include "merge_sort.h"

void SortData::sort_employees() const {

    //instantiate merge sort class
    MergeSort merge_sort(_field_num);
    merge_sort._merged_file = _data_file;

    //create all 3 files that will be used in the application
    create_files(merge_sort);

    //sort the employees records
    merge_sort.sort();

    // create a copy of the sorted file and save it where the user selected
    save_sorted_file(merge_sort);

    // clean up: delete files used for sorting
    delete_files(merge_sort);

}

void SortData::create_files(const MergeSort& merge_sort) const {

    //create the 4 empty files used in the program
    std::ofstream file_1(_file_to_save, std::ios::trunc);
    std::ofstream file_2(merge_sort._split_file_1, std::ios::trunc);
    std::ofstream file_3(merge_sort._split_file_2, std::ios::trunc);
    std::ofstream file_4(merge_sort._temp_file, std::ios::trunc);

    if (!file_1 || !file_2 || !file_3 || !file_4) {
        std::cerr << "Error creating one or more files" << std::endl;
        std::exit(EXIT_FAILURE);
    }

}

void SortData::save_sorted_file(const MergeSort& merge_sort) const {

    std::ifstream sorted_file(merge_sort._merged_file, std::ios::binary);
    std::ofstream new_file(_file_to_save, std::ios::binary);

    // copy the employee records over from the sorted file to the new file
    new_file << sorted_file.rdbuf();

}

void SortData::delete_files(const MergeSort& merge_sort) {

    //delete the files used for sorting
    if (std::remove(merge_sort._split_file_1.c_str()) != 0) {
        std::cerr << "Error deleting " << merge_sort._split_file_1 << std::endl;
    }

    if (std::remove(merge_sort._split_file_2.c_str()) != 0) {
        std::cerr << "Error deleting " << merge_sort._split_file_2 << std::endl;
    }

    if (std::remove(merge_sort._temp_file.c_str()) != 0) {
        std::cerr << "Error deleting " << merge_sort._temp_file << std::endl;
    }
}