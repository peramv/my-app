#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_maximum_input_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_maximum_input_amt() { }
		~CIFast_IFast_ifastcbo_err_maximum_input_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MAXIMUM_INPUT_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input amount exceeds the group contribution limit of %MAXIMUM_AMT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eingabebetrag überschreitet die Gruppen-Beteiligungs-Grenze %MAXIMUM_AMT%. Bitte geben Sie einen neuen Betrag ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto introducido excede el límite de aportación de grupo %MAXIMUM_AMT%. Por favor vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant saisi excède la limite de cotisation de groupe qui est de %MAXIMUM_AMT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invoerbedrag overschrijft limiet groepsbijdrage %MAXIMUM_AMT%, vul opnieuw in")); }

        // Actions
	};
}



