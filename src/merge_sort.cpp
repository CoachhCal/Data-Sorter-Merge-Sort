//
// Created by calvi on 2025-04-11.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "merge_sort.h"

void MergeSort::split() {

    std::fstream in_file(_merged_file, std::ios::in);
    std::string line;

    auto num_subfiles = 0;

    // keep splitting while there are records to read
    std::string prev = "-1";

    while (getline(in_file, line)) {

        // read a field
        auto curr = extract_field(line, _field_num);

        // increase the subfile count when the next record is a decreasing value
        if (compare_values(curr, prev, "<")) num_subfiles++;

        // write out subfiles in an odds/evens fashion
        if (num_subfiles % 2 == 0) {
            append_to_file(_split_file_1, line);
        } else {
            append_to_file(_split_file_2, line);
        }

        prev = curr;
    }
}

bool MergeSort::elements_in_sublist(const std::string& first, const std::string& last) const {

    return !is_file_empty(first)
           && compare_values(extract_first_field(first, _field_num), std::move(last), ">=");
}

bool MergeSort::elements_in_column(const std::string& first, const std::string& second, const std::string& last) const {

    return !is_file_empty(first)
           && compare_values(extract_first_field(first, _field_num), last, ">=")
           && (is_file_empty(second)
               || (compare_values(extract_first_field(second, _field_num), last, "<"))
               || (compare_values(extract_first_field(first, _field_num),
                                  extract_first_field(second, _field_num),
                                  "<")));
}

bool MergeSort::elements_not_in_current_list(const std::string& first, const std::string& second, const std::string& last) const {

    return is_file_empty(first) || !is_file_empty(second)
                                   && ((compare_values(extract_first_field(first, _field_num), last, "<"))
                                       || ((compare_values(extract_first_field(first, _field_num), last, ">"))
                                           && (compare_values(extract_first_field(second, _field_num),
                                                              extract_first_field(first, _field_num),
                                                              "<"))));
}

auto MergeSort::merge() {

    auto num_subfiles = 0;

    // empty the file before records are appended to it
    empty_file(_merged_file);

    // who starts the process?
    std::string first = is_file_empty(_split_file_2)
                        || (compare_values(extract_first_field(_split_file_1, _field_num),
                                           extract_first_field(_split_file_2, _field_num),
                                           "<"))
                        ? _split_file_1 : _split_file_2;

    std::string second = first == _split_file_1 ? _split_file_2 : _split_file_1;

    // keep merging while there are records left to read
    while (!is_file_empty(_split_file_1) || !is_file_empty(_split_file_2)) {

        std::string last = "-1";

        while (elements_in_sublist(first, last)) {

            // take records from file while they are in order
            do {

                last = extract_first_field(first, _field_num);
                append_to_file(_merged_file, get_first_record(first));
                remove_first_record(first);

            } while (elements_in_column(first, second, last));

            // done taking elements, now switch to other file
            if (elements_not_in_current_list(first, second, last)) {
                std::swap(first, second);
            }
        }

        // move to next sublist
        num_subfiles++;
    }

    return num_subfiles;
}

bool MergeSort::compare_values(const std::string& left_value, const std::string& right_value, const std::string& comparison) const {

    // fields that are cast to doubles and compared as such
    if (_field_num == 3 || _field_num == 9 || _field_num == 10 || _field_num == 13) {
        try {

            double left = std::stod(left_value);
            double right = std::stod(right_value);

            if (comparison == "<") return left < right;
            else if (comparison == ">") return left > right;
            else if (comparison == ">=") return left >= right;

        } catch (const std::invalid_argument&) {
            std::cerr << "error converting from string to double" << std::endl;
        }
    }

    // fields that are of type string and will be compared as such
    if (comparison == "<") return left_value < right_value;
    else if (comparison == ">") return left_value > right_value;
    else if (comparison == ">=") return left_value >= right_value;
    else {
        std::cerr << "error comparing values" << std::endl;
        return false;
    }
}

std::string MergeSort::get_first_record(const std::string& file_name) {

    std::ifstream file(file_name);
    std::string line;

    // get the first line (record) from the file
    if (std::getline(file, line)) {
        return line;
    }

    std::cerr << "error extracting field from first line" << std::endl;

    return {};
}

std::string MergeSort::extract_field(const std::string& line, int field_num) {

    std::stringstream ss(line);
    std::string field;
    int currentIndex = 0;

    // get the required field from the record
    while (std::getline(ss, field, '\t')) {
        if (currentIndex == field_num) {
            return field;
        }
        ++currentIndex;
    }

    return "";
}

std::string MergeSort::extract_first_field(const std::string& file_name, int field_num) {

    std::ifstream file(file_name);
    std::string line;
    std::string value;

    // get the required field from the record
    if (std::getline(file, line)) {
        value = extract_field(line, field_num);

        // if it's the address field, extract only the street number
        if (field_num == 3) {
            return get_address_number(value);
        } else {
            return value;
        }

    } else {
        std::cerr << "error getting line from file" << std::endl;
        return value;
    }
}

void MergeSort::append_to_file(const std::string& file_name, const std::string& record) {

    std::ofstream file(file_name, std::ios::app);

    if (!file) {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    // append the record onto the file
    file << record << std::endl;
}

bool MergeSort::is_file_empty(const std::string& file_name) {

    std::ifstream file(file_name);

    // check to see if the file is empty
    return file.peek() == std::ifstream::traits_type::eof();
}

void MergeSort::remove_first_record(const std::string& file_name) {

    std::ifstream file_in(file_name);

    if (!file_in) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::ofstream file_out(_temp_file);
    std::string line;

    // Skip the first line
    if (std::getline(file_in, line)) {}

    // Copy remaining lines directly to the new file
    while (std::getline(file_in, line)) {
        file_out << line << '\n';
    }

    file_in.close();
    file_out.close();

    // copy the contents from the temporary file back to the original file
    copy_file(_temp_file, file_name);

}

void MergeSort::copy_file(const std::string& temp_file, const std::string& main_file) {

    std::string line;

    std::ifstream file_in(temp_file);
    std::ofstream file_out(main_file, std::ios::out | std::ios::trunc);

    if (!file_in || !file_out) {
        std::cerr << "Error: Unable to overwrite original file." << std::endl;
        return;
    }

    // Overwrite original file with the records stored in temp file
    while (std::getline(file_in, line)) {
        file_out << line << '\n';
    }
}

void MergeSort::empty_file(const std::string& file_name) {

    std::ofstream file(file_name, std::ios::out | std::ios::trunc);

}

std::string MergeSort::get_address_number(const std::string& address) {

    std::istringstream iss(address);
    std::string street_number;

    // extract the first word (street number)
    iss >> street_number;

    try {

        // check if street number can be cast to double
        double num = std::stod(street_number);
        return std::to_string(num);

    } catch (const std::invalid_argument&) {

        std::string numbers;

        // since street number can't be cast to a double,
        // filter through and take only the digits (ex. 71B becomes 71)
        for (char ch: street_number) {
            if (std::isdigit(ch)) {
                numbers += ch;
            }
        }

        // return empty string if no numbers found
        if (numbers.empty()) {
            return {};
        }

        return numbers;
    }
}

void MergeSort::sort() {

    auto subfiles = 0;

    do {

        // sort the "merged" file into two separate files
        split();

        // merge the two files back into the "merged" file
        subfiles = merge();

    } while (subfiles != 1);

}
