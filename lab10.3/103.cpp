#include <iostream>
#include <iomanip>
#include <cstring>
#include <Windows.h>

using namespace std;

struct Product {
    char name[100];
    double unitPrice;
    int quantity;
    char unit[50];
};

void displayMenu() {
    cout << "\n����:\n";
    cout << "1. ������ �����\n";
    cout << "2. �������� �����\n";
    cout << "3. ���������� �����\n";
    cout << "4. ��������� ������\n";
    cout << "5. ����� ������ �� ������\n";
    cout << "6. ����� ������ � ������� �������\n";
    cout << "7. ������� �� ������ �� �����\n";
    cout << "8. �����\n";
    cout << "������� �����: ";
}

void inputProductData(Product& product) {
    cout << "������ ����� ������: ";
    cin >> ws;
    cin.getline(product.name, 100);

    cout << "������ ������� ������� ������ � �������: ";
    cin >> product.unitPrice;

    cout << "������ ������� ������: ";
    cin >> product.quantity;

    cout << "������ ������� ����������: ";
    cin >> ws;
    cin.getline(product.unit, 50);
}

void printProduct(const Product& product, int index) {
    double totalValue = product.unitPrice * product.quantity;
    cout << "| " << setw(3) << right << index + 1 << " ";
    cout << "| " << setw(22) << left << product.name
        << "| " << setw(15) << right << product.unitPrice << " "
        << "| " << setw(9) << right << product.quantity << " "
        << "| " << setw(23) << left << product.unit
        << "| " << setw(21) << right << totalValue << " |\n";
}

void printProducts(const Product* products, int size) {
    cout << "==============================================================================================================\n";
    cout << "| �   | ����� ������          |������� ������� | ʳ������ | ������� ����������    | �������� �������     |\n";
    cout << "--------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < size; ++i) {
        printProduct(products[i], i);
    }
    cout << "==============================================================================================================\n";
}

void addProduct(Product*& products, int& size) {
    Product product;
    inputProductData(product);

    Product* temp = new Product[size + 1];
    for (int i = 0; i < size; ++i) {
        temp[i] = products[i];
    }
    temp[size] = product;
    delete[] products;
    products = temp;
    ++size;

    cout << "����� ������ ������.\n";
}

void deleteProduct(Product*& products, int& size) {
    if (size == 0) {
        cout << "������ ������ �������.\n";
        return;
    }

    int index;
    cout << "������ ������ ������ ��� ��������� (1-" << size << "): ";
    cin >> index;
    if (index < 1 || index > size) {
        cout << "������������ ������.\n";
        return;
    }

    Product* temp = new Product[size - 1];
    for (int i = 0, j = 0; i < size; ++i) {
        if (i != index - 1) {
            temp[j++] = products[i];
        }
    }
    delete[] products;
    products = temp;
    --size;

    cout << "����� �������� ������.\n";
}

void editProduct(Product* products, int size) {
    if (size == 0) {
        cout << "������ ������ �������.\n";
        return;
    }

    int index;
    cout << "������ ������ ������ ��� ����������� (1-" << size << "): ";
    cin >> index;
    if (index < 1 || index > size) {
        cout << "������������ ������.\n";
        return;
    }

    inputProductData(products[index - 1]);
    cout << "����� ���������� ������.\n";
}

void sortProducts(Product* products, int size) {
    int option;
    cout << "������ ��� ���������� (1 - �� ������, 2 - �� ��������� �������): ";
    cin >> option;

    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if ((option == 1 && strcmp(products[i].name, products[j].name) > 0) ||
                (option == 2 && (products[i].unitPrice * products[i].quantity) <
                    (products[j].unitPrice * products[j].quantity))) {
                swap(products[i], products[j]);
            }
        }
    }

    cout << "������ �����������.\n";
}

void findProductByName(const Product* products, int size) {
    char name[100];
    cout << "������ ����� ������ ��� ������: ";
    cin >> ws;
    cin.getline(name, 100);

    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (strcmp(products[i].name, name) == 0) {
            printProduct(products[i], i);
            found = true;
        }
    }

    if (!found) {
        cout << "����� �� ��������.\n";
    }
}

void findProductsInRange(const Product* products, int size) {
    double minPrice, maxPrice;
    cout << "������ �������� �������: ";
    cin >> minPrice;
    cout << "������ ����������� �������: ";
    cin >> maxPrice;

    bool found = false;
    for (int i = 0; i < size; ++i) {
        double totalValue = products[i].unitPrice * products[i].quantity;
        if (totalValue >= minPrice && totalValue <= maxPrice) {
            printProduct(products[i], i);
            found = true;
        }
    }

    if (!found) {
        cout << "������ � ��������� ������� �� ��������.\n";
    }
}

void displayAllProducts(const Product* products, int size) {
    if (size == 0) {
        cout << "������ ������ �������.\n";
        return;
    }

    printProducts(products, size);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Product* products = nullptr;
    int size = 0;
    bool exit = false;

    while (!exit) {
        displayMenu();
        int option;
        cin >> option;

        switch (option) {
        case 1:
            addProduct(products, size);
            break;
        case 2:
            deleteProduct(products, size);
            break;
        case 3:
            editProduct(products, size);
            break;
        case 4:
            sortProducts(products, size);
            break;
        case 5:
            findProductByName(products, size);
            break;
        case 6:
            findProductsInRange(products, size);
            break;
        case 7:
            displayAllProducts(products, size);
            break;
        case 8:
            exit = true;
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    }

    delete[] products;
    return 0;
}