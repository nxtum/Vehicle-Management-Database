# Vehicle Management Database

The Vehicle Management Database is a project aimed at managing a database of vehicles using SQLite. It provides functionalities for adding, removing, and viewing vehicles in a dealership inventory. The system also supports user authentication and role-based access control.

## Project Overview

This project consists of several components:

- **Main Program (`main.cpp`):** This is the entry point of the application. It contains the main function that orchestrates the interaction with the user through the terminal.

- **Vehicle Class (`Vehicle.cpp`, `Vehicle.h`):** Defines the base class for all types of vehicles, such as cars and motorbikes.

- **Car Class (`Car.cpp`, `Car.h`):** Implements the specific characteristics and behaviors of cars, such as the number of doors and body style.

- **Motorbike Class (`Motorbike.cpp`, `Motorbike.h`):** Defines the properties and actions related to motorbikes, such as the number of wheels.

- **Dealership Class (`Dealership.cpp`, `Dealership.h`):** Manages the inventory of vehicles and provides functions for adding, removing, and displaying vehicles.

- **AuthenticationManager Class (`AuthenticationManager.cpp`, `AuthenticationManager.h`):** Handles user authentication and role-based access control.

- **DatabaseHandler Class (`DatabaseHandler.cpp`, `DatabaseHandler.h`):** Provides functionalities for interacting with the SQLite database, including saving and loading data.

- **UtilityFunctions (`UtilityFunctions.cpp`, `UtilityFunctions.h`):** Contains utility functions used throughout the project, such as clearing the screen and handling user input.

## How It Works

The project uses C++ as the primary programming language and relies on the SQLite3 library for database operations. The database is automatically updated + loaded.

1. **Authentication:** Users are required to log in with a username and password. The system verifies the credentials against the database and grants appropriate access based on the user's role (admin, employee, or customer).

2. **Main Menu:** After logging in, users are presented with a menu of options, depending on their role. Admin users have access to administrative functions such as managing the vehicle inventory and user accounts. Employees can perform tasks related to inventory management, while customers have limited access for browsing available vehicles.

3. **Database Interaction:** The application interacts with the SQLite database to store and retrieve information about vehicles, users, and their roles. It uses SQL queries to perform operations such as inserting new records, updating existing ones, and querying data based on specific criteria.

4. **Terminal Interface:** The interaction with the user occurs primarily through the terminal interface. Users navigate the menu by entering numeric options corresponding to different functionalities. The system provides feedback and prompts to guide users through the available actions.

