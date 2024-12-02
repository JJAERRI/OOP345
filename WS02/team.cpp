#include "team.h"
#include <iostream>
#include <iomanip>

namespace seneca {

    // �⺻ ������
    Team::Team() : m_name("No team"), m_members(nullptr), m_count(0) {}

    // �̸��� �޾� �ʱ�ȭ�ϴ� ������
    Team::Team(const char* name) : m_name(name), m_members(nullptr), m_count(0) {}

    // �Ҹ���
    Team::~Team() {
        deallocate();
    }

    // �޸� ���� �Լ�
    void Team::deallocate() {
        for (size_t i = 0; i < m_count; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
        m_members = nullptr;
        m_count = 0;
    }

    // ���� ������
    Team::Team(const Team& other) : m_members(nullptr), m_count(0) {
        copyFrom(other);
    }

    // ���� ���� ������
    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            deallocate();
            copyFrom(other);
        }
        return *this;
    }

    // �̵� ������
    Team::Team(Team&& other) noexcept : m_members(nullptr), m_count(0) {
        moveFrom(std::move(other));
    }

    // �̵� ���� ������
    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            deallocate();
            moveFrom(std::move(other));
        }
        return *this;
    }

    // ���� �� �̵� ���� �Լ�
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

    // ��� �߰�
    void Team::addMember(const Character* c) {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;  // �̹� ���� �̸��� ����� ����
            }
        }
        Character** temp = new Character * [m_count + 1];
        for (size_t i = 0; i < m_count; ++i) {
            temp[i] = m_members[i];
        }
        temp[m_count] = c->clone();  // ��� ����
        delete[] m_members;
        m_members = temp;
        ++m_count;
    }

    // ��� ����
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

    // ��� �˻� (�ε����� ����)
    Character* Team::operator[](size_t idx) const {
        return (idx < m_count) ? m_members[idx] : nullptr;
    }

    // ��� ���
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
