#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_to_lrsp_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_to_lrsp_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_transfer_to_lrsp_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TO_LRSP_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer to LRSP is not allowed for shareholder over 71 years old.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert vers un REER immobilisé n'est pas autorisé pour un actionnaire âgé de plus de 71 ans.")); }

        // Actions
	};
}



