#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include <string>
#include <vector>

class DataLoader {
public:
    using Row = std::vector<std::string>;
    using Table = std::vector<Row>;

    static Table loadCSV(const std::string& filePath, char delimiter = ',');
};

#endif
