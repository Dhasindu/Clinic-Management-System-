# Clinical Management System

This project is a console-based **Clinical Management System** developed in C++. It is designed to streamline interactions between doctors and patients, providing functionalities tailored to each user type. Patients can manage their appointments and view medical records, while doctors can view schedules, access patient records, and update medical information. 

## Project Overview

This system includes the following core features:

### 1. User Authentication
- **User Accounts**: Supports user accounts for both doctors and patients.
- **Secure Passwords**: Each user has a unique username with securely hashed passwords.
- **Login Functionality**: Users can log in to access the system.

### 2. Patient Functionalities
- **View Medical Records**: Patients can view their personal details and a list of past and upcoming appointments.
- **Schedule Appointments**: Patients can view a list of available doctors and their schedules, ensuring no overlapping appointments.
- **Cancel Appointments**: Allows patients to cancel upcoming appointments, confirming and updating the schedule accordingly.
- **Update Personal Information**: Patients can modify their contact details, which are then updated in the system.

### 3. Doctor Functionalities
- **View Schedule**: Doctors can view their upcoming appointments with details about each patient.
- **Access Patient Records**: Doctors can search for a patient by name and view medical history.
- **Update Patient Records**: Doctors can update patient records post-consultation with diagnoses, prescriptions, and recommendations.
- **Mark Appointment as Complete**: After a consultation, doctors can mark an appointment as completed.

## Technical Requirements

- **Data Persistence**: Data for patients and doctors is stored using file handling, allowing information to persist across sessions.
- **Security**: Implements password hashing to secure user credentials.
- **Console Interface**: User-friendly interface with clear prompts and menus.
- **Error Handling**: Robust error handling for invalid inputs with helpful messages.

## Getting Started

### Prerequisites
- **C++ Compiler**: Ensure a C++ compiler is installed (e.g., GCC or Visual Studio).
- **Terminal**: Run the application in a terminal or console.

### Running the Program
1. **Clone the Repository**:
   ```shell
   git clone https://github.com/your-username/clinical-management-system.git
