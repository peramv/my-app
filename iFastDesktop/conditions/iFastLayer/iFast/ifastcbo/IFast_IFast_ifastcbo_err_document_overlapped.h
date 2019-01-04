#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_document_overlapped : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_document_overlapped() { }
		~CIFast_IFast_ifastcbo_err_document_overlapped() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DOCUMENT_OVERLAPPED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are other documents with the same type overlap with this document.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("D’autres documents du même type recoupent partiellement le présent document.")); }

        // Actions
	};
}



