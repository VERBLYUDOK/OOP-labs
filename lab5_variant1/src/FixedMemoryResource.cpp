#include "FixedMemoryResource.h"

FixedMemoryResource::FixedMemoryResource(size_t totalSize) 
    : _totalSize(totalSize), _offset(0) {
    _memoryStart = ::operator new(_totalSize);
}

FixedMemoryResource::~FixedMemoryResource() {
    ::operator delete(_memoryStart);
}

void* FixedMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    // Сначала ищем подходящий свободный блок
    for (auto it = _freeBlocks.begin(); it != _freeBlocks.end(); ++it) {
        if (it->size >= bytes) {
            void* ptr = it->address;
            _freeBlocks.erase(it);
            return ptr;
        }
    }

    size_t space = _totalSize - _offset;
    void* ptr = static_cast<char*>(_memoryStart) + _offset;

    size_t alignmentOffset = reinterpret_cast<size_t>(ptr);
    size_t adjusment = alignment - (alignmentOffset % alignment);
    if (adjusment == alignment) {
        adjusment = 0;
    }

    if (bytes + adjusment > space) {
        throw std::bad_alloc();
    }

    _offset += adjusment;
    ptr = static_cast<char*>(ptr) + adjusment;
    _offset += bytes;
    return ptr;
}

void FixedMemoryResource::do_deallocate(void* p, size_t bytes, size_t alignment) {
    _freeBlocks.push_back({p, bytes});
}

bool FixedMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}