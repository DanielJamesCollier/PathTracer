#ifndef MutexPrint_hpp
#define MutexPrint_hpp

#include <sstream>
#include <mutex>

/** Thread safe cout class
  * Exemple of use:
  *    MutexPrint{} << "Hello world!" << std::endl;
  */
class MutexPrint: public std::ostringstream
{
public:
    MutexPrint() = default;

    ~MutexPrint() {
        std::lock_guard<std::mutex> guard(sm_mutexPrint);
        std::cout << this->str();
    }

private:
    static std::mutex sm_mutexPrint;
};

std::mutex MutexPrint::sm_mutexPrint{};

#endif /* MutexPrint_hpp */