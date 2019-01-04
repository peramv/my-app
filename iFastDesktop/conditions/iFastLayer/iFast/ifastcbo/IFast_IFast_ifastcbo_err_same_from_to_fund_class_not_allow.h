#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_same_from_to_fund_class_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_same_from_to_fund_class_not_allow() { }
		~CIFast_IFast_ifastcbo_err_same_from_to_fund_class_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange to same fund and class within account is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'échange vers le même fonds et la même catégorie au sein du compte est désormais autorisé")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wechseln zu gleichem Fonds und gleicher Klasse innerhalb eines Kontos ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten traspasos al mismo fondo y clase dentro de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un échange au même fonds et à la même classe à l'intérieur du compte n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ruilen naar hetzelfde fonds en dezelfde categorie binnen account is niet toegestaan")); }

        // Actions
	};
}



