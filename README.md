# C++ MYSQL DataBase connect:
## Project Info ℹ️:

- Name:         C++_MySQLDB
- Author:       RiseGhost 👻
- Language:     C++

Este projeto como objetivo uma implementação de low level de uma conexão com uma base de dados MySQL.

**Main file: C++_MySQLDB.cpp**

## Install MySQL drives:
Para fazer a conexão com a base de dados é necessário ter os drives do MySQL. E adiciona-los como bibliotecas externas ao projeto.

Os drives podem ser entrados no seguinte link:
https://dev.mysql.com/downloads/connector/cpp/

A configuração no Visual Studio Code deverá ficar algo parecido com:

![](https://user-images.githubusercontent.com/91985039/242590218-0bf99dd5-5fae-4368-9247-5b60dbe522a8.jpg)

![](https://user-images.githubusercontent.com/91985039/242590224-4da218fa-bed6-4be4-83fa-837d0891f48f.jpg)

![](https://user-images.githubusercontent.com/91985039/242590232-772d3ef3-aec5-4711-a7a3-0ae00d31001e.jpg)

Vou disponibelizar os drives que utilizei neste repositório dentro da pasta __mysql-connector-c++-8.0.33-winx64__.

## Functionalities:

As funcionalidade do código são:
- Fazer Querys a base de dados;
- Obter os nomes das tabelas de uma base de dados;
- Obter os nomes das colunas de um tabela;
- Obter os tipos de dados de uma coluna.

## How to acess column data 📝:
Para conseguir obter os dados das colunas é necessário instanciar um objeto do tipo __sql::ResultSet*__. 

Após isso basta fazer um __result.getDataType(Column Name)__.

Por exemplo:

__Table:__

|   id   |   nome    |   senha   |
|  :---  |  :---:    |   ---:    |
|   1    |  admin    |   admin   |
|  43    |  banana   |   banana  |
|  46    |  ferro    |   gg      |
|  47    |  Jose     |   25789   |

__Code:__

```cpp
int main(void) {
    sql::Driver* driver;
    sql::Connection* con;
    string DataBaseName = "music";
    
    if (DBConnect(&driver, &con) == true) {
        con->setSchema(DataBaseName);

        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT id, nome, senha FROM users");
        sql::ResultSet* result = pstmt->executeQuery();

        while (result->next()){ //Fica a ler enquando houver dados
            cout << result->getInt("id")        << endl;
            cout << result->getString("nome")   << endl;
            cout << result->getString("senha")  << endl;
            cout << '\n';
        }
        con->close();
    }
    else cout << "Erro ao conectar com a base de dados\n";
    
    return 0;
}
```

É possível fazer um getString(Column Name) para uma coluna que tem um número.

## Output:

![](https://user-images.githubusercontent.com/91985039/242590237-14ed67b7-8312-4a10-ad37-4884a643fe31.jpg)
