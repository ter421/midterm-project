// jed filip m. sayat

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

class Product 
{
private:
    string prodId;
    string prodName;
    int prodQuantity;
    double prodPrice;
    string prodCategory;

public:
    Product(string id, string name, int quantity, double price, string category)
        : prodId(id), prodName(name), prodQuantity(quantity), prodPrice(price), prodCategory(category) 
        {}

    string getProdId() { return prodId; }
    string getProdName() { return prodName; }
    int getProdQuantity() { return prodQuantity; }
    double getProdPrice() { return prodPrice; }
    string getProdCategory() { return prodCategory; }

    void setProdQuantity(int newQuantity) { prodQuantity = newQuantity; }
    void setProdPrice(double newPrice) { prodPrice = newPrice; }

    void displayProd() 
    {
        cout << prodId << "\t" << prodName << "\t" << prodQuantity << "\t" << prodPrice << "\t" << prodCategory << endl;
    }
};

class StoreInventoryAbstraction {
protected:
    Product *products[100] = {};
    int prodCount = 0;

    string toLowercaseString(const string &str) 
    {
        string result = str;
        for (char &c: result) 
        {
            c = tolower(c);
        }
        return result;
    }

    bool isProdCategoryValid(const string &category) 
    {
        return toLowercaseString(category) == "clothing" || toLowercaseString(category) == "electronics" || toLowercaseString(category) ==
               "entertainment";
    }

    bool isProdIdAlphaNumeric(const string &id) 
    {
        for (char c: id) 
        {
            if (!isalnum(c))
            {
                return false;
            }
        }
        return true;
    }

    bool isProdIdValid(const string &id) 
    {
        for (char c: id) 
        {
            if (!isdigit(c)) 
            {
                return false;
            }
        }
        return true;
    }

    int findProdIndexById(const string &id) 
    {
        for (int i = 0; i < prodCount; i++) 
        {
            if (products[i]->getProdId() == id) 
            {
                return i;
            }
        }
        return -1;
    }

public:
    virtual ~StoreInventoryAbstraction()
    {
        for (int i = 0; i < prodCount; i++) 
        {
            delete products[i];
        }
    }

    virtual void addProduct() = 0;
    virtual void updateProduct() = 0;
    virtual void removeProduct() = 0;
    virtual void displayProductsByCategory() = 0;
    virtual void displayAllProducts() = 0;
    virtual void searchProduct() = 0;
    virtual void sortProducts() = 0;
    virtual void displayLowStockProducts() = 0;
};

