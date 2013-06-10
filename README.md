# N-Test Library

This an unit test framework used by the Nova project for the testing of its components.
Its goal is to be easy to use, fast and independent, it doesn't have any dependences in
other libraries.

## Usage

To use N-Test inside a project, you need to develop the tests using the macros offered by
the library. Just add the 'public' directory as an additional directory in the compiler
options.

Then include 'n-test\test-manager.hpp', and use the macros 'TEST\_UNIT' and 'TEST\_METHOD'.

<pre>
#include &lt;n-test\test-unit.hpp&gt;

TEST_UNIT("test-unit")
	TEST_METHOD("test-method", testContext) {
		testContext.Accept();
	}
END_TEST_UNIT
</pre>

Inside a test method, testContext.Accept() signals a successful test, and testContext.Fail()
does the same with a failed test.

Now, to run all the tests, you just need to execute:

<pre>
Nova::Test::GetTestManagerInstance().RunAll();
</pre>

Just include 'n-test\test-manager.hpp'. An simple example of a main function follows:

<pre>
#include &lt;n-test\test-manager.hpp&gt;

int main() {
	Nova::Test::GetTestManagerInstance().RunAll();
	return 0;
}
</pre>

There is a sample project in the 'sample' directory.

## License

This projects use the [MIT License](LICENSE.md).

## History

Version 0.1 - First version released.