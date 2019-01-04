#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_inactive_sales_rep : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_inactive_sales_rep() { }
		~CIFast_IFast_ifastcbo_err_inactive_sales_rep() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INACTIVE_SALES_REP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account sales representative is inactive. Please change sales representative at the account level.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account sales representative is inactive. Please change sales representative at the account level.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto Verkaufsvertreter ist inaktiv. Bitte ändern Sie den Verkaufsvertreter auf Konto-Level.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El representante de ventas de la cuenta está inactivo. Por favor cambie el representante de ventas al nivel de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le représentant des ventes du compte est inactif. Veuillez changer le représentant des ventes au niveau du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger account is inactief. Wijzig vertegenwoordiger op het accountniveau")); }

        // Actions
	};
}



