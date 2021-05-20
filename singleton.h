#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class singleton {
public:
    template<class ...ARGS>
    static T &instance(ARGS ...args) {
        static T obj(args...);
        return obj;
    }
protected:
    singleton() = default;
    ~singleton() = default;
};

#define singleton_class(classname) friend class singleton<classname>

#endif // SINGLETON_H
