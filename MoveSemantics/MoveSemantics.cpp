
#include <iostream>

class String {
public:
    String() = default;
    String(const char* string)
    {
        printf("Created!\n");
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }
    String(const String& other)
    {
        printf("Copied!\n");
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }
    String(String&& other) noexcept
    {
        printf("Moved!\n");
        m_Size = other.m_Size;
        m_Data = other.m_Data;

        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    String& operator=(String&& other) noexcept
    {
        printf("Move assignment!\n");
        if (this != &other)
        {
            delete[] m_Data;

            m_Size = other.m_Size;
            m_Data = other.m_Data;

            other.m_Size = 0;
            other.m_Data = nullptr;
        }
        return *this;
    }
        
    void printName()
    {
        for (uint32_t i = 0; i < m_Size; i++)
        {
            printf("%c", m_Data[i]);
        }
        printf("\n");
    }
    ~String()
    {
        printf("Deleted!\n");
        delete m_Data;
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity {
public:
    Entity(const String& name)
        : m_Name(name) {}
    Entity(String&& name)
        : m_Name(std::move(name)) {}

    void Print()
    {
        m_Name.printName();
    }
   
private:
    String m_Name;
};
int main()
{
    Entity entity(String("Adrian"));
    entity.Print();

    String string1 = "Apple";
    String dest;

    std::cout << "Apple: ";
    string1.printName();
    std::cout << "Dest: ";
    dest.printName();

    dest = std::move(string1);

    std::cout << "Apple: ";
    string1.printName();
    std::cout << "Dest: ";
    dest.printName();

    std::cin.get();
}

