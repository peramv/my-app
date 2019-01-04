#ifndef _PROGRESS_MESSAGE_JCLIENT_ERRORCODES_H_
#define _PROGRESS_MESSAGE_JCLIENT_ERRORCODES_H_

/*
 * Copyright (c) 2001 - 2008 Progress Software Corporation. All Rights Reserved.
 * This software is the confidential and proprietary information of Progress
 * Software Corporation ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Progress Software Corporation.
 */

#include <java/lang/package.h>
#include <progress/message/jclient/package_decls.h>

namespace progress { namespace message { namespace jclient {

class SMQ_API ErrorCodes
{
public:
	/**
	 * Tests the error code associated with a JMSException against
	 * an integer value associated with a Progress SonicMQ ErrorCode.
	 *
	 * @param anException A JMSException that needs to be tested.
	 * @param aCode An error code specified as an integer.
	 *
	 * @returns True, if the error code of the exception is the one specified.
	 */
	static jboolean testException(JMSExceptionRef anException, jint aCode);
};

}}} // namespace


#endif // _PROGRESS_MESSAGE_JCLIENT_ERRORCODES_H_
