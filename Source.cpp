#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>


using namespace std;

class Animal {
private:
    string species;
    string breed;
    double price;
    int quantity;
public:
    Animal(string species, string breed, double price, int quantity)
        : species(species), breed(breed), price(price), quantity(quantity) {}

    string getSpecies() const { return species; }
    string getBreed() const { return breed; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};


class Feed {
private:
    string name;
    string suitableFor;
    double price;
    int quantity;
public:
    Feed(string name, string suitableFor, double price, int quantity)
        : name(name), suitableFor(suitableFor), price(price), quantity(quantity) {}

    string getName() const { return name; }
    string getSuitableFor() const { return suitableFor; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};


class PetShop {
private:
    vector<Animal> animals;
    vector<Feed> feeds;
    vector<string> salesHistory;

public:
    void addProduct(const Animal& animal) { animals.push_back(animal); }
    void addProduct(const Feed& feed) { feeds.push_back(feed); }
    void removeProduct(string productName);
    void showProducts() const;
    void sellProduct(string productName, int quantity);
    void showSalesHistory() const;
    void updateProduct(string productName, double newPrice, int newQuantity);
    void showInventoryReport() const;
    void findProductByName(string productName) const;
    void findMostExpensiveProduct() const;
};


void PetShop::removeProduct(string productName) {
    for (auto it = animals.begin(); it != animals.end(); ++it) {
        if (it->getSpecies() == productName) {
            animals.erase(it);
            return;
        }
    }
    for (auto it = feeds.begin(); it != feeds.end(); ++it) {
        if (it->getName() == productName) {
            feeds.erase(it);
            return;
        }
    }
    cout << "����� �� ������!" << endl;
}

void PetShop::findProductByName(string productName) const {
    bool found = false;
    for (const auto& animal : animals) {
        if (animal.getSpecies() == productName || animal.getBreed() == productName) {
            cout << "�������� �������:\n";
            cout << animal.getSpecies() << ": " << animal.getBreed() << "\n����: " << animal.getPrice()
                << "\n� �������: " << animal.getQuantity() << endl;
            found = true;
        }
    }
    for (const auto& feed : feeds) {
        if (feed.getName() == productName) {
            cout << "���� ������:\n";
            cout << feed.getName() << " - �������� ���: " << feed.getSuitableFor() << "\n����: " << feed.getPrice()
                << " \n� �������: " << feed.getQuantity() << endl;
            found = true;
        }
    }
    if (!found)
        cout << "������� �� ������!" << endl;
}

void PetShop::showProducts() const {

    cout << "�������� � �������:" << endl;
    for (const auto& animal : animals) {
        cout << animal.getSpecies() << ": " << animal.getBreed() << "\n����: " << animal.getPrice()
            << "\n� �������: " << animal.getQuantity() << endl;
    }
    cout << endl;
    cout << "���� � �������:" << endl;
    for (const auto& feed : feeds) {
        cout << feed.getName() << " - �������� ���: " << feed.getSuitableFor() << "\n����: " << feed.getPrice()
            << " \n� �������: " << feed.getQuantity() << endl;
    }
    cout << endl;

}

void PetShop::sellProduct(string productName, int quantity) {
    for (auto& animal : animals) {
        if (animal.getSpecies() == productName) {
            if (animal.getQuantity() >= quantity) {
                animal.setQuantity(animal.getQuantity() - quantity);
                salesHistory.push_back(productName + " (��������) - " + to_string(quantity) + " ��.");
                cout << "������� ������� ���������!" << endl;
                return;
            }
            else {
                cout << "������������ ������ � �������!" << endl;
                return;
            }
        }
    }
    for (auto& feed : feeds) {
        if (feed.getName() == productName) {
            if (feed.getQuantity() >= quantity) {
                feed.setQuantity(feed.getQuantity() - quantity);
                salesHistory.push_back(productName + " (����): " + to_string(quantity) + " ��.");
                cout << "������� ������� ���������!" << endl;
                return;
            }
            else {
                cout << "������������ ������ � �������!" << endl;
                return;
            }
        }
    }
    cout << "����� �� ������!" << endl;
}

void PetShop::showSalesHistory() const {
    cout << "������� ������:" << endl;
    for (const auto& sale : salesHistory) {
        cout << sale << endl;
    }
    cout << endl;
}

void PetShop::updateProduct(string productName, double newPrice, int newQuantity) {
    for (auto& animal : animals) {
        if (animal.getSpecies() == productName) {
            animal.setPrice(newPrice);
            animal.setQuantity(newQuantity);
            cout << "���������� � ������ ������� ���������!" << endl;
            return;
        }
    }
    for (auto& feed : feeds) {
        if (feed.getName() == productName) {
            feed.setPrice(newPrice);
            feed.setQuantity(newQuantity);
            cout << "���������� � ������ ������� ���������!" << endl;
            return;
        }
    }
    cout << "����� �� ������!" << endl;
}

void PetShop::findMostExpensiveProduct() const {
    if (!animals.empty() || !feeds.empty()) {
        auto mostExpensiveAnimal = max_element(animals.begin(), animals.end(), [](const Animal& a, const Animal& b) {
            return a.getPrice() < b.getPrice();
            });

        auto mostExpensiveFeed = max_element(feeds.begin(), feeds.end(), [](const Feed& a, const Feed& b) {
            return a.getPrice() < b.getPrice();
            });

        cout << "����� ������� ��������: " << mostExpensiveAnimal->getSpecies() << " (" << mostExpensiveAnimal->getBreed()
            << ") ����: " << mostExpensiveAnimal->getPrice() << endl;

        cout << "����� ������� ����: " << mostExpensiveFeed->getName() << " ����: " << mostExpensiveFeed->getPrice() << endl;
    }
    else {
        cout << "������� ����!" << endl;
    }
}


int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    PetShop petShop;

