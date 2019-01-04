#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_percentage_not_equal_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_percentage_not_equal_100() { }
		~CIFast_IFast_ifastcbo_err_percentage_not_equal_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PERCENTAGE_NOT_EQUAL_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocations for this Account Fund and Class must total 100 percent.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocations for this Account Fund and Class must total 100 percent.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisungen für diese(n) Konto-Fonds und –Klasse müssen 100 Prozent ergeben. Bitte bestätigen Sie dies und gleichen Sie ihre Angaben entsprechend an.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las asignaciones para este fondo y clase de cuenta deben sumar 100 por ciento. Por favor verifique y haga los ajustes necesarios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions pour le fonds et la classe de ce compte doivent totaliser 100 %.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Allocaties voor dit accountfonds en deze categorie moeten in totaal 100 procent zijn. Controleer en pas dit zo nodig aan")); }

        // Actions
	};
}



