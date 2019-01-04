#ifndef _JAVA_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H_
#define _JAVA_LANG_STRINGINDEXOUTOFBOUNDSEXCEPTION_H_
/*
 * Copyright (c) 2001 - 2008 Progress Software Corporation. All Rights Reserved.
 * This software is the confidential and proprietary information of Progress
 * Software Corporation ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Progress Software Corporation.
 */

#include <java/lang/IndexOutOfBoundsException.h>

namespace java { 
    namespace lang { 

	/**
	 * Thrown by the <code>charAt</code> method in class 
	 * <code>String</code> and by other <code>String</code> 
	 * methods to indicate that an index is either negative or greater 
	 * than or equal to the size of the string. 
	 */
	class SMQJ_API StringIndexOutOfBoundsException : public IndexOutOfBoundsException
	{
	    public:
	    /**
	     * For Sonic Software Internal use only: DO NOT USE.
	     */
	    virtual ~StringIndexOutOfBoundsException();

	    /**
	     * Returns the type-code for this class' classtype.
	     *
	     * @return     the type-code for this class.
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
	    virtual bool instanceof(int classType) const;
	};

    } // namespace lang
} // namespace java

#endif // _JAVA_LANG_ARRAYINDEXOUTOFBOUNDSEXCEPTION_H_
