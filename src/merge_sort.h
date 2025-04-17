//
// Created by calvi on 2025-04-11.
//

#ifndef EMPLOYEE_RECORD_SORTER_MERGE_SORT_H
#define EMPLOYEE_RECORD_SORTER_MERGE_SORT_H


#include <string>

class MergeSort {
public:

    const int _field_num;
    std::string _merged_file;
    const std::string _split_file_1 = "split_file_1.txt";
    const std::string _split_file_2 = "split_file_2.txt";
    const std::string _temp_file = "temp_file.txt";

    explicit MergeSort(int field_num) : _field_num(field_num) {}

    void split();
    void sort();
    auto merge();
    [[nodiscard]] bool elements_in_sublist(const std::string&, const std::string&) const;
    [[nodiscard]] bool elements_in_column(const std::string&, const std::string&, const std::string&) const;
    [[nodiscard]] bool elements_not_in_current_list(const std::string&, const std::string&, const std::string&) const;
    void remove_first_record(const std::string&);
    static std::string extract_first_field(const std::string&, int);
    static std::string get_first_record(const std::string&);
    static std::string extract_field(const std::string&, int);
    static std::string get_address_number(const std::string&);
    [[nodiscard]] bool compare_values(const std::string&, const std::string&, const std::string&) const;
    static bool is_file_empty(const std::string&);
    static void append_to_file(const std::string&, const std::string&);
    static void empty_file(const std::string&);
    static void copy_file(const std::string&, const std::string&);

};


#endif //EMPLOYEE_RECORD_SORTER_MERGE_SORT_H
