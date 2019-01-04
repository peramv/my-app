///////////////////////////////////////////////////////////////////////////////
// MvcZoomCommand.h : Zoom command class
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author:       Jeff Boenig
// Description:  Zoom command class
//

#pragma once

#ifndef __MVCZOOMCOMMAND_H__
#define __MVCZOOMCOMMAND_H__

#if !defined(_SFL)
#define _SFL
#endif

#include <Foundation\MVC\MvcCommand.h>

namespace stingray {
namespace foundation {

/////////////////////////////////////////////////////////////////////////////
//@doc CMvcZoomCommand
//
//@class CMvcZoomCommand | Implements a zoom command by querying the command
// receiver object for the <c IZoom> interface and using the interface
// acquired to change the magnification.
//
//@tcarg unsigned int | nTypeID | Type identifier for the command.
//@tcarg typename | _Receiver | Type of object that will receive the command.
//
//@base public | CMvcCommand

template <unsigned int nTypeID, typename _Receiver>
class CMvcZoomCommand : public CMvcCommand
{
// Constructors/destructor
public:
	//@cmember
	/* Construct a zoom command. */
	CMvcZoomCommand(_Receiver* pICmdRecvr = NULL) :
		m_nZoomPctX(100),
		m_nZoomPctY(100)
	{
		SetCommandReceiver(pICmdRecvr);
	}

// Attributes
protected:
	//@cmember
	/* Pointer to the object that will receiver the command. */
	_Receiver* m_pCmdRecvr;
	//@cmember
	/* Magnification for X axis in percent. */
	int m_nZoomPctX;
	//@cmember
	/* Magnification for Y axis in percent. */
	int m_nZoomPctY;

// Operations
public:
	//@cmember
	/* The type ID of the message.  Used for safe typecasting. */
	virtual unsigned int GetTypeID() const
	{
		return nTypeID;
	}

	//@cmember
	/* Print information on the zoom command for logging purposes. */
	virtual void Sprint(CString& strCmd)
	{
		strCmd.Format(_T("Zoom Command: X magnification = %d, Y magnification = %d"), m_nZoomPctX, m_nZoomPctY);
	}

	//@cmember
	/* Assign pointer to the command receiver. */
	void SetCommandReceiver(_Receiver* pCmdRecvr)
	{
		m_pCmdRecvr = pCmdRecvr;
	}

	//@cmember
	/* Set the magnification values. */
	virtual void SetMagnification(const int nZoomPctX, const int nZoomPctY)
	{
		m_nZoomPctX = nZoomPctX;
		m_nZoomPctY = nZoomPctY;
	}

	//@cmember
	/* Return the magnification values. */
	virtual void GetMagnification(int& nZoomPctX, int& nZoomPctY)
	{
		nZoomPctX = m_nZoomPctX;
		nZoomPctY = m_nZoomPctY;
	}

	//@cmember
	/* Execute the zoom command. */
	virtual BOOL Execute()
	{
		IZoom* pIZoom = guid_cast<IZoom*>(m_pCmdRecvr);
		if (pIZoom != NULL)
		{
			pIZoom->SetMagnification(m_nZoomPctX, m_nZoomPctY);
		}
		ISubject* pISubject = guid_cast<ISubject*>(m_pCmdRecvr);
		if (pISubject != NULL)
		{
			pISubject->UpdateAllObservers(NULL, this);
		}
		return TRUE;
	}
};

};	// namespace stingray::foundation
};  // namespace stingray

#endif  // #ifndef __MVCZOOMCOMMAND_H__
