#include "datasource.h"

string DataSource::findImg(string uid, string& time)
{
    string src;

    MYSQL* conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    MYSQL* conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);
    
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
        string queryStr = "SELECT img_src, NOW() FROM rfid_user WHERE UID = \"" + uid + "\"";
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

        while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
        {
            src = (string)row[0];
            time = (string)row[1];
        }

        mysql_free_result(result);
        mysql_close(conn);
    }

    return src;
}

bool DataSource::exists(string uid)
{
    string exists;

    MYSQL* conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    MYSQL* conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

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

bool DataSource::isActive(string uid)
{
    string exists;

    MYSQL* conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    MYSQL* conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

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
        string queryStr = "SELECT active FROM rfid_user WHERE uid = \"" + uid + "\"";
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

        if (stoi(exists) == 1) { return true; }
    }

    return false;
}

void DataSource::addUser(string uid, string src)
{
    MYSQL* conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    MYSQL* conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        string queryStr = "INSERT INTO rfid_user SET uid = \"" + uid + "\", img_src = \"" + src + "\"";
        sprintf_s(query, 1024, queryStr.c_str());
        std::cout << query << std::endl;
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
    MYSQL* conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    MYSQL* conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        string queryStr = "INSERT INTO rfid_entry_log SET uid = \"" + uid + "\"";
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

void DataSource::deactivate(string uid)
{
    MYSQL* conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    MYSQL* conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

    if (NULL == conn_result)
    {
        cout << "DB Connection Fail" << endl;
    }
    else
    {
        cout << "DB Connection Success" << endl;

        char query[1024];
        string queryStr = "UPDATE rfid_user SET active = 0 WHERE uid = \"" + uid + "\"";
        sprintf_s(query, 1024, queryStr.c_str());

        // Send Query
        if (mysql_query(conn, query))
        {
            cout << "DEACTIVATE Fail" << endl;
        }
        else
        {
            cout << "DEACTIVATE Success" << endl;
        }

        mysql_close(conn);
    }
}