    int choice;
    do {
        cout << "\n����:" << endl;
        cout << "1. �������� �����" << endl;
        cout << "2. ������� �����" << endl;
        cout << "3. �������� �����" << endl;
        cout << "4. �������� ��� ������" << endl;
        cout << "5. ������� �����" << endl;
        cout << "6. �������� ������� ������" << endl;
        cout << "7. ����� ����� ������� �����" << endl;
        cout << "8. ����� ����� �� ��������" << endl;
        cout << "9. ����� �� ���������" << endl;
        cout << "�������� ��������: ";

        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "\n�������� ��� ������ (1 - ��������, 2 - ����): ";
            int typeChoice;
            cin >> typeChoice;
            if (typeChoice == 1) {
                string species, breed;
                double price;
                int quantity;
                cout << "������� ��� ���������: ";
                cin >> species;
                cout << "������� ������ ���������: ";
                cin >> breed;
                cout << "������� ����: ";
                cin >> price;
                cout << "������� ����������: ";
                cin >> quantity;

                if (price <= 0 || quantity <= 0) {
                    cout << "\n���� � ���������� ������ ���� �������������� �������!" << endl;
                    break;
                }

                petShop.addProduct(Animal(species, breed, price, quantity));
            }
        case 2: {
            string productName;
            cout << "\n������� �������� ������, ������� ������ �������: ";
            cin >> productName;


            if (productName.empty()) {
                cout << "\n�������� ������ �� ������ ���� ������!" << endl;
                break;
            }

            petShop.removeProduct(productName);
            break;
        }

        case 3: {
            string productName;
            double newPrice;
            int newQuantity;
            cout << "\n������� �������� ������, ������� ������ ��������: ";
            cin >> productName;
            cout << "������� ����� ����: ";
            cin >> newPrice;
            cout << "������� ����� ����������: ";
            cin >> newQuantity;

            if (productName.empty() || newPrice <= 0 || newQuantity <= 0) {
                cout << "\n�������� ������! ��������� ��������� ��������." << endl;
                break;
            }

            petShop.updateProduct(productName, newPrice, newQuantity);
            break;
        }
        case 4: {
            petShop.showProducts();
            break;
        }
        case 5: {
            string productName;
            int quantity;
            cout << "\n������� �������� ������, ������� ������ �������: ";
            cin >> productName;
            cout << "������� ����������: ";
            cin >> quantity;


            if (productName.empty() || quantity <= 0) {
                cout << "\n�������� ������! ��������� ��������� ��������." << endl;
                break;
            }

            petShop.sellProduct(productName, quantity);
            break;
        }
        case 6: {
            petShop.showSalesHistory();
            break;
        }
        case 7: {
            petShop.findMostExpensiveProduct();
            break;
        }
        case 8: {
            string productName;
            cout << "\n������� �������� ������ ��� ������: ";
            cin >> productName;


            if (productName.empty()) {
                cout << "\n�������� ������ �� ������ ���� ������!" << endl;
                break;
            }

            petShop.findProductByName(productName);
            break;
        }
        case 9: {
            cout << "\n�� ��������!" << endl;
            return 0;
        }
        default: {
            cout << "\n�������� ����� ��������!" << endl;
            break;
        }


        }
              return 0;
        }
    }while(true);
}