class StoreInventory : public StoreInventoryAbstraction 
{
private:

public:
    void addProduct() override 
    {
        if (prodCount >= 100) 
        {
            cout << "\nInventory is full! Cannot add more products." << endl;
            return;
        }

        string prodCategory, prodId, prodName;
        int prodQuantity;
        double prodPrice;

        bool isValid;

        do 
        {
            isValid = false;
            cout << "\nEnter Product Category (Clothing, Electronics, Entertainment): ";
            cin >> prodCategory;

            if (isProdCategoryValid(prodCategory)) 
            {
                isValid = true;
            } 
            
            else 
            {
                cout << "\nCategory " << prodCategory << " does not exist! Please try again." << endl;
            }
        } 
        
        while (!isValid);


        do 
        {
            isValid = false;
            cout << "\nEnter Product ID: ";
            cin >> prodId;

            if (isProdIdValid(prodId)) 
            {
                isValid = true;
            } 
            
            else 
            {
                cout << "\nInvalid input! Product ID should contain numbers and letters only. Try again." << endl;
            }
        } 
        
        while (!isValid);

        cout << "\nEnter Product Name: ";
        cin.ignore();
        getline(cin, prodName);


        do 
        {
            isValid = false;
            cout << "\nEnter Quantity: ";

            if (cin >> prodQuantity && prodQuantity > 0) 
            {
                isValid = true;
            } 
            
            else 
            {
                cout << "\nInvalid input! Quantity must be a positive integer. Try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } 
        
        while (!isValid);

        do 
        {
            isValid = false;
            cout << "\nEnter Price: ";

            if (cin >> prodPrice && prodPrice > 0) 
            {
                isValid = true;
            } 
            
            else 
            {
                cout << "\nInvalid input! Price must be a positive number. Try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } 
        
        while (!isValid);

        products[prodCount++] = new Product(prodId, prodName, prodQuantity, prodPrice, toLowercaseString(prodCategory));
        cout << "\nProduct added successfully!" << endl;
    }

    void updateProduct() override 
    {
        if (prodCount == 0) 
        {
            cout << "\nNo products in the inventory to update!" << endl;
            return;
        }

        string prodId;
        cout << "\nEnter Product ID: ";
        cin >> prodId;

        int index = findProdIndexById(prodId);

        if (index == -1) 
        {
            cout << "\nProduct not found!" << endl;
            return;
        }

        string updateChoice;
        cout << "\nUpdate (quantity/price)? ";
        cin >> updateChoice;
        updateChoice = toLowercaseString(updateChoice);

        if (updateChoice == "quantity") 
        {
            int newQuantity;
            bool isValid;

            do 
            {
                isValid = false;
                cout << "\nEnter new quantity: ";
                if (cin >> newQuantity && newQuantity > 0) 
                {
                    isValid = true;
                    cout << "\nQuantity of Product " << products[index]->getProdName() << " is updated from "
                            << products[index]->getProdQuantity() << " to " << newQuantity << endl;
                    products[index]->setProdQuantity(newQuantity);
                } 
                
                else 
                {
                    cout << "\nInvalid input! Quantity must be a positive integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } 
            
            while (!isValid);
        } 
        
        else if (updateChoice == "price") 
        {
            double newPrice;
            bool isValid;

            do 
            {
                isValid = false;
                cout << "\nEnter new price: ";

                if (cin >> newPrice && newPrice > 0) 
                {
                    isValid = true;
                    cout << "\nPrice of Product " << products[index]->getProdName() << " is updated from "
                            << products[index]->getProdPrice() << " to " << newPrice << endl;
                    products[index]->setProdPrice(newPrice);
                } 
                
                else 
                {
                    cout << "\nInvalid input! Price must be a positive number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } 
            
            while (!isValid);
        } 
        
        else 
        {
            cout << "\nInvalid input! Invalid update option." << endl;
        }
    }

    void removeProduct() override 
    {
        if (prodCount == 0) 
        {
            cout << "\nNo products to remove!" << endl;
            return;
        }

        string prodId;
        cout << "\nEnter Product ID to remove: ";
        cin >> prodId;

        int index = findProdIndexById(prodId);
        if (index == -1) 
        {
            cout << "\nProduct not found!" << endl;
            return;
        }

        cout << "\nProduct " << products[index]->getProdName() << " has been removed from the inventory." << endl;
        delete products[index];
        for (int i = index; i < prodCount - 1; i++) 
        {
            products[i] = products[i + 1];
        }
        prodCount--;
    }

    void displayProductsByCategory() override 
    {
        if (prodCount == 0) 
        {
            cout << "\nThere are no products in the inventory!" << endl;
            return;
        }

        string prodCategory;
        bool isValid;

        do 
        {
            isValid = false;
            cout << "\nEnter Category to display products: ";
            cin >> prodCategory;

            if (isProdCategoryValid(prodCategory)) 
            {
                isValid = true;
            } 
            
            else 
            {
                cout << "\nCategory " << prodCategory << " does not exist! Please try again." << endl;
            }
        } 
        
        while (!isValid);

        cout << "\nID\tName\tQuantity\tPrice\tCategory" << endl;
        cout << "---------------------------------------------" << endl;

        bool found = false;
        for (int i = 0; i < prodCount; i++) 
        {
            if (products[i]->getProdCategory() == toLowercaseString(prodCategory)) 
            {
                products[i]->displayProd();
                found = true;
            }
        }

        if (!found) 
        {
            cout << "\nNo products found in the " << prodCategory << " category." << endl;
        }
    }

    void displayAllProducts() override 
    {
        if (prodCount == 0) 
        {
            cout << "\nNo products in the inventory!" << endl;
            return;
        }

        cout << "\nID\tName\tQuantity\tPrice\tCategory" << endl;
        cout << "---------------------------------------------" << endl;

        for (int i = 0; i < prodCount; i++) 
        {
            products[i]->displayProd();
        }
    }

    void searchProduct() override 
    {
        if (prodCount == 0) 
        {
            cout << "\nNo products in the inventory!" << endl;
            return;
        }

        string prodId;
        cout << "\nEnter Product ID: ";
        cin >> prodId;

        int index = findProdIndexById(prodId);
        if (index == -1) 
        {
            cout << "\nProduct not found!" << endl;
            return;
        }

        cout << "\nID\tName\tQuantity\tPrice\tCategory" << endl;
        cout << "---------------------------------------------" << endl;
        products[index]->displayProd();
    }

    void sortProducts() override 
    {
        if (prodCount < 2) 
        {
            cout << "\nNot enough products to sort." << endl;
            return;
        }

        for (int i = 0; i < prodCount - 1; i++) 
        {
            for (int j = i + 1; j < prodCount; j++) 
            {
                if (products[i]->getProdName() > products[j]->getProdName()) 
                {
                    swap(products[i], products[j]);
                }
            }
        }
        cout << "\nProducts sorted alphabetically by name." << endl;
    }

    void displayLowStockProducts() override 
    {
        if (prodCount == 0) 
        {
            cout << "\nNo products in the inventory!" << endl;
            return;
        }

        int threshold;
        bool isValid;

        do 
        {
            isValid = false;
            cout << "\nEnter stock threshold to display products with low stock: ";
            if (cin >> threshold && threshold > 0) 
            {
                isValid = true;
            } 
            
            else 
            {
                cout << "\nInvalid input! Threshold must be a positive integer. Try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } 
        
        while (!isValid);

        cout << "\nID\tName\tQuantity\tPrice\tCategory" << endl;
        cout << "---------------------------------------------" << endl;

        bool found = false;
        for (int i = 0; i < prodCount; i++) 
        {
            if (products[i]->getProdQuantity() < threshold) 
            {
                products[i]->displayProd();
                found = true;
            }
        }

        if (!found) 
        {
            cout << "\nNo products found with quantity less than " << threshold << endl;
        }
    }
};

int main() 
{
    StoreInventory storeInventory;

    int choice;
    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Remove Product\n";
        cout << "4. Display Products by Category\n";
        cout << "5. Display All Products\n";
        cout << "6. Search Product\n";
        cout << "7. Sort Products\n";
        cout << "8. Display Low Stock Products\n";
        cout << "9. Exit\n";
        cout << "\nEnter your choice (1-9): ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                storeInventory.addProduct();
                break;
            case 2:
                storeInventory.updateProduct();
                break;
            case 3:
                storeInventory.removeProduct();
                break;
            case 4:
                storeInventory.displayProductsByCategory();
                break;
            case 5:
                storeInventory.displayAllProducts();
                break;
            case 6:
                storeInventory.searchProduct();
                break;
            case 7:
                storeInventory.sortProducts();
                break;
            case 8:
                storeInventory.displayLowStockProducts();
                break;
            case 9:
                cout << "\nExiting..." << endl;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } 
    
    while (choice != 9);

    return 0;
}
