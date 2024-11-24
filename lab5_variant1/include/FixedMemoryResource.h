#ifndef MEMORY_RESOURCE_H
#define MEMORY_RESOURCE_H

#include <memory_resource>
#include <list>

class FixedMemoryResource : public std::pmr::memory_resource {
private:
    size_t _totalSize;
    void* _memoryStart;
    size_t _offset;

    struct Block {
        void* address;
        size_t size;
    };
    std::list<Block> _freeBlocks;

public:
    explicit FixedMemoryResource(size_t);
    ~FixedMemoryResource();

protected:
    void* do_allocate(size_t, size_t) override;
    void do_deallocate(void*, size_t, size_t) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif