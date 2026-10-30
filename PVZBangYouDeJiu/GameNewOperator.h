#ifndef GAME_NEW_OPERATOR_H
#define GAME_NEW_OPERATOR_H
#include <stdint.h>

inline void* operator new(size_t size) {
auto op_new_game = (void* (_cdecl*)(unsigned int _Size))0x61C130;
return op_new_game(size);
}

inline void operator delete(void* ptr) noexcept {
    // 假设游戏中对应的释放函数为 GameFree
    auto op_delete_game = (void(_cdecl*)(void* _Block))0x61C19A;
    return op_delete_game(ptr);
}

// 数组版本 - 直接调用普通版本
inline void* operator new[](size_t size) {
    return operator new(size);  // 复用普通 new 的逻辑
}

inline void operator delete[](void* ptr) noexcept {
    operator delete(ptr);       // 复用普通 delete 的逻辑
}

#endif

