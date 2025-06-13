#include <iostream>
#include <b2b/zip.hpp>

b2b::Zip::File::File(zip_file_t *file)
    : m_File(file)
{
}

b2b::Zip::File::~File()
{
    zip_fclose(m_File);
}

zip_int64_t b2b::Zip::File::Read(void *buffer, const zip_uint64_t buffer_size) const
{
    const auto count = zip_fread(m_File, buffer, buffer_size);

    if (count < 0)
    {
        const auto error = zip_file_get_error(m_File);
        std::cerr << error->str << std::endl;
    }

    return count;
}

void b2b::Zip::File::Seek(const zip_int64_t offset, const int whence) const
{
    if (zip_fseek(m_File, offset, whence) < 0)
    {
        const auto error = zip_file_get_error(m_File);
        std::cerr << error->str << std::endl;
    }
}

zip_int64_t b2b::Zip::File::Tell() const
{
    const auto pos = zip_ftell(m_File);

    if (pos < 0)
    {
        const auto error = zip_file_get_error(m_File);
        std::cerr << error->str << std::endl;
    }

    return pos;
}

b2b::Zip::Entry::Entry(zip_t *archive, const unsigned index)
    : m_Archive(archive),
      m_Index(index)
{
}

zip_stat_t b2b::Zip::Entry::Stat() const
{
    zip_stat_t stat;
    zip_stat_index(m_Archive, m_Index, 0, &stat);
    return stat;
}

b2b::Zip::File b2b::Zip::Entry::Open() const
{
    const auto file = zip_fopen_index(m_Archive, m_Index, ZIP_RDONLY);

    if (!file)
    {
        const auto error = zip_get_error(m_Archive);
        std::cerr << error->str << std::endl;
    }

    return File(file);
}

b2b::Zip::Iterator::Iterator(zip_t *archive, const unsigned index)
    : m_Archive(archive),
      m_Index(index)
{
}

b2b::Zip::Iterator &b2b::Zip::Iterator::operator++()
{
    m_Index++;
    return *this;
}

b2b::Zip::Entry b2b::Zip::Iterator::operator*() const
{
    return Entry(m_Archive, m_Index);
}

bool b2b::Zip::Iterator::operator!=(const Iterator &entry) const
{
    return m_Archive != entry.m_Archive || m_Index != entry.m_Index;
}

b2b::Zip::Zip(const char *filename)
{
    m_Archive = zip_open(filename, ZIP_RDONLY, nullptr);
    m_NumEntries = zip_get_num_entries(m_Archive, 0);
}

b2b::Zip::~Zip()
{
    zip_close(m_Archive);
    m_Archive = nullptr;
    m_NumEntries = 0;
}

b2b::Zip::Iterator b2b::Zip::begin() const
{
    return Iterator(m_Archive, 0);
}

b2b::Zip::Iterator b2b::Zip::end() const
{
    return Iterator(m_Archive, m_NumEntries);
}
