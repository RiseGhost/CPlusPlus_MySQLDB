#include <iostream>
#include <vector>
#include <iomanip>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/metadata.h>
           
//https://dev.mysql.com/downloads/connector/cpp/

#define true 1
#define false 0
using namespace std;
string UserName = "root", PassWord = "25789", DataBaseName = "music";

int DBConnect(sql::Driver** diver, sql::Connection** con) {
    try {
        *diver = get_driver_instance();
        *con = (*diver)->connect("localhost", UserName, PassWord);
        return true;
    }
    catch (sql::SQLException e) {
        return false;
    }
}

vector<string> getTablesNames(sql::Connection* con, string DataBaseName) {
    vector<string> TablesNames;
    sql::ResultSet* ResulTablesName = con->prepareStatement("SELECT Table_name as TablesName from information_schema.tables where table_schema = '" + DataBaseName + "'")->executeQuery();
    while (ResulTablesName->next())
        TablesNames.push_back(ResulTablesName->getString("TablesName"));
    return TablesNames;
}

vector<string> getColumnName(sql::Connection* con, string Query) {
    vector<string> ColumnName;
    sql::ResultSetMetaData* MetaData = con->prepareStatement(Query)->executeQuery()->getMetaData();
    for (int i = 1; i <= MetaData->getColumnCount(); i++)
        ColumnName.push_back(MetaData->getColumnName(i));
    return ColumnName;
}

vector<string> getColumnType(sql::Connection* con, string Query) {
    vector<string> ColumnType;
    sql::ResultSetMetaData* MetaData = con->prepareStatement(Query)->executeQuery()->getMetaData();
    for (int i = 1; i <= MetaData->getColumnCount(); i++)
        ColumnType.push_back(MetaData->getColumnTypeName(i));
    return ColumnType;
}

int main(void) {
    sql::Driver* driver;
    sql::Connection* con;
    
    if (DBConnect(&driver, &con) == true) {
        con->setSchema(DataBaseName);

        vector<string> Column = getColumnName(con, "SELECT id, nome, senha FROM users");
        vector<string> ColumnType = getColumnType(con, "SELECT id, nome, senha FROM users");

        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT id, nome, senha FROM users");
        sql::ResultSet* result = pstmt->executeQuery();

        for (int i = 0; i < Column.size(); i++)
            cout << std::setw(10 * i) << std::right << ColumnType[i];
        cout << endl;

        for (int i = 0; i < Column.size(); i++)
            cout << std::setw(10 * i) << std::right << Column[i];
        cout << endl;

        while (result->next()){
            cout <<  result->getInt("id");
            cout << std::setw(10) << std::right << result->getString("nome");
            cout << std::setw(20) << std::right << result->getString("senha");
            cout << '\n';
        }
        con->close();
    }
    else cout << "Erro ao conectar com a base de dados\n";
    
    return 0;
}