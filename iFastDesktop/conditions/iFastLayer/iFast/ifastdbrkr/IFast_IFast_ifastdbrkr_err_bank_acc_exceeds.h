#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bank_acc_exceeds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bank_acc_exceeds() { }
		~CIFast_IFast_ifastdbrkr_err_bank_acc_exceeds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_ACC_EXCEEDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank account number exceeds allowable numbers of digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Bank account number exceeds allowable numbers of digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankkontonummer überschreitet die erlaubte Anzahl der Ziffern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta bancaria excede la cantidad de dígitos permitida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte bancaire excède le nombre de caractères numériques autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer bankrekening overschrijdt toegestane aantal cijfers")); }

        // Actions
	};
}



