#include "DBConnector.h"

DBConnector::DBConnector()
{
    Driver = get_driver_instance();
}

DBConnector::~DBConnector()
{

}

bool DBConnector::Connect(const string& Server, const string& User, const string& Password, const int& Port)

{
    try
    {
        Con = Driver->connect(Server + ":" + std::to_string(Port), User, Password);
        Stmt = Con->createStatement();

        cout << "[DB] ���� ����" << endl;
        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "[DB] ���� : ";
        cout << e.what() << endl;
        return false;
    }

    return true;
}

void DBConnector::Close()
{
    Con->close();
}

bool DBConnector::SearchAccount(const string& Id, const string& Password)
{
    string sql = "SELECT * FROM `UserAccount`.`UserInfo` WHERE `Id` = '";
    sql += Id + "' and `Pw` = '" + Password + "'";

    try
    {
        Res = Stmt->executeQuery(sql);
        if (Res->next())
        {
            cout << "Id = " << Res->getString("Id") << endl;
            cout << "Pw = " << Res->getString("Pw") << endl;

            return true;
        }
        else
        {
            cout << "[DB] �ش� ���� �������� ����" << endl;
        return false;
        }
    mysql_free_result(Res);

    return bResult;
}

bool DBConnector::SignUpAccount(const string& Id, const string& Password)
{
    string sql = "SELECT * FROM `UserAccount`.`UserInfo` WHERE `Id` = '";
    sql += Id + "'";

    Res = Stmt->executeQuery(sql);
    if (Res->next())
    {
       
        cout << "[DB] �̹� �����ϴ� ���̵� : " << Res->getString("Id") << endl;
        return false;
    }

    else
    {
        sql = "INSERT INTO `UserAccount`.`UserInfo` (`Id`, `Pw`) VALUES ('";
        sql += Id + "', '" + Password + "')";

        Stmt->executeUpdate(sql);
        return true;
    }
}
bool DBConnector::SetUserData(const int& difficulty, const int& stage, const int& key)
{
    string sql = "SELECT * FROM `UserAccount`.`UserInfo` (`Key`) VALUES ('";
    sql += to_string(key) + "')";

    Res = Stmt->executeQuery(sql);

    if (Res->next())
    {
        sql = "INSERT INTO `UserAccount`.`UserInfo` (`Difficulty`, `Stage`) VALUES ('";
        sql += to_string(difficulty) + "', '" + to_string(stage) + "')";

        Stmt->executeUpdate(sql);
        cout << "[DB] ������ �Է� ����" << endl;

        return true;
    }

    else cout << "[DB] �ش� ���� ���� {KEY = " << key << "}" << endl;
    return false;
}

int DBConnector::GetDifficulty(const string& Id)
{
    string sql = "SELECT * FROM `UserAccount`.`UserInfo` WHERE `Id` = '";
    sql += Id + "'";

    Res = Stmt->executeQuery(sql);

    if (Res->next())
    {
        return Res->getInt("Difficulty");
    }

    return 0;
}

int DBConnector::GetStage(const string& Id)
{
    string sql = "SELECT * FROM `UserAccount`.`UserInfo` WHERE `Id` = '";
    sql += Id + "'";

    Res = Stmt->executeQuery(sql);

    if (Res->next())
    {
        return Res->getInt("Stage");
    }

    return 0;
}

int DBConnector::GetKey(const string& Id)
{
    string sql = "SELECT * FROM `UserAccount`.`UserInfo` WHERE `Id` = '";
    sql += Id + "'";

    Res = Stmt->executeQuery(sql);

    if (Res->next())
    {
        return Res->getInt("Key");
    }

    return 0;
}