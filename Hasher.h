#ifndef TASKWA_HASHER_H
#define TASKWA_HASHER_H

#include <string>
#include <memory>
#include <vector>
#include <mutex>

struct Crc {
    uint32_t value;
    size_t counter;
    bool operator<(const Crc &rhs)
    {
        return counter < rhs.counter;
    }
};

class Hasher {
public:
    Hasher(const std::string &aIn, const std::string &aOut, size_t aBlockSize);
    ~Hasher() = default;

    void run();
protected:
private:

    std::string m_inFileName;
    std::string m_outFileName;

    size_t m_blockSize;

    using FilePtr = std::unique_ptr<FILE, decltype(&fclose)>;
    FilePtr m_inFile;
    FilePtr m_outFile;

    using DataType = std::vector<uint8_t> ;
    std::mutex m_lock;
    std::vector<Crc> m_resultData;

    void dropResult();
};


#endif //TASKWA_HASHER_H
