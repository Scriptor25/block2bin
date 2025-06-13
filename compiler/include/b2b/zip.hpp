#pragma once

#include <zip.h>

namespace b2b
{
    class Zip
    {
        class File
        {
        public:
            explicit File(zip_file_t *file);
            ~File();

            zip_int64_t Read(void *buffer, zip_uint64_t buffer_size) const;
            void Seek(zip_int64_t offset, int whence) const;
            zip_int64_t Tell() const;

        private:
            zip_file_t *m_File;
        };

        class Entry
        {
        public:
            Entry(zip_t *archive, unsigned index);

            zip_stat_t Stat() const;
            File Open() const;

        private:
            zip_t *m_Archive;
            unsigned m_Index;
        };

        class Iterator
        {
        public:
            Iterator(zip_t *archive, unsigned index);

            Iterator &operator++();
            Entry operator*() const;

            bool operator!=(const Iterator &entry) const;

        private:
            zip_t *m_Archive;
            unsigned m_Index;
        };

    public:
        explicit Zip(const char *filename);
        ~Zip();

        Iterator begin() const;
        Iterator end() const;

    private:
        zip_t *m_Archive;
        unsigned m_NumEntries;
    };
}
