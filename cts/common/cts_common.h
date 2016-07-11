/* Copyright 2016 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __CTS_COMMON_H
#define __CTS_COMMON_H

#include "console.h"

/* Console output macros */
#define CPUTS(outstr) cputs(CC_SYSTEM, outstr)
#define CPRINTF(format, args...) cprintf(CC_SYSTEM, format, ## args)
#define CPRINTS(format, args...) cprints(CC_SYSTEM, format, ## args)

/* In a single test, only one board can return unknown, the other must
 * return a useful result (i.e. success, failure, etc)
 */
enum cts_error_code {
	SUCCESS,
	FAILURE,
	BAD_SYNC,
	UNKNOWN
};

#endif
