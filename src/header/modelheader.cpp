#include "modelheader.h"

#include "database/database.h"

ModelHeader::ModelHeader() {}

void ModelHeader::selectData(int userId)
{

    QString queryString = "SELECT TP.id AS tp_id, CONCAT(EY.begin_year, '-', EY.end_year) AS year_text, D.id AS d_id, "
                          "D.`name` AS d_name, P.id AS p_id, P.`name` AS p_name, U.surname AS u_sname, U.`name` AS u_name, "
                          "U.middle_name AS u_mname "
                          "FROM teacher_plan TP "
                          "INNER JOIN staff S ON TP.staff_id = S.id "
                          "INNER JOIN educational_years EY ON EY.id = TP.year_id "
                          "INNER JOIN department D ON D.id = S.department_id "
                          "INNER JOIN post P ON P.id = S.post_id "
                          "INNER JOIN `user` U ON U.id = S.user_id "
                          "WHERE S.user_id = :user_id;";
    Arguments args;
    args.insert(":user_id", userId);

    auto answer = Database::get()->selectQuery(queryString, args);
    setQuery(answer);
}
