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
    boost::asio::thread_pool pool(std::thread::hardware_concurrency());

    m_inFile.reset(fopen64(m_inFileName.c_str(), "r"));
    if (!m_inFile) {
        throw std::runtime_error("Can't open input file");
    }
    m_outFile.reset(fopen64(m_outFileName.c_str(), "w"));
    if (!m_outFile) {
        throw std::runtime_error("Can't open output file");
    }

    size_t counter = 0;
    while (!feof(m_inFile.get())) {
        std::vector<uint8_t> data(m_blockSize);
        auto dataRead = fread(data.data(), 1, m_blockSize, m_inFile.get());
        boost::asio::post(pool, [&, aData{std::move(data)}, counter, dataRead] {
            boost::crc_32_type crc;
            crc.process_bytes(aData.data(), dataRead);
            uint32_t cs = crc.checksum();
            std::lock_guard guard(m_lock);
            m_resultData.push_back({cs, counter});
        });
        counter++;
    }

    pool.join();

    dropResult();
}

void Hasher::dropResult()
{
    std::sort(m_resultData.begin(), m_resultData.end());

    for (auto &elem : m_resultData) {
        fwrite(&elem.value, sizeof(elem.value), 1, m_outFile.get());
    }
}
