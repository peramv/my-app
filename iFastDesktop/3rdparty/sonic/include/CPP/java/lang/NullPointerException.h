#ifndef _JAVA_LANG_NULLPOINTEREXCEPTION_H_
#define _JAVA_LANG_NULLPOINTEREXCEPTION_H_
/*
 * Copyright (c) 2001 - 2008 Progress Software Corporation. All Rights Reserved.
 * This software is the confidential and proprietary information of Progress
 * Software Corporation ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Progress Software Corporation.
 */

#include <java/lang/package_decls.h>
#include <java/lang/RuntimeException.h>

namespace java { namespace lang {

  /**
   * Thrown to indicate that a null pointer was derefenced within
   * the SonicMQ client library.
   */
  class SMQJ_API NullPointerException : public RuntimeException
  {
  public:
    /**
     * For Sonic Software Internal use only: DO NOT USE.
     */
	virtual ~NullPointerException();

    /**
     * Returns the type-code for this class' classtype.
     *
     * @return     the type-code for this class.
     */
	static int		type();

    /**
     * Returns the type-code for this object's classtype.
     *
     * @return     the type-code for this object.
     */
	virtual int		getType() const;

    /**
     * Indicates whether this object is an instance of the given classtype. 
     * An object is an instance of the given classtype if it is exactly
     * that classtype or derives from that classtype.
     *
     * @param   classtype   the type-code for the classtype with which to compare.
     * @return  <code>jtrue</code> if this object is the same as or derived from
     *          the given classtype;<code>jfalse</code> otherwise.
     */
	virtual bool	instanceof(int classtype) const;
  };

}} // namespace java::lang

using java::lang::NullPointerException;
using java::lang::NullPointerExceptionRef;

#endif // _JAVA_LANG_NULLPOINTEREXCEPTION
