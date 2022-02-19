#pragma once

#include <lib/panic.h>

#define assert_(e) do { if (!(e)) { panic();} } while (false)
