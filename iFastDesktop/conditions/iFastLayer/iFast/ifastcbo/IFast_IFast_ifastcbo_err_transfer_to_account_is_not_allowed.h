#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_to_account_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_to_account_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_transfer_to_account_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TO_ACCOUNT_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from fund %FUND% and class %CLASS% to account %ACCOUNT% is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer from fund %FUND% and class %CLASS% to account %ACCOUNT% is not allowed.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transfer from fund %FUND% and class %CLASS% to account %ACCOUNT% is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert du fonds %FUND% et de la classe %CLASS% au compte %ACCOUNT% n'est pas autorisé.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please go to allocation screen to change fund and class.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please go to allocation screen to change fund and class.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please go to allocation screen to change fund and class.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez aller à l'écran de répartition pour changer le fonds et la classe.")); }
	};
}



