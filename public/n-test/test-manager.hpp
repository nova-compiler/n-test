//
// test-manager.hpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#ifndef _NOVA_COMMON_TEST_MANAGER_HEADER_
#define _NOVA_COMMON_TEST_MANAGER_HEADER_

#include "test-unit.hpp"

namespace Nova {
namespace Test {

	class DefaultUnitContext : public IUnitContext {
		std::string _unitName;
		int _success, _attempts;
		int _totalSuccess, _totalAttempts;

	public:
		inline explicit DefaultUnitContext(
			const std::string & unitName
			)
			: _unitName(unitName), _success(0), _attempts(0), _totalSuccess(0), _totalAttempts(0)
			{
			}

		inline ~DefaultUnitContext(
			) {

			}

		virtual void Accept(
			bool value
			) override {
				if (value) ++_success, ++_totalSuccess;
				++_attempts, ++_totalAttempts;
			}

		virtual void EndMethod(
			const std::string & methodName
			) override {
				printf("%s\\%s [%d/%d]\n", _unitName.c_str(), methodName.c_str(), _success, _attempts);
				_success = _attempts = 0;
			}

		virtual int GetSuccessCount(
			) const override {
				return _totalSuccess;
			}

		virtual int GetAttemptsCount(
			) const override {
				return _totalAttempts;
			}
	};

	bool TestManager::RunAll(
		) {
			bool success = true;
			for (auto unit : _units) {
				DefaultUnitContext unitContext(unit.first);
				for (auto method : unit.second->Methods) {
					TestContext context(method.first, unitContext);
					method.second(context);
				}

				if (unitContext.GetSuccessCount() < unitContext.GetAttemptsCount())
					success = false;
			}

			return success;
		}

} // namespace Test
} // namespace Nova

#endif // !_NOVA_COMMON_TEST_MANAGER_HEADER_