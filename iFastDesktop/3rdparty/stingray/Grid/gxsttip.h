// This is a part of the Objective Grid C++ Library.
// Copyright � 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government�s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Ricky Pearson
//
// gxsttip.h : declaration of cell tip functionality
//			   in CGXStatic
//

#ifndef _GX_STT_IP_H__
#define _GX_STT_IP_H__

struct CGXCellTipStatic : public CGXCellTipBase
{
	CGXCellTipStatic(CGXStatic* pStatic);
	
	virtual ~CGXCellTipStatic();
	
	virtual BOOL NeedShowCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);

	virtual DWORD GetCellTipID(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);

	virtual void InitializeCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CGXCellTipWnd* pCellTip);
	
	CGXStatic* m_pStatic;
};

#endif //_GX_STT_IP_H__
