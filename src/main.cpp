#include <iostream>
#include "sort_data.h"

int parse_field_argument(const std::string& arg) {

    std::string prefix = "-field=";

    // Ensure the argument starts with "-field="
    if (arg.rfind(prefix, 0) == 0) {

        //extract the number
        std::string num_str = arg.substr(prefix.length());

        try {

            int num = std::stoi(num_str);

            //ensure field is between 0 and 13
            if (num >= 0 && num <= 13) {
                return num;
            } else {
                std::cerr << "Error: Field number must be between 0 and 13." << std::endl;
                std::exit(EXIT_FAILURE);
            }

        } catch (const std::invalid_argument&) {
            std::cerr << "Error: Invalid field number '" << num_str << "'. Must be an integer." << std::endl;
            std::exit(EXIT_FAILURE);
        }

    } else {
        std::cerr << "Error: Argument format must be '-field=<number>'." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    SortData sort_data;

    sort_data._data_file = argv[1];
    sort_data._field_num = parse_field_argument(argv[2]);
    sort_data._file_to_save = argv[3];

    // call method that starts the sorting algorithm
    sort_data.sort_employees();

}
