#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_owner_duplicate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_owner_duplicate() { }
		~CIFast_IFast_ifastcbo_err_acct_owner_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_OWNER_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate set up is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les doublons de configurations ne sont pas autorisés.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppelte Erstellung ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite la configuración repetida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La copie du réglage n'est pas autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbele instelling is niet toegestaan")); }

        // Actions
	};
}



