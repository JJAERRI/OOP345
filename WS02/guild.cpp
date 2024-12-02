#include "guild.h"
#include <iomanip>

namespace seneca {

    // �⺻ ������
    Guild::Guild() : m_name(""), m_members(nullptr), m_count(0) {}

    // �̸��� �޾� �ʱ�ȭ�ϴ� ������
    Guild::Guild(const char* name) : m_name(name), m_members(nullptr), m_count(0) {}

    // ���� ���� �Լ�
    void Guild::copyFrom(const Guild& src) {
        m_name = src.m_name;
        m_count = src.m_count;
        m_members = new Character * [m_count];
        for (size_t i = 0; i < m_count; ++i) {
            m_members[i] = src.m_members[i]; 
        }
    }

    // ���� ������
    Guild::Guild(const Guild& src) {
        copyFrom(src);
    }

    // ���� ���� ������
    Guild& Guild::operator=(const Guild& src) {
        if (this != &src) {
            delete[] m_members;  // ���� �޸� ����
            copyFrom(src);
        }
        return *this;
    }

    // �̵� ���� �Լ�
    void Guild::moveFrom(Guild&& src) noexcept {
        m_name = std::move(src.m_name);
        m_members = src.m_members;
        m_count = src.m_count;

        // �̵� �� ���� ��ü �ʱ�ȭ
        src.m_members = nullptr;
        src.m_count = 0;
    }

    // �̵� ������
    Guild::Guild(Guild&& src) noexcept {
        moveFrom(std::move(src));
    }

    // �̵� ���� ������
    Guild& Guild::operator=(Guild&& src) noexcept {
        if (this != &src) {
            delete[] m_members;
            moveFrom(std::move(src));
        }
        return *this;
    }

    // �Ҹ���
    Guild::~Guild() {
        delete[] m_members;
    }

    // ��� ã�� �Լ�
    int Guild::findMember(const std::string& name) {
        for (size_t i = 0; i < m_count; ++i) {
            if (m_members[i]->getName() == name) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // ��� �߰�
    void Guild::addMember(Character* c) {
        if (findMember(c->getName()) == -1) {  // �ߺ� ����
            c->setHealthMax(c->getHealthMax() + 300);  // �ִ� ü�� ����
            c->setHealth(c->getHealthMax());  // ���� ü�µ� �ִ� ü������ ����

            // �迭 ũ�� ���� �� ��� �߰�
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

    // ��� ����
    void Guild::removeMember(const std::string& name) {
        int idx = findMember(name);
        if (idx != -1) {
            m_members[idx]->setHealthMax(m_members[idx]->getHealthMax() - 300);  // ü�� ����
            m_members[idx]->setHealth(m_members[idx]->getHealthMax());

            // �迭���� ��� ����
            for (size_t i = idx; i < m_count - 1; ++i) {
                m_members[i] = m_members[i + 1];
            }
            --m_count;
        }
    }

    // ��� ���� ������
    Character* Guild::operator[](size_t idx) const {
        return (idx < m_count) ? m_members[idx] : nullptr;
    }

    // ��� ���
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
