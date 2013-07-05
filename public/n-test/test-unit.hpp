//
// test-unit.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_COMMON_UNIT_TEST_HEADER_
#define _NOVA_COMMON_UNIT_TEST_HEADER_

#include <map>
#include <string>

namespace Nova {
namespace Test {

	class IUnitContext {
	public:
		virtual void Accept(
			bool value
			) = 0;

		virtual void EndMethod(
			const std::string & methodName
			) = 0;

		virtual int GetSuccessCount(
			) const = 0;

		virtual int GetAttemptsCount(
			) const = 0;
	};

	class TestContext {
		IUnitContext & _unitContext;
		std::string _methodName;

		TestContext(const TestContext & other);
		TestContext & operator = (const TestContext & other);

	public:
		inline TestContext(
			const std::string & methodName, IUnitContext & unitContext
			)
			: _methodName(methodName), _unitContext(unitContext)
			{
			}

		inline ~TestContext(
			) {
				_unitContext.EndMethod(_methodName);
			}

		void Accept(
			bool value = true
			) {
				_unitContext.Accept(value);
			}

		void Fail(
			) {
				Accept(false);
			}
	};

	namespace Internal {
		typedef void (* TestMethodFn) (TestContext & testContextName);
	}

	/// <summary>
	/// Utility class for the management of test units.
	/// </summary>
	class TestManager {
		struct _TestUnit {
			std::map<std::string, Internal::TestMethodFn> Methods;
		};

		std::map<std::string, _TestUnit *> _units;

		TestManager(const TestManager & other);
		TestManager & operator =(const TestManager & other);

	public:
		inline TestManager(
			) {
			}

		/// <summary>
		/// Destructor for the instance.
		/// </summary>
		~TestManager(
			) {
				for (auto unit : _units)
					delete unit.second;
			}

		/// <summary>
		/// Register a new method in the manager.
		/// </summary>
		/// <param name="unitName">
		/// Name of the unit.
		/// </param>
		/// <param name="unitMethodName">
		/// Name of the method to register assigned to the specified unit name.
		/// </param>
		void RegisterMethod(
			const char * unitName, const char * unitMethodName, Internal::TestMethodFn callback
			) {
				if (_units[unitName] == NULL)
					_units[unitName] = new _TestUnit();

				if (_units[unitName]->Methods[unitMethodName]) {
					std::string message = std::string() + "Warning: Method '" + unitName + "' already registered in the unit '" + unitMethodName + "'. Ignored.";
					puts(message.c_str());
				} else
					_units[unitName]->Methods[unitMethodName] = callback;
			}

		/// <summary>
		/// Run all test registered in the manager.
		/// </summary>
		bool RunAll(
			);
	};

	/// <summary>
	/// Get default instance of the manager.
	/// </summary>
	inline TestManager & GetTestManagerInstance(
		) {
			static TestManager testManager;
			return testManager;
		}

	namespace Internal {
		class TestMethodStub {
		public:
			inline TestMethodStub(
				const char * unitId, const char * method, TestMethodFn testMethod
				) {
					GetTestManagerInstance().RegisterMethod(unitId, method, testMethod);
				}
		};
	}

#define _TEST_UNIT_2(id, counter) \
	namespace { \
		namespace TestUnit##counter { \
			static const char * nova_testUnitId = id; \

#define _TEST_UNIT_1(id, counter) \
	_TEST_UNIT_2(id, counter)

#define TEST_UNIT(id) \
	_TEST_UNIT_1(id, __LINE__)

#define END_TEST_UNIT \
		} \
	}

#define _TEST_METHOD_2(id, testContextName, counter) \
	static void TestMethod##counter(::Nova::Test::TestContext & testContextName); \
	static ::Nova::Test::Internal::TestMethodStub stub##counter(nova_testUnitId, id, TestMethod##counter); \
	\
	static void TestMethod##counter(::Nova::Test::TestContext & testContextName)

#define _TEST_METHOD_1(id, testContextName, counter) \
	_TEST_METHOD_2(id, testContextName, counter)

#define TEST_METHOD(id, testContextName) \
	_TEST_METHOD_1(id, testContextName, __LINE__)

} // namespace Test
} // namespace Nova

#endif // !_NOVA_COMMON_UNIT_TEST_HEADER_