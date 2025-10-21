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
            [[nodiscard]] zip_int64_t Tell() const;

        private:
            zip_file_t *m_File;
        };

        class Entry
        {
        public:
            Entry(zip_t *archive, unsigned index);

            [[nodiscard]] zip_stat_t Stat() const;
            [[nodiscard]] File Open() const;

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

        explicit operator bool() const;

        [[nodiscard]] Iterator begin() const;
        [[nodiscard]] Iterator end() const;

    private:
        int m_Error = 0;
        zip_t *m_Archive = nullptr;
        unsigned m_NumEntries = 0u;
    };
}
