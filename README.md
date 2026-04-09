# rfid-smart-shopping-trolley-lpc2129
RFID-Based Smart Shopping Trolley System using ARM7 LPC2129 with real-time billing and data storage
# 🚗 RFID-Based Smart Shopping Trolley System

### Intelligent Embedded Retail Automation using ARM7 LPC2129

---

## 📌 Overview

This project presents the design and implementation of an **RFID-Based Smart Shopping Trolley System** using the **ARM7 LPC2129 microcontroller**, aimed at enabling **real-time, self-service retail billing** directly within a shopping trolley.

The system eliminates traditional checkout processes by integrating **RFID-based product identification**, embedded billing logic, and real-time display, thereby reducing billing time, minimizing human error, and improving customer experience.

---

## 🧠 System Concept

Each product is equipped with a unique **RFID tag**. When a product is placed in the trolley, the RFID reader detects the tag and transmits its ID to the LPC2129 microcontroller.

The controller:

* Identifies the product using an internal database
* Updates cart and total bill in real time
* Displays item details and billing information on an LCD

This transforms a conventional shopping trolley into a **smart, autonomous billing unit**.

---

## 🏗️ System Architecture

The system follows a modular embedded architecture:

* **RFID Module** → Automatic product identification
* **LPC2129 Controller** → Core processing and control logic
* **LCD Interface** → Real-time display of item and billing data
* **Cart Management Module** → Item addition, removal, and quantity handling
* **EEPROM Storage** → Last bill retention
* **RTC Module (DS1307)** → Date and time tracking
* **User Interface (Switches)** → Remove, clear, and checkout operations

---

## ⚙️ Key Features

* 🔹 RFID-based automatic product detection
* 🔹 Real-time billing within the shopping trolley
* 🔹 Dynamic cart management (add / remove / clear items)
* 🔹 Quantity tracking for repeated scans
* 🔹 EEPROM-based last bill storage
* 🔹 RTC-based timestamping of transactions
* 🔹 LCD-based user interface
* 🔹 Modular and scalable embedded design

---

## 📡 System Workflow

```text
RFID Tag → RFID Reader → LPC2129 Controller → Product Database Match
        → Cart Update → Total Calculation → LCD Display
        → EEPROM Storage + RTC Timestamp → Checkout
```

---

## 🔌 Hardware Components

* ARM7 LPC2129 Microcontroller
* RFID Reader (EM-18)
* RFID Tags (for products)
* 16x2 LCD Display
* EEPROM (AT24C04 / AT24C08)
* RTC Module (DS1307)
* Push Button Switches
* Power Supply Unit

---

## 💻 Software & Tools

* Embedded C Programming
* Keil uVision IDE
* LPC2129 Device Libraries

---

## 📂 Project Structure

```
rfid-smart-shopping-trolley-lpc2129/
│
├── main.c
├── lcd.c / lcd.h
├── delay.c / delay.h
├── uart0.c / uart0.h
├── rfid.c / rfid.h
├── i2c0.c / i2c0.h
├── eeprom.c / eeprom.h
├── rtc_ds1307.c / rtc_ds1307.h
├── product_db.c / product_db.h
├── cart.c / cart.h
├── STARTUP.S
└── README.md
```

---

## 🚀 How It Works

1. User places product inside trolley
2. RFID reader scans the product tag
3. LPC2129 matches tag with product database
4. Item is added to cart automatically
5. Total bill updates in real time
6. User can:

   * Remove last item
   * Clear entire cart
   * Checkout
7. At checkout:

   * Final bill displayed
   * Timestamp added via RTC
   * Bill stored in EEPROM

---

## 📸 Demonstration

> ![RFID-Based Smart Shopping Trolley System using ARM7 LPC2129 with Real-Time Billing and Data Storage](https://github.com/user-attachments/assets/e6ebf202-ac45-442f-8b7f-73797f759ccb)


* Hardware setup
* LCD output
* Working demonstration

---

## 🎯 Applications

* Smart Retail Systems
* Automated Billing Solutions
* Supermarkets and Shopping Malls
* IoT-based Retail Automation
* Embedded System Prototyping

---

## 🧪 Advantages

* ✔ Eliminates billing queues
* ✔ Reduces human errors
* ✔ Fast and automated checkout
* ✔ Improves customer experience
* ✔ Scalable system design
* ✔ Low-cost embedded solution

---

## 🔮 Future Enhancements

* Mobile app integration
* Wireless billing synchronization
* Cloud-based data logging
* Payment gateway integration
* Weight sensor integration for fraud detection

---

## 📜 License

This project is licensed under the **MIT License**.

---

## 👨‍💻 Author

**SABARINATHAN**
Embedded Software Developer

* 🔗 LinkedIn: https://www.linkedin.com/in/sabarinathans23
* 📧 Email: [sabarinathansja23@gmail.com](mailto:sabarinathansja23@gmail.com)

---

## ⭐ Support

If you found this project useful, please consider giving it a ⭐ on GitHub.
