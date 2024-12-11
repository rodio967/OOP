#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

template <typename T>
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const T& eventData) = 0;
};

template <typename T>
class Subject {
public:
    Subject();
    ~Subject();

    void attach(std::shared_ptr<IObserver<T>> observer);
    void detach(std::shared_ptr<IObserver<T>> observer);
    void notify(const T& eventData);

private:
    class SubjectImpl;
    std::unique_ptr<SubjectImpl> impl;
};

template <typename T>
class Subject<T>::SubjectImpl {
public:
    void attach(std::shared_ptr<IObserver<T>> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver<T>> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const T& eventData) {
        for (const auto& observer : observers) {
            if (observer) {
                observer->onEvent(eventData);
            }
        }
    }

private:
    std::vector<std::shared_ptr<IObserver<T>>> observers;
};

template <typename T>
Subject<T>::Subject() : impl(std::make_unique<SubjectImpl>()) {}

template <typename T>
Subject<T>::~Subject() = default;

template <typename T>
void Subject<T>::attach(std::shared_ptr<IObserver<T>> observer) {
    impl->attach(observer);
}

template <typename T>
void Subject<T>::detach(std::shared_ptr<IObserver<T>> observer) {
    impl->detach(observer);
}

template <typename T>
void Subject<T>::notify(const T& eventData) {
    impl->notify(eventData);
}


template <typename T>
class ConsoleObserver : public IObserver<T> {
public:
    void onEvent(const T& eventData) override {
        std::cout << "ConsoleObserver received event: " << eventData << std::endl;
    }
};

template <typename T>
class LoggingObserver : public IObserver<T> {
public:
    explicit LoggingObserver(const std::string& filename) : logFile(filename) {}

    void onEvent(const T& eventData) override {
        std::ofstream file(logFile, std::ios::app);
        if (file) {
            file << "LoggingObserver received event: " << eventData << std::endl;
        }
    }

private:
    std::string logFile;
};


struct CustomEvent {
    std::string id;
    std::string type;
    std::string payload;

    friend std::ostream& operator<<(std::ostream& os, const CustomEvent& event) {
        os << "CustomEvent { id: " << event.id << ", type: " << event.type
           << ", payload: " << event.payload << " }";
        return os;
    }
};

int main() {
    Subject<int> intSubject;
    auto intConsoleObserver = std::make_shared<ConsoleObserver<int>>();
    auto intLoggingObserver = std::make_shared<LoggingObserver<int>>("int_events.txt");

    intSubject.attach(intConsoleObserver);
    intSubject.attach(intLoggingObserver);
    intSubject.notify(30);


    Subject<std::string> stringSubject;
    auto stringConsoleObserver = std::make_shared<ConsoleObserver<std::string>>();
    auto stringLoggingObserver = std::make_shared<LoggingObserver<std::string>>("string_events.txt");

    stringSubject.attach(stringConsoleObserver);
    stringSubject.attach(stringLoggingObserver);
    stringSubject.notify("Hello, Observer!");


    Subject<CustomEvent> customEventSubject;
    auto customEventConsoleObserver = std::make_shared<ConsoleObserver<CustomEvent>>();
    auto customEventLoggingObserver = std::make_shared<LoggingObserver<CustomEvent>>("custom_events.txt");

    customEventSubject.attach(customEventConsoleObserver);
    customEventSubject.attach(customEventLoggingObserver);
    customEventSubject.notify({"123", "INFO", "This is a custom event"});

    return 0;
}