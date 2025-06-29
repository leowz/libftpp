#ifndef THREAD_SAFE_IOSTREAM_TPP
# define THREAD_SAFE_IOSTREAM_TPP

template<typename T>
ThreadSafeIOStream& ThreadSafeIOStream::operator<<(const T& value) {
    std::lock_guard<std::mutex> lock(outputMutex);
    printPrefixIfNewLine();
    std::ostringstream oss;
    oss << value;
    const std::string& str = oss.str();

    for (char c : str) {
        if (isNewLine) printPrefixIfNewLine();
        std::cout.put(c);
        isNewLine = (c == '\n');
    }
    std::cout.flush();
    return *this;
}

template<typename T>
ThreadSafeIOStream& ThreadSafeIOStream::operator>>(T& value) {
    std::lock_guard<std::mutex> lock(inputMutex);
    std::istringstream iss(threadPrefix);
    iss >> value;
    return *this;
}

template<typename T>
void ThreadSafeIOStream::prompt(const std::string& question, T& dest) {
    *this << question;
    *this >> dest;
}

#endif
