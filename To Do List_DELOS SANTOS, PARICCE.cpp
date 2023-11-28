#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool isPriority;

    Task(const string& desc, bool priority) : description(desc), isPriority(priority) {}
};

struct User {
    string username;
    string password;
    vector<Task> todoList;
    vector<string> completedTasks;
};

vector<User> users;

bool isUserExist(const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

User* getUser(const string& username, const string& password) {
    for (User& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}

void displayTodoList(const User& user) {
    cout << endl;
    cout << setw(67) << "Your TODO list:" << endl;
    if (user.todoList.empty()) {
        cout << setw(67) << "(Empty)" << endl;
    }
    else {
        for (size_t i = 0; i < user.todoList.size(); ++i) {
            const auto& task = user.todoList[i];
            cout << setw(52) << i << " - " << (task.isPriority ? "[Priority] " : "") << task.description << endl;
        }
    }
}

void displayCompletedTasks(const User& user) {
    cout << setw(70) << "Your Completed Tasks:" << endl;
    if (user.completedTasks.empty()) {
        cout << setw(70) << "(Empty)" << endl;
    }
    else {
        for (size_t i = 0; i < user.completedTasks.size(); ++i) {
            cout << setw(70) << "\t" << i << " - " << user.completedTasks[i] << endl;
        }
    }
}

int main() {
    while (true) {
        cout << "************************************************************************************************************************\n";
        cout << setw(75) << "WELCOME TO YOUR TO DO LIST!" << endl;
        cout << "************************************************************************************************************************\n" << endl;

        cout << setw(73) << "Please choose an option:\n" << endl;
        cout << setw(66) << "[R] - Register" << endl;
        cout << setw(63) << "[L] - Login" << endl;
        cout << setw(62) << "[E] - Exit" << endl;
        cout << endl;
        cout << endl;
        cout << setw(65) << "Your Choice: ";


        char option;
        cin >> option;

        switch (option) {
        case 'E':
        case 'e':
            cout << endl;
            cout << "                                     ***********************************************                        " << endl;
            cout << setw(78) << " Thank you for trying To Do List! " << endl;
            cout << "                                     ***********************************************                        " << endl;
            return 0;

        case 'R':
        case 'r':
        {
            cout << endl;
            cout << "                                     ***********************************************                        " << endl;
            cout << endl;
            cout << setw(73) << "Register a new account\n\n" << endl;
            string username, password;
            cout << setw(68) << "Enter a username: ";
            cin >> username;

            if (isUserExist(username)) {
                cout << endl;
                cout << setw(90) << "Username already exists. Please choose a different username." << endl;
                cout << endl;

                continue;
            }

            cout << setw(68) << "Enter a password: ";
            cin >> password;
            cout << endl;

            users.push_back({ username, password, {}, {} });
            cout << setw(79) << "{  Account successfully registered! }" << endl;
            cout << endl;
            cout << endl;
            break;
        }

        case 'L':
        case 'l':
        {
            cout << endl;
            cout << "                                     ***********************************************                        " << endl;
            cout << endl;
            cout << endl;
            cout << setw(65) << "Login: \n\n" << endl;
            string username, password;
            cout << setw(70) << "Enter your username: ";
            cin >> username;

            if (!isUserExist(username)) {
                cout << setw(70) << "Username not found. Please register or enter a valid username." << endl;
                continue;
            }

            cout << setw(70) << "Enter your password: ";
            cin >> password;

            User* currentUser = getUser(username, password);

            if (currentUser) {
                cout << endl;
                cout << setw(72) << "{  Login Successful! } " << endl;
                cout << endl;
                cout << endl;
                cout << "                                     ***********************************************                        " << endl;
                cout << setw(60) << "Welcome, " << username << "!! <33" << endl;
                cout << "                                     ***********************************************                        " << endl;

                while (true) {
                    int todoOption;

                    cout << endl;
                    cout << setw(70) << "TODO list options: \n" << endl;
                    cout << setw(68) << "|1| View TODO list" << endl;
                    cout << setw(70) << "|2| Add to TODO list" << endl;
                    cout << setw(76) << "|3| Mark task as completed" << endl;
                    cout << setw(74) << "|4| View Completed Tasks" << endl;
                    cout << setw(60) << "|5| Logout" << endl;
                    cout << endl;
                    cout << endl;
                    cout << setw(65) << "Your Choice:";
                    cin >> todoOption;
                    cout << endl;
                    cout << "                                     ***********************************************                        " << endl;





                    switch (todoOption) {
                    case 5:
                        cout << setw(73) << "Logged out Successfully!" << endl;
                        cout << "                                     ***********************************************                        " << endl;
                        cout << setw(65) << " See you soon, " << username << "! :<<" << endl;
                        cout << "                                     ***********************************************                        " << endl;
                        return 0;

                    case 1:
                        cout << "                                     ***********************************************                        " << endl;
                        displayTodoList(*currentUser);
                        break;

                    case 2: {
                        cout << endl;
                        cout << "Please enter your TODO list item and then press enter: ";
                        string newTodoListItem;
                        cin.ignore();
                        getline(cin, newTodoListItem);

                        cout << endl;
                        cout << setw(77) << "Is this task a priority? \n" << endl;
                        cout << setw(58) << "|1| Yes" << endl;
                        cout << setw(57) << "|0| No" << endl;
                        cout << "Your Choice: ";
                        bool isPriority;
                        cin >> isPriority;

                        currentUser->todoList.push_back({ newTodoListItem, isPriority });
                        cout << "                                     ***********************************************                        " << endl;
                        displayTodoList(*currentUser);
                        cout << endl;
                        cout << endl;
                        cout << setw(75) << "Item added to the TODO list!" << endl;
                        cout << "                                     ***********************************************                        " << endl;
                        cout << endl;
                        break;
                    }

                    case 3: {
                        cout << "Please enter the index of the TODO list item to mark as completed: ";
                        int completeIndex;
                        cin >> completeIndex;


                        if (completeIndex < 0 || completeIndex >= static_cast<int>(currentUser->todoList.size())) {
                            cout << "Invalid index! Please enter a valid index." << endl;
                            continue;
                        }

                        const auto& completedTask = currentUser->todoList[completeIndex];
                        currentUser->completedTasks.push_back(completedTask.description);

                        currentUser->todoList.erase(currentUser->todoList.begin() + completeIndex);
                        cout << "                                     ***********************************************                        " << endl;
                        displayTodoList(*currentUser);
                        cout << endl;
                        cout << endl;
                        cout << setw(85) << "Task marked as completed and moved to history!" << endl;
                        cout << "                                     ***********************************************                        " << endl;
                        break;
                    }

                    case 4:
                        displayCompletedTasks(*currentUser);
                        break;

                    default:
                        cout << "Invalid option! Please choose a valid TODO list option." << endl;
                    }
                }
            }
            else {
                cout << setw(70) << "Invalid password. Please try again or register a new account." << endl;
            }
            break;
        }

        default:
            cout << setw(70) << "Invalid option! Please choose a valid option." << endl;
        }
    }

    return 0;
}
