#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Goods {
    string model;       // 货物型号
    int quantity;       // 数量
};

vector<Goods> inventory; // 库存

// Function prototypes
void showInventory();     // 显示库存
void addStock();          // 入库
void sellStock();         // 出库
void saveInventoryToFile();// 保存库存到文件
void loadInventoryFromFile(); // 从文件加载库存

int main() {
    // 在程序启动时从文件中加载库存
    loadInventoryFromFile();

    int choice;
    do {
        cout << "1. Show Inventory\n";
        cout << "2. Add Stock\n";
        cout << "3. Sell Stock\n";
        cout << "4. Exit Program\n";
        cout << "Enter the menu number: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showInventory();
                break;
            case 2:
                addStock();
                break;
            case 3:
                sellStock();
                break;
            case 4:
                // Save inventory to file before exiting
                saveInventoryToFile();
                cout << "Program has exited.\n";
                break;
            default:
                cout << "Invalid selection. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void showInventory() {
    cout << "Inventory List:\n";
    for (const auto& item : inventory) {
        cout << "Model: " << item.model << ", Quantity: " << item.quantity << endl;
    }
}

void addStock() {
    Goods newGoods;
    cout << "Enter the model of the goods: ";
    cin >> newGoods.model;
    cout << "Enter the quantity to add: ";
    cin >> newGoods.quantity;

    inventory.push_back(newGoods);
    cout << "Stock added successfully.\n";
}

void sellStock() {
    string model;
    int quantity;  // Add this line to define quantity
    // 出库
    cout << "Enter the model of the goods: ";
    cin >> model;
    cout << "Enter the quantity to sell: ";
    cin >> quantity;

    for (auto& item : inventory) {
        if (item.model == model) {
            if (item.quantity >= quantity) {
                item.quantity -= quantity;
                cout << "Stock sold successfully.\n";
            } else {
                cout << "Insufficient stock.\n";
            }
            return;
        }
    }

    cout << "Goods not found.\n";
}

void saveInventoryToFile() {
    // 保存库存数据到文件
    ofstream outFile("inventory.txt");
    if (outFile.is_open()) {
        for (const auto& item : inventory) {
            outFile << item.model << " " << item.quantity << endl;
        }
        outFile.close();
        cout << "Inventory data saved.\n";
    } else {
        cout << "Unable to save inventory data to file.\n";
    }
}

void loadInventoryFromFile() {
    // 从文件加载库存数据
    ifstream inFile("inventory.txt");
    if (inFile.is_open()) {
        inventory.clear(); // 清除现有库存数据

        while (!inFile.eof()) {
            Goods item;
            inFile >> item.model >> item.quantity;
            if (!item.model.empty()) {
                inventory.push_back(item);
            }
        }

        inFile.close();
        cout << "Inventory data loaded.\n";
    } else {
        cout << "Inventory data file not found.\n";
    }
}