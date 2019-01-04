#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_invalid_acct_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_invalid_acct_taxtype() { }
		~CIFast_IFast_ifastcbo_err_at_invalid_acct_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_INVALID_ACCT_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfers are not allowed between accounts of these tax types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transfers are not allowed between accounts of these tax types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfers zwischen Konten dieser Steuerart sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias entre cuentas de estos tipos tributarios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transferts ne sont pas autorisés entre les comptes avec ces types d'imposition.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdrachten zijn niet toegestaan tussen accounts van deze belastingtypes")); }

        // Actions
	};
}



