#include "datasource.h"

void DataSource::db_connect_test()
{
    MYSQL* conn;
    MYSQL* conn_result;
    unsigned int timeout_sec = 1;

    conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

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

        sprintf_s(query, 1024, "SELECT * FROM test");

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
            for (int i = 0; i < fields; i++)    // 각각의 레코드에서 모든 필드 값 출력
            {
                cout << row[i] << "   ";
            }
            cout << endl;
        }

        mysql_free_result(result);
        mysql_close(conn);
    }

    return;
}

string DataSource::findImg(string uid)
{
    MYSQL* conn;
    MYSQL* conn_result;
    unsigned int timeout_sec = 1;
    string src;

    conn = mysql_init(NULL);
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
    conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "Springf!37D", "mysql", 3309, NULL, 0);

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
        string queryStr = "SELECT imgSrc FROM test_img WHERE UID = \"" + uid + "\"";
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