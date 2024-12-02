#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>

namespace seneca {

    class Team {
        std::string m_name;
        Character** m_members;
        size_t m_count;

        // 메모리 관리 함수
        void deallocate();
        void copyFrom(const Team& other);
        void moveFrom(Team&& other);

    public:
        // 기본 생성자
        Team();

        // 이름을 받아 초기화하는 생성자
        Team(const char* name);

        // Rule of 5: 소멸자, 복사 생성자, 복사 대입 연산자, 이동 생성자, 이동 대입 연산자
        ~Team();
        Team(const Team& other);
        Team(Team&& other) noexcept;
        Team& operator=(const Team& other);
        Team& operator=(Team&& other) noexcept;

        // 멤버 추가
        void addMember(const Character* c);

        // 멤버 제거
        void removeMember(const std::string& name);

        // 멤버 검색 (인덱스로 접근)
        Character* operator[](size_t idx) const;

        // 멤버 출력
        void showMembers() const;
    };

} // namespace seneca

#endif
