#ifndef TASKWA_HASHER_H
#define TASKWA_HASHER_H

#include <string>
#include <memory>

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
};


#endif //TASKWA_HASHER_H
