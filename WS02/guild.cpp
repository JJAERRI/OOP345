#include "guild.h"
#include <iomanip>

namespace seneca {

    // 기본 생성자
    Guild::Guild() : m_name(""), m_members(nullptr), m_count(0) {}

    // 이름을 받아 초기화하는 생성자
    Guild::Guild(const char* name) : m_name(name), m_members(nullptr), m_count(0) {}

    // 복사 보조 함수
    void Guild::copyFrom(const Guild& src) {
        m_name = src.m_name;
        m_count = src.m_count;
        m_members = new Character * [m_count];
        for (size_t i = 0; i < m_count; ++i) {
            m_members[i] = src.m_members[i]; 
        }
    }

    // 복사 생성자
    Guild::Guild(const Guild& src) {
        copyFrom(src);
    }

    // 복사 대입 연산자
    Guild& Guild::operator=(const Guild& src) {
        if (this != &src) {
            delete[] m_members;  // 기존 메모리 해제
            copyFrom(src);
        }
        return *this;
    }

    // 이동 보조 함수
    void Guild::moveFrom(Guild&& src) noexcept {
        m_name = std::move(src.m_name);
        m_members = src.m_members;
        m_count = src.m_count;

        // 이동 후 원본 객체 초기화
        src.m_members = nullptr;
        src.m_count = 0;
    }

    // 이동 생성자
    Guild::Guild(Guild&& src) noexcept {
        moveFrom(std::move(src));
    }

    // 이동 대입 연산자
    Guild& Guild::operator=(Guild&& src) noexcept {
        if (this != &src) {
            delete[] m_members;
            moveFrom(std::move(src));
        }
        return *this;
    }

    // 소멸자
    Guild::~Guild() {
        delete[] m_members;
    }

    // 멤버 찾기 함수
    int Guild::findMember(const std::string& name) {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // 멤버 추가
    void Guild::addMember(Character* c) {
        if (findMember(c->getName()) == -1) {  // 중복 방지
            c->setHealthMax(c->getHealthMax() + 300);  // 최대 체력 증가
            c->setHealth(c->getHealthMax());  // 현재 체력도 최대 체력으로 설정

            // 배열 크기 증가 및 멤버 추가
            Character** newMembers = new Character * [m_count + 1];
            for (size_t i = 0; i < m_count; ++i) {
                newMembers[i] = m_members[i];
            }
            newMembers[m_count] = c;
            delete[] m_members;
            m_members = newMembers;
            ++m_count;
        }
    }

    // 멤버 제거
    void Guild::removeMember(const std::string& name) {
        int idx = findMember(name);
        if (idx != -1) {
            m_members[idx]->setHealthMax(m_members[idx]->getHealthMax() - 300);  // 체력 감소
            m_members[idx]->setHealth(m_members[idx]->getHealthMax());

            // 배열에서 멤버 제거
            for (size_t i = idx; i < m_count - 1; ++i) {
                m_members[i] = m_members[i + 1];
            }
            --m_count;
        }
    }

    // 멤버 접근 연산자
    Character* Guild::operator[](size_t idx) const {
        return (idx < m_count) ? m_members[idx] : nullptr;
    }

    // 멤버 출력
    void Guild::showMembers() const {
        if (m_name.empty() && m_count == 0)
            std::cout << "No guild." << std::endl;
        else {
            std::cout << "[Guild] " << m_name << std::endl;
            for (size_t i = 0; i < m_count; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_members[i]) << std::endl;
            }
        }
    }
}
