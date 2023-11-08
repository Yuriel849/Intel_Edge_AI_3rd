#include "datasource.h"

DataSource::DataSource()
{
    conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);
}

string DataSource::findImg(string uid)
{
    string src;

    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        MYSQL_RES* result;
        MYSQL_ROW row;
        string queryStr = "SELECT img_src FROM rfid_user WHERE UID = \"" + uid + "\"";
        sprintf_s(query, 1024, queryStr.c_str());

        // Send Query
        if (mysql_query(conn, query))
        {
            cout << "SELECT Fail" << endl;
            return "";
        }

        // Get Response
        result = mysql_store_result(conn);

        int fields = mysql_num_fields(result);    // 필드 갯수 구함

        src = (string)mysql_fetch_row(result)[0];
        cout << src << endl;

        mysql_free_result(result);
        mysql_close(conn);
    }

    return src;
}

bool DataSource::exists(string uid)
{
    string exists;

    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        MYSQL_RES* result;
        MYSQL_ROW row;
        string queryStr = "SELECT EXISTS(SELECT 1 FROM rfid_user WHERE UID = \"" + uid + "\")";
        sprintf_s(query, 1024, queryStr.c_str());

        // Send Query
        if (mysql_query(conn, query))
        {
            cout << "SELECT Fail" << endl;
        }

        // Get Response
        result = mysql_store_result(conn);

        int fields = mysql_num_fields(result);    // 필드 갯수 구함
        while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
        {
            exists = (string)row[0];
        }

        mysql_free_result(result);
        mysql_close(conn);

        if (stoi(exists) != 0) { return true; }
    }

    return false;
}

//
void DataSource::getData(string uid, string& src, string& desc, string& entry_date)
{
    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        MYSQL_RES* result;
        MYSQL_ROW row;
        string queryStr = "SELECT * FROM warehouse WHERE UID = \"" + uid + "\"";
        sprintf_s(query, 1024, queryStr.c_str());

        // Send Query
        if (mysql_query(conn, query))
        {
            cout << "SELECT Fail" << endl;
        }

        // Get Response
        result = mysql_store_result(conn);

        int fields = mysql_num_fields(result);    // 필드 갯수 구함

        while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
        {
            src = (string)row[1];
            desc = (string)row[2];
            entry_date = (string)row[3];
            cout << endl;
        }

        mysql_free_result(result);
        mysql_close(conn);
    }
}

void DataSource::addUser(string uid, string src)
{
    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        MYSQL_RES* result;
        MYSQL_ROW row;
        string queryStr = "INSERT INTO rfid_user VALUES (\"" + uid + "\", 1)";
        sprintf_s(query, 1024, queryStr.c_str());

        // Send Query
        if (mysql_query(conn, query))
        {
            cout << "INSERT Fail" << endl;
        }
        else
        {
            cout << "INSERT Success" << endl;
        }

        mysql_close(conn);
    }
}

void DataSource::setEntry(string uid)
{
    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        MYSQL_RES* result;
        MYSQL_ROW row;
        string queryStr = "INSERT INTO rfid_entry_log VALUES (\"" + uid + "\", 1)";
        sprintf_s(query, 1024, queryStr.c_str());

        // Send Query
        if (mysql_query(conn, query))
        {
            cout << "INSERT Fail" << endl;
        }
        else
        {
            cout << "INSERT Success" << endl;
        }

        mysql_close(conn);
    }
}
