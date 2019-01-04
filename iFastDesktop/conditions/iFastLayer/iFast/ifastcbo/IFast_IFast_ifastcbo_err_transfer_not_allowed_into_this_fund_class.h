#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_not_allowed_into_this_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_not_allowed_into_this_fund_class() { }
		~CIFast_IFast_ifastcbo_err_transfer_not_allowed_into_this_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_NOT_ALLOWED_INTO_THIS_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange is not allowed into this fund class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer in diese Fondsklasse nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias a esta clase de fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échanges non autorisé dans cette classe de fonds")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht is niet toegestaan naar deze fondscategorie")); }

        // Actions
	};
}



