#include "DataProcessor.hpp"

#include <cctype>
#include <stdexcept>

std::string DataProcessor::trim(const std::string& value) {
    std::size_t start = 0;
    while (start < value.size() &&
           std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }

    std::size_t end = value.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    return value.substr(start, end - start);
}

DataProcessor::Table DataProcessor::cleanRows(const Table& table) {
    Table cleaned;

    for (const auto& row : table) {
        std::vector<std::string> cleanedRow;
        bool hasValue = false;

        for (const auto& cell : row) {
            std::string value = trim(cell);
            if (!value.empty()) {
                hasValue = true;
            }
            cleanedRow.push_back(value);
        }

        if (hasValue) {
            cleaned.push_back(cleanedRow);
        }
    }

    return cleaned;
}

std::vector<std::string> DataProcessor::getColumn(
    const Table& table,
    std::size_t columnIndex,
    bool skipHeader
) {
    std::vector<std::string> column;

    std::size_t startRow = skipHeader ? 1 : 0;

    for (std::size_t row = startRow; row < table.size(); ++row) {
        if (columnIndex < table[row].size()) {
            column.push_back(trim(table[row][columnIndex]));
        }
    }

    return column;
}

std::vector<double> DataProcessor::toNumeric(
    const std::vector<std::string>& values,
    bool ignoreInvalid
) {
    std::vector<double> numeric;

    for (const auto& raw : values) {
        std::string value = trim(raw);

        if (value.empty()) {
            if (ignoreInvalid) {
                continue;
            }
            throw std::invalid_argument("Empty value cannot be converted to a number.");
        }

        try {
            std::size_t used = 0;
            double number = std::stod(value, &used);

            if (used != value.size()) {
                throw std::invalid_argument("Extra characters after number.");
            }

            numeric.push_back(number);
        } catch (const std::exception&) {
            if (!ignoreInvalid) {
                throw std::invalid_argument("Invalid numeric value: " + value);
            }
        }
    }

    return numeric;
}
