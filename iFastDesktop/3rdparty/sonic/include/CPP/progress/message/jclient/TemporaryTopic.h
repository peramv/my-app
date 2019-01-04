#ifndef _PROGRESS_MESSAGE_JCLIENT_TEMPORARYTOPIC_H_
#define _PROGRESS_MESSAGE_JCLIENT_TEMPORARYTOPIC_H_
/*
 * Copyright (c) 2001 - 2008 Progress Software Corporation. All Rights Reserved.
 * This software is the confidential and proprietary information of Progress
 * Software Corporation ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Progress Software Corporation.
 */

#include <progress/message/jclient/Topic.h>

namespace progress { namespace message { namespace jclient {


/** A TemporaryTopic is a unique Topic object created for the duration of 
  * a TopicConnection. It is a system defined Topic that can only be 
  * consumed by the TopicConnection that created it.
  */
class SMQ_API TemporaryTopic : public Topic
{
public:
	virtual ~TemporaryTopic();

	/**
	 * Returns the int corresponding to the TemporaryTopic type.
	 *
	 * @return the int corresponding to the TemporaryTopic type
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

	/** Delete this temporary topic. If there are still existing publishers
     * or subscribers still using it, then a JMSException will be thrown.
     *  
     * @exception JMSException if JMS implementation fails to delete a 
     *                         Temporary queue due to some internal error.
     */
	virtual void _delete();

    private: void PMJTTreserved0();
};

}}} // namespace progress::message::jclient

#endif // _PROGRESS_MESSAGE_JCLIENT_TEMPORARYTOPIC_H_
