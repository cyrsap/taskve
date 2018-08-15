#include "Hasher.h"
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/crc.hpp>


static int customCloseFile(FILE *aFile) {
    if (aFile) {
        return fclose(aFile);
    }
    return 0;
}

Hasher::Hasher(const std::string &aIn, const std::string &aOut, size_t aBlockSize)
    : m_inFileName(aIn)
    , m_outFileName(aOut)
    , m_blockSize(aBlockSize)
    , m_inFile(nullptr, &customCloseFile)
    , m_outFile(nullptr, &customCloseFile)
{}

void Hasher::run()
{
    boost::asio::thread_pool pool;

    boost::asio::post(pool, [](){});

}
