#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_miss_bank_country : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_miss_bank_country() { }
		~CIFast_IFast_ifastcbo_err_miss_bank_country() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISS_BANK_COUNTRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank Country is mandatory; please enter it on the banking screen.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bankland ist obligatorisch, bitte geben Sie es im Banking-Bildschirm ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El país del banco es obligatorio; por favor introdúzcalo en la pantalla de bancos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pays de la banque est requis; veuillez l'entrer dans l'écran d'information bancaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bankland is verplicht, vul dit in op het bankscherm")); }

        // Actions
	};
}



