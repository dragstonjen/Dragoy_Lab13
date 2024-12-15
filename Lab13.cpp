#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
protected:
    string name;
    double price;

public:
    Product(const string& name, double price) : name(name), price(price) {}

    virtual ~Product() {}

    void setName(const string& name) { this->name = name; }
    string getName() const { return name; }

    void setPrice(double price) { this->price = price; }
    double getPrice() const { return price; }

    virtual double getFinalPrice() const = 0;

    virtual void printDetails() const {
        cout << "Product: " << name << endl;
        cout << "Base Price: " << price << " UAH" << endl;
    }
};

class Discountable {
public:
    virtual ~Discountable() {}

    virtual double applyDiscount(double price) const = 0;
};

class Book : public Product, public Discountable {
public:
    Book(const string& name, double price) : Product(name, price) {}

    double applyDiscount(double price) const override {
        return price * 0.9;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }

    void printDetails() const override {
        Product::printDetails();
        cout << "Final Price (with discount): " << getFinalPrice() << " UAH" << endl;
    }
};

class Pen : public Product, public Discountable {
public:
    Pen(const string& name, double price) : Product(name, price) {}

    double applyDiscount(double price) const override {
        return (price > 5) ? price - 5 : price;
    }

    double getFinalPrice() const override {
        return applyDiscount(price);
    }

    void printDetails() const override {
        Product::printDetails();
        cout << "Final Price (with discount): " << getFinalPrice() << " UAH" << endl;
    }
};

int main() {
 
    vector<Product*> products;
    products.push_back(new Book("C++ Programming", 300));
    products.push_back(new Book("Data Structures", 250));
    products.push_back(new Pen("Blue Pen", 10));
    products.push_back(new Pen("Cheap Pen", 3));

    for (const auto& product : products) {
        product->printDetails();
        cout << "---------------------------" << endl;
    }

    for (auto& product : products) {
        delete product;
    }

    return 0;
