	/*
  Copyright (C) 2011 Markus Kauppila <markus.kauppila@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h> /* printf/fprintf */
#include <stdarg.h> /* va_list */
#include <time.h>

#include "logger.h"

#include "SDL_test.h"

/*! \brief return value of test case. Non-zero value means that the test failed */
int _testReturnValue;

/*! \brief counts the failed asserts */
int _testAssertsFailed;

/*! \brief counts the passed asserts */
int _testAssertsPassed;

void
_InitTestEnvironment()
{
	_testReturnValue = 0;
	_testAssertsFailed = 0;
	_testAssertsPassed = 0;
}

int
_QuitTestEnvironment()
{
	AssertSummary(_testAssertsFailed + _testAssertsPassed,
                  _testAssertsFailed, _testAssertsPassed, time(0));

	if(_testAssertsFailed == 0 && _testAssertsPassed == 0) {
		_testReturnValue = 2;
	}

	return _testReturnValue;
}

int
_CountFailedAsserts() {
	return _testAssertsFailed;
}

void
AssertEquals(int expected, int actual, char *message, ...)
{
   va_list args;
   char buf[256];

   va_start( args, message );
   memset(buf, 0, sizeof(buf));
   SDL_vsnprintf( buf, sizeof(buf), message, args );
   va_end( args );

   if(expected != expected) {
      AssertWithValues("AssertEquals", 0, buf, actual, expected, time(0));

      _testReturnValue = 1;
      _testAssertsFailed++;
   } else {
	   AssertWithValues("AssertEquals", 1, buf,
    		  actual, expected, time(0));

      _testAssertsPassed++;
   }
}

void
AssertTrue(int condition, char *message, ...)
{
   va_list args;
   char buf[256];
   va_start( args, message );
   SDL_vsnprintf( buf, sizeof(buf), message, args );
   va_end( args );

   if (!condition) {
      Assert("AssertTrue", 0, buf, time(0));

      _testReturnValue = 1;
      _testAssertsFailed++;
   } else {
		Assert("AssertTrue", 1, buf, time(0));

		_testAssertsPassed++;
   }
}

void
AssertPass(char *message, ...)
{
   va_list args;
   char buf[256];
   
   va_start( args, message );
   SDL_vsnprintf( buf, sizeof(buf), message, args );
   va_end( args );

   Assert("AssertPass", 1, buf, time(0));

   _testAssertsPassed++;
}

void
AssertFail(char *message, ...)
{
   va_list args;
   char buf[256];
   
   va_start( args, message );
   SDL_vsnprintf( buf, sizeof(buf), message, args );
   va_end( args );

   Assert("AssertFail", 0, buf, time(0));

   _testReturnValue = 1;
   _testAssertsFailed++;
}

