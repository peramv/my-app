#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_fundclass_transfer_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_fundclass_transfer_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_at_fundclass_transfer_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from %FIELD1% and %FIELD2% to %FIELD3% and %FIELD4% is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transfer from %FIELD1% and %FIELD2% to %FIELD3% and %FIELD4% is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer von %FIELD1% und %FIELD2% zu %FIELD3% und %FIELD4% ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transferencia de %FIELD1% y %FIELD2% a %FIELD3% y %FIELD4% no está permitida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert de %FIELD1% et %FIELD2% à %FIELD3% et %FIELD4% n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht van %FIELD1% en %FIELD2% naar %FIELD3% en %FIELD4% is niet toegestaan")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-enter fund or class")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-enter fund or class")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte geben Sie einen neuen Fonds oder eine neue Klasse ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-enter fund or class")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez saisir de nouveau le fonds ou la classe.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul fonds of categorie opnieuw in")); }
	};
}



