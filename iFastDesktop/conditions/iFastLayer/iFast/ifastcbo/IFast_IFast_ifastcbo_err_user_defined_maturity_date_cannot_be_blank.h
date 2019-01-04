#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_defined_maturity_date_cannot_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_defined_maturity_date_cannot_be_blank() { }
		~CIFast_IFast_ifastcbo_err_user_defined_maturity_date_cannot_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User Defined Maturity Date cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance définie par l'utilisateur est requise.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please click the User Defined Maturity Date button and select your date.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez cliquer sur le bouton Date d'échéance définie par l'utilisateur et sélectionner votre date.")); }
	};
}



