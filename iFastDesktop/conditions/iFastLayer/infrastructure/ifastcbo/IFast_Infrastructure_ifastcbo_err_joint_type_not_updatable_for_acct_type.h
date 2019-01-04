#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_joint_type_not_updatable_for_acct_type : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_joint_type_not_updatable_for_acct_type() { }
		~CIFast_Infrastructure_ifastcbo_err_joint_type_not_updatable_for_acct_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_JOINT_TYPE_NOT_UPDATABLE_FOR_ACCT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be numeric. Type a numeric value.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^ must be numeric. Type a numeric value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss nummerisch sein. Geben Sie einen nummerischen Wert ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% debe ser numérico. Escriba un valor numérico.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %FIELD% doit être numérique. Entrez une valeur numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet numeriek zijn. Typ een numerieke waarde")); }

        // Actions
	};
}



