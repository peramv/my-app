#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_hold_for_return_mail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_hold_for_return_mail() { }
		~CIFast_IFast_ifastcbo_err_no_hold_for_return_mail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_HOLD_FOR_RETURN_MAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Hold flag must be set to Yes when authorization is Return Mail for document type %TYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de retenue doit être activé lorsque l'autorisation est Retour de courrier pour le type de document %TYPE%.")); }

        // Actions
	};
}



