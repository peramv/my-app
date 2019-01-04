#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_closeacctcode_not_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_closeacctcode_not_fund() { }
		~CIFast_IFast_ifastdbrkr_err_closeacctcode_not_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLOSEACCTCODE_NOT_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Controls record CloseAcctCode not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Controls record CloseAcctCode not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontrolleintrag \"CloseAcctCode\" wurde nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro de controles CloseAcctCode")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de fermeture du compte de l'enregistrement des contrôles est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Besturingsrecord CloseAcctCode is niet gevonden")); }

        // Actions
	};
}



