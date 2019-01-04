﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_amount_transfer : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_amount_transfer() { }
		~CIFast_IFast_ifastcbo_err_at_amount_transfer() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_AMOUNT_TRANSFER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full Transfer is not allowed on Multi-Transfers.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Full Transfer is not allowed on Multi-Transfers.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Voller Transfer ist bei Mehrfach-Transfers nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias totales sobre transferencias múltiples.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert total n'est pas autorisé parmi les multitransferts.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige overdracht is niet toegestaan bij meervoudige overdrachten")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-enter amount")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-enter amount")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie den Betrag erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-enter amount")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez saisir de nouveau le montant.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul bedrag opnieuw in")); }
	};
}



