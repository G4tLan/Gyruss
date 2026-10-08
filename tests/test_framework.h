#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

// Minimal dependency-free test framework. A test is a function registered at
// static-initialisation time; tests/*.cpp are linked together with tests/main.cpp
// which calls testfw::run().
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace testfw {

struct TestCase {
	std::string name;
	std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
	static std::vector<TestCase> cases;
	return cases;
}

inline int& failureCount() {
	static int failures = 0;
	return failures;
}

inline int& checkCount() {
	static int checks = 0;
	return checks;
}

struct Registrar {
	Registrar(const std::string& name, std::function<void()> fn) {
		registry().push_back(TestCase{name, fn});
	}
};

inline void reportFailure(const std::string& expr, const char* file, int line) {
	++failureCount();
	std::cerr << "    FAILED: " << expr << "  (" << file << ":" << line << ")\n";
}

inline int run() {
	std::cout << "Running " << registry().size() << " tests\n\n";
	int failedTests = 0;
	for (auto& test : registry()) {
		int failuresBefore = failureCount();
		std::cout << "[ RUN  ] " << test.name << "\n";
		test.fn();
		if (failureCount() == failuresBefore) {
			std::cout << "[  OK  ] " << test.name << "\n";
		} else {
			std::cout << "[ FAIL ] " << test.name << "\n";
			++failedTests;
		}
	}
	std::cout << "\n" << registry().size() << " tests run, "
	          << failedTests << " failed, "
	          << checkCount() << " checks, "
	          << failureCount() << " failed checks\n";
	return failedTests == 0 ? 0 : 1;
}

}  // namespace testfw

#define TEST(name)                                            \
	static void name();                                       \
	static testfw::Registrar testfw_reg_##name(#name, name);  \
	static void name()

#define CHECK(cond)                                            \
	do {                                                       \
		++testfw::checkCount();                                \
		if (!(cond)) {                                         \
			testfw::reportFailure(#cond, __FILE__, __LINE__);  \
		}                                                      \
	} while (0)

#define REQUIRE(cond)                                          \
	do {                                                       \
		++testfw::checkCount();                                \
		if (!(cond)) {                                         \
			testfw::reportFailure(#cond, __FILE__, __LINE__);  \
			return;                                            \
		}                                                      \
	} while (0)

#define CHECK_EQ(a, b)                                                  \
	do {                                                                \
		++testfw::checkCount();                                         \
		if (!((a) == (b))) {                                            \
			std::cerr << "    FAILED: " << #a << " == " << #b           \
			          << "  (got " << (a) << " vs " << (b) << ")  ("    \
			          << __FILE__ << ":" << __LINE__ << ")\n";          \
			++testfw::failureCount();                                   \
		}                                                               \
	} while (0)

#define REQUIRE_EQ(a, b)                                                \
	do {                                                                \
		++testfw::checkCount();                                         \
		if (!((a) == (b))) {                                            \
			std::cerr << "    FAILED: " << #a << " == " << #b           \
			          << "  (got " << (a) << " vs " << (b) << ")  ("    \
			          << __FILE__ << ":" << __LINE__ << ")\n";          \
			++testfw::failureCount();                                   \
			return;                                                     \
		}                                                               \
	} while (0)

#define CHECK_NEAR(a, b, eps)                                          \
	do {                                                               \
		++testfw::checkCount();                                        \
		if (std::fabs((a) - (b)) > (eps)) {                            \
			std::cerr << "    FAILED: " << #a << " ~= " << #b          \
			          << "  (got " << (a) << " vs " << (b) << ")  ("   \
			          << __FILE__ << ":" << __LINE__ << ")\n";         \
			++testfw::failureCount();                                  \
		}                                                              \
	} while (0)

#endif  // TEST_FRAMEWORK_H
