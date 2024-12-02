#include "team.h"
#include <iostream>
#include <iomanip>

namespace seneca {

    // 기본 생성자
    Team::Team() : m_name("No team"), m_members(nullptr), m_count(0) {}

    // 이름을 받아 초기화하는 생성자
    Team::Team(const char* name) : m_name(name), m_members(nullptr), m_count(0) {}

    // 소멸자
    Team::~Team() {
        deallocate();
    }

    // 메모리 해제 함수
    void Team::deallocate() {
        for (size_t i = 0; i < m_count; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
        m_members = nullptr;
        m_count = 0;
    }

    // 복사 생성자
    Team::Team(const Team& other) : m_members(nullptr), m_count(0) {
        copyFrom(other);
    }

    // 복사 대입 연산자
    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            deallocate();
            copyFrom(other);
        }
        return *this;
    }

    // 이동 생성자
    Team::Team(Team&& other) noexcept : m_members(nullptr), m_count(0) {
        moveFrom(std::move(other));
    }

    // 이동 대입 연산자
    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            deallocate();
            moveFrom(std::move(other));
        }
        return *this;
    }

    // 복사 및 이동 보조 함수
    void Team::copyFrom(const Team& other) {
        m_name = other.m_name;
        m_members = new Character * [other.m_count];
        m_count = other.m_count;
        for (size_t i = 0; i < m_count; ++i) {
            m_members[i] = other.m_members[i]->clone();
        }
    }

    void Team::moveFrom(Team&& other) {
        m_name = std::move(other.m_name);
        m_members = other.m_members;
        m_count = other.m_count;

        other.m_members = nullptr;
        other.m_count = 0;
    }

    // 멤버 추가
    void Team::addMember(const Character* c) {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;  // 이미 같은 이름의 멤버가 있음
            }
        }
        Character** temp = new Character * [m_count + 1];
        for (size_t i = 0; i < m_count; ++i) {
            temp[i] = m_members[i];
        }
        temp[m_count] = c->clone();  // 멤버 복사
        delete[] m_members;
        m_members = temp;
        ++m_count;
    }

    // 멤버 제거
    void Team::removeMember(const std::string& name) {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == name) {
                delete m_members[i];
                for (size_t j = i; j < m_count - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_count;
                return;
            }
        }
    }

    // 멤버 검색 (인덱스로 접근)
    Character* Team::operator[](size_t idx) const {
        return (idx < m_count) ? m_members[idx] : nullptr;
    }

    // 멤버 출력
    void Team::showMembers() const {
        if (m_name.empty() && m_count == 0)
            std::cout << "No team." << std::endl;
        else {
            std::cout << "[Team] " << m_name << std::endl;
            for (size_t i = 0; i < m_count; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_members[i]) << std::endl;
            }
        }
    }

} // namespace seneca
