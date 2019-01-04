#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_acct_owner_needed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_acct_owner_needed() { }
		~CIFast_IFast_ifastcbo_err_multiple_acct_owner_needed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_ACCT_OWNER_NEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least two active Accountholder entities must be set up for this type of account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins deux entites de Titulaires de compte actives doivent être definies pour ce type de compte")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für diese Kontoart müssen mindestens zwei Kontoinhaber-Objekte erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Deben configurarse al menos dos entidades de titular de cuenta activas para este tipo de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins deux entités titulaires de compte actives doivent être réglées pour ce type de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moeten ten minste twee actieve accounthouderseenheden zijn gemaakt voor dit type account")); }

        // Actions
	};
}



