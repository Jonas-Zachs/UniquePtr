#include <iostream>

template<typename T>
class UniquePtr {
private:
    T* m_ptr; // raw pointer that owns the managed object

public:
    // explicit single-argument constructor to avoid implicit conversions.
    // noexcept because construction won't throw.
    explicit UniquePtr(T* p = nullptr) noexcept : m_ptr(p) {}

    // destructor: deletes the owned object (if any).
    ~UniquePtr() {
        delete m_ptr;
    }

    // copy operations are deleted: UniquePtr is move-only.
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // move constructor: take ownership from `other` and leave it null.
    UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    // move assignment: clean up current resource, take ownership from other.
    // self-assignment check is performed.
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete m_ptr;           // free current resource
            m_ptr = other.m_ptr;    // steal other's pointer
            other.m_ptr = nullptr;  // leave other empty
        }
        return *this;
    }

    // dereference operator: returns reference to managed object.
    T& operator*() const {
        return *m_ptr;
    }

    // member access operator: returns the raw pointer so callers can use ->.
    T* operator->() const {
        return m_ptr;
    }

    // return the raw pointer without changing ownership.
    T* get() const noexcept {
        return m_ptr;
    }

    // replace the managed object with p (default null).
    // deletes the old object unless p is the same pointer (prevents double-delete).
    void reset(T* p = nullptr) noexcept {
        if (m_ptr != p) {
            delete m_ptr;
            m_ptr = p;
        }
    }

    // release ownership and return the raw pointer; leave this UniquePtr empty.
    T* release() noexcept {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }
};

struct Foo {
    int x;
    Foo(int val) : x(val) {}
    void display() {
        printf("Foo: %d\n", x);
    }
};

int main() {
    // create a UniquePtr that owns a new Foo(42)
    UniquePtr<Foo> ptr1(new Foo(42));
    ptr1->display();

    // move ownership from ptr1 to ptr2; ptr1 becomes null
    UniquePtr<Foo> ptr2 = std::move(ptr1);
    if (!ptr1.get()) {
        printf("ptr1 is now null after move.\n");
    }

    ptr2->display();

    // create another UniquePtr and then move-assign from ptr2
    UniquePtr<Foo> ptr3(new Foo(43));

	ptr3->display();

    ptr3 = std::move(ptr2);

    ptr3->display();
}