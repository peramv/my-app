#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_stop_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_stop_transfer() { }
		~CIFast_IFast_ifastcbo_err_fund_stop_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_STOP_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer is not allowed to the fund and class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer in diesen Fonds und diese Klasse nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias a este fondo y clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transfert non autorisé pour le fonds et la classe")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht is niet toegestaan naar dit fonds en deze categorie")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please select another fund or class.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("please select another fund or class.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please select another fund or class.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez sélectionner un autre fonds ou une autre classe.")); }
	};
}



