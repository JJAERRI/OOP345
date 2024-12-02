#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <iostream>
#include <string>
#include "character.h"

namespace seneca {
    class Guild {
        std::string m_name;
        Character** m_members;
        size_t m_count;

        void copyFrom(const Guild& src);  // 복사 보조 함수
        void moveFrom(Guild&& src) noexcept;  // 이동 보조 함수
        int findMember(const std::string& name);  // 멤버 찾기 함수

    public:
        Guild();  // 기본 생성자
        Guild(const char* name);  // 이름으로 초기화하는 생성자
        Guild(const Guild& src);  // 복사 생성자
        Guild& operator=(const Guild& src);  // 복사 대입 연산자
        Guild(Guild&& src) noexcept;  // 이동 생성자
        Guild& operator=(Guild&& src) noexcept;  // 이동 대입 연산자
        ~Guild();  // 소멸자

        void addMember(Character* c);  // 멤버 추가
        void removeMember(const std::string& name);  // 멤버 제거
        Character* operator[](size_t idx) const;  // 멤버 접근 연산자
        void showMembers() const;  // 멤버 출력
    };
}

#endif
