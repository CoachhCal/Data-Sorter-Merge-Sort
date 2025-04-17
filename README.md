# Employee Information Sorter

## Overview
This program implements a **file-based Merge Sort** algorithm to sort an employee information file based on a user-specified field. The file is a **tab-separated values** format containing employee records.

<details>
  <summary>📂 Employee File Format</summary>

Each row in the file represents an employee, and the columns include:
1. Employee ID (`W9999999`)
2. Last Name
3. First Name
4. Street Address
5. City
6. Province (`ON`, `NS`, `NB`, …)
7. Postal Code (`A9A-9A9`)
8. Phone Number (`999-999-9999`)
9. Gender (`M/F`)
10. Age (`99`)
11. Number of Dependents (`99`)
12. Department Category (`factory`, `office`, `sales`)
13. Union Member (`Y/N`)
14. Hourly Rate (`99.99`)

</details>

## Usage
The program takes in an **employee file**, a **field number** (number from 0-13) to sort by, and a **filename** to save the sorted file as.

To execute the program from the command line, navigate into the cmake-build-debug folder and run:

```sh
Employee_Record_Sorter.exe ../employees.txt -field=<0 - 13> ../output/<file-to-save>.txt

