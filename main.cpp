#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <filesystem>
#include <sqlite3.h> 

using namespace std;

bool checkLogin () { // check for login validity
    string username, password, uname, pword;
    cout << "Type in your username: ";
    cin >> username;
    cout << "Type in your password: ";
    cin >> password;

    ifstream MyReadFile(username + ".txt"); // look for the username
    getline(MyReadFile, uname);
    getline(MyReadFile, pword); // read in the password from the txt

    if (uname == username && pword == password) {
        return true;
    }
    else {
        return false;
    }
}

bool checkUsername (string username) { // username validity
    if (username.length() < 3) {
        cout << "Username length must be longer than 3!";
        return false;
    }
    else {
        return true;
    }
}

bool checkPassword (string password) {
    if (password.length() < 5) { // password validity
        cout << "Password length must be longer than 5!";
        return false;
    }
    else {
        return true;
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main () {
    string status;
    cout << "Hello and welcome to our website." << endl;
    cout << "Are you a new user? Type YES. If not, type NO to login." << endl;
    cin >> status;
    string username, password;
    bool success = false;
    if (status == "yes" || status == "Yes" || status == "YES") { // register
        bool usernameStatus = false;
        bool passwordStatus = false;
        while (usernameStatus == false) {
            cout << "Type in your username: "; cin >> username;
            usernameStatus = checkUsername(username);
        }
        while (passwordStatus == false) {
            cout << "Type in your password: "; cin >> password;
            passwordStatus = checkPassword(password);
        }
        
        //cout << "Type in your password: "; cin >> password;
        ofstream file (username + ".txt");
        file << username << endl << password;

        // Allow the user to login after creating their user profile. 
        status = "no";
    }
    if (status == "no" || status == "No" || status == "NO") { // login
        bool login = checkLogin();
        if (!login) {
            cout << "Invalid login" << endl;
            //system("pause");
            //return 0;
        }
        else {
            cout << "Login successful" << endl;
            success = true;
            //system("pause");
            //return 0;
        }
    }

    // ask user if they would like to view a car, rent a car, or return a car. 

    // to view the list:
/*     ifstream car("Vehicles.txt");
    if (car.is_open()) {
        cout << "Car ID---Car Name---Availability";
        cout << car.rdbuf();
    }
    else {
        cout << "Error opening the vehicle list.";
    }

    // to rent a car:
    string carID = "001";
    int num = stoi(carID); */
    
    /* string option;
    cout << "Would you like to view (1), rent a car (2), or return a car (3)?"; cin >> option;

    if (option == "1") {
        string path = "Vehicles";
            for (const auto & entry : filesystem::directory_iterator(path)) {
                std::cout << entry.path() << std::endl;
            }
    }

    if (option == "2") {
        string name;
        cout << "Type in the vehicle name."; cin >> name;
        
    }
 */

/*     sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    //const char* sql[];

    /* Open database 
    rc = sqlite3_open("vehicles.db", &db);
   
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
    fprintf(stdout, "Opened database successfully\n");
    }

    /* Create SQL statement 
    const char *sql = "INSERT INTO vehicles VALUES (1, 'test', 1);";

    /* Execute SQL statement 
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db);
*/

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("vehicles.db", &db);
    
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
    fprintf(stdout, "Opened database successfully\n");
    }

    sqlite3_stmt* stmt;
    const char* sql_stmt = "SELECT * FROM vehicles";
    rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%s %s %s\n", sqlite3_column_text(stmt, 0), sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2));
    }

    return 0;
    //g++ main.cpp -lsqlite3
}
