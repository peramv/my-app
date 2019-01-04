#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_number_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_number_empty() { }
		~CIFast_IFast_ifastcbo_err_account_number_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number in automatic transfer allocation is empty.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account number in automatic transfer allocation is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fehler: Kontonummer in der automatischen Transfer-Zuweisung ist leer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("error: el número de cuenta en la asignación de transferencia automática está vacío")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte pour la répartition de transfert automatique est manquant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("fout: accountnummer in automatische overdrachtsallocatie is leeg")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please go to allocation screen")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please go to allocation screen")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Rufen Sie bitte den Zuweisungsbildschirm auf")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please go to allocation screen")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez aller à l'écran de répartition.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("ga naar allocatiescherm")); }
	};
}



