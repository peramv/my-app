#ifndef _PROGRESS_MESSAGE_JCLIENT_JMSSECURITYEXCEPTION_H_
#define _PROGRESS_MESSAGE_JCLIENT_JMSSECURITYEXCEPTION_H_

/*
 * Copyright (c) 2001 - 2008 Progress Software Corporation. All Rights Reserved.
 * This software is the confidential and proprietary information of Progress
 * Software Corporation ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Progress Software Corporation.
 */

#include <progress/message/jclient/JMSException.h>

namespace progress { namespace message { namespace jclient {

class SMQ_API JMSSecurityException : public JMSException
{
public:
	virtual ~JMSSecurityException();

	/**
	 * Returns the int corresponding to the JMSSecurityException type.
	 *
	 * @return the int corresponding to the JMSSecurityException type
	 */
	static  int type();
    /**
     * Returns the type-code for this object's classtype.
     *
     * @return     the type-code for this object.
     */
	virtual int getType() const;
    /**
     * Indicates whether this object is an instance of the given classtype. 
     * An object is an instance of the given classtype if it is exactly
     * that classtype or derives from that classtype.
     *
     * @param   classtype   the type-code for the classtype with which to compare.
     * @return  <code>jtrue</code> if this object is the same as or derived from
     *          the given classtype;<code>jfalse</code> otherwise.
     */
	virtual bool instanceof(int classtype) const;
};

}}} // namespace

#endif // _PROGRESS_MESSAGE_JCLIENT_JMSSECURITYEXCEPTION_H_
