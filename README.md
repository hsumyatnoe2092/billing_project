Alright bro — I got your full **C++ billing system project** (second semester project) 📘
I’ll create a **clean, professional, ready-to-upload README.md** for your GitHub repo.

It will explain:


# **Supermarket Billing System (C++ Project)**

*A second semester C++ project using file handling, OOP, and a menu-driven system.*
## 📌 **Project Overview**

This is a **Supermarket Billing System** implemented in **C++** using:

* File handling (`fstream`)
* Classes and OOP concepts
* Menu-driven architecture
* Order placement and stock updates
* Admin product management
* Billing history logging

The system allows customers to place orders and admins to manage product data stored in external files.

---

## 🎯 **Features**

### 🔹 **Customer Features**

* View available products
* Place an order
* Auto-calculate:

  * Amount
  * Discount
  * Final total
* Generates invoice/voucher
* Saves billing history in `billing_history.txt`

---

### 🔹 **Admin Features**

* Add a new product
* Modify existing products
* Delete a product
* View all product menu
* View full billing history

Admin operations modify the file:
📄 **Store_Info.txt**

---

## 🧾 **File Descriptions**

| File                    | Purpose                                                               |
| ----------------------- | --------------------------------------------------------------------- |
| **Store_Info.txt**      | Stores all product records (item no, name, price, discount, quantity) |
| **billing_history.txt** | Stores past order records (order no, product name, quantity, total)   |
| **Temp.txt**            | Used temporarily for Delete operations                                |
| **billingproject.cpp**  | Main source code (your project)                                       |

---

## 📦 **Class & Functions**

### **Class: `supermarket`**

Handles all core logic such as:

* `AddProduct()`
* `ShowProduct()`
* `PlaceOrder()`
* `Update()`
* `Delete()`
* `Display()`
* `menu()`
* `AdminMenu()`
* `DisplayBillingHistory()`

Uses nested struct:

### **Struct: `BillingHistory`**

Stores:

* Order Number
* Product Name
* Quantity
* Total Amount

---

## ▶️ **How to Run the Program**

### **1. Compile**

Using g++:

```bash
g++ billingproject.cpp -o billing
```

### **2. Run**

```bash
./billing
```

---

## 🧮 **Program Flow**

### ⭐ **MAIN MENU**

```
1. Customer
2. Administrator
3. Exit
```

### ⭐ **ADMIN MENU**

```
1. Create Product  
2. Modify Product  
3. Delete Product  
4. View Product Menu  
5. View Billing History  
6. Back to Main Menu  
```

---

## 💡 **Key Concepts Used**

* File Handling (read, write, append)
* Object-Oriented Programming
* Data validation
* Error handling (invalid input check)
* Dynamic menu interaction
* Record updating via file pointer seeking
* Storing billing history

---

## 📝 **Sample Output (Invoice)**

```
******************************** VOUCHER ************************

Item No.   Item Name   Quantity   Price   Amount   Amount after discount

TOTAL = XXXX
```

---

## 📚 **Project Purpose**

This project is created for **Second Semester C++ Course**, demonstrating:

* Practical use of OOP
* File management
* Real-world billing system logic
* Clean user interface via menus

---

## 👨‍💻 Author

**hsumyatnoe**
Second Semester  Student
GitHub: *hsumyatnoe2092*



                   ┌────────────────────┐
                   │      START         │
                   └───────┬────────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │      MAIN MENU       │
                │ 1. Customer          │
                │ 2. Administrator     │
                │ 3. Exit              │
                └─────────┬────────────┘
                          │
        ┌─────────────────┴───────────────────┐
        ▼                                     ▼
 ┌──────────────┐                    ┌───────────────────┐
 │   CUSTOMER   │                    │   ADMINISTRATOR   │
 └──────┬───────┘                    └──────────┬────────┘
        │                                      │
        ▼                                      ▼
┌──────────────────┐               ┌─────────────────────────────┐
│ Display Product   │               │       ADMIN MENU            │
│ Menu (menu())     │               │ 1. Create Product           │
└───────┬──────────┘               │ 2. Modify Product           │
        │                          │ 3. Delete Product           │
        ▼                          │ 4. View Product Menu        │
┌───────────────────────┐          │ 5. View Billing History     │
│ Place Order? (Y/N)    │          │ 6. Back to Main Menu        │
└──────────┬────────────┘          └──────────┬──────────────────┘
           │                                   │
   ┌───────▼────────┐                 ┌────────▼────────────────┐
   │ Enter Product   │                 │    Selected Option?     │
   │ Number & Qty    │                 └─────────┬──────────────┘
   └───────┬────────┘                           │
           │                          ┌─────────┴─────────┐
┌──────────▼───────────────────┐      │ 1. Create Product │
│ Validate Product Exists?     │      └─────────┬─────────┘
└──────────┬───────────────────┘                │
           │ Yes                                ▼
           ▼                          ┌──────────────────────┐
┌─────────────────────────────┐       │ Input Product, Save  │
│ Calculate Amount & Discount │       │ To Store_Info.txt    │
└───────────┬─────────────────┘       └──────────────────────┘
            │
            ▼
┌─────────────────────────────┐
│ Update Stock in File        │
│ Record Billing History      │
└──────────┬──────────────────┘
           │
           ▼
┌──────────────────────────────┐
│ Add Another Product? (Y/N)   │
└──────────┬───────────────────┘
           │
      ┌────▼──────┐
      │   YES     │ Loop back to Place Order
      └────┬──────┘
           │
           ▼ NO
┌───────────────────────────────┐
│ Generate Invoice / Voucher     │
└───────────┬────────────────────┘
            │
            ▼
       ┌───────────┐
       │   END     │
       └───────────┘

