#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_too_many_failed_logons : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_too_many_failed_logons() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_too_many_failed_logons() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_TOO_MANY_FAILED_LOGONS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("End of data reached.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("End of data reached.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenende erreicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se llegó al final de los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fin des données")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einde gegevens bereikt")); }

        // Actions
	};
}



