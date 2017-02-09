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
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cout << this->str();
    }

private:
    static std::mutex _mutexPrint;
};

std::mutex MutexPrint::_mutexPrint{};

#endif /* MutexPrint_hpp */