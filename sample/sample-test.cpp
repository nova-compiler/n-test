//
// sample-test.cpp
//
// Copyright (c) 2013 Luis Garcia.
// This source file is subject to terms of the MIT License. (See accompanying file LICENSE)
//

#include <n-test\test-unit.hpp>
#include "sample-class.hpp"

TEST_UNIT("sample-test")
	TEST_METHOD("succesful-test", testContext) {
		SampleClass sampleClass;
		testContext.Accept(sampleClass.Foo() == 42);
	}

	TEST_METHOD("failed-test", testContext) {
		SampleClass sampleClass;
		testContext.Accept(sampleClass.Foo() == 11);
	}
END_TEST_UNIT